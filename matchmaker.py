from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from typing import List, Dict
import threading

app = FastAPI()

class ServerInfo(BaseModel):
    ip: str
    port: int
    player_count: int = 0
    max_players: int = 2

servers: List[Dict] = []
lock = threading.Lock()  # 동기화용 Lock

@app.post("/register")
def register_server(info: ServerInfo):
    with lock:
        for s in servers:
            if s["ip"] == info.ip and s["port"] == info.port:
                return {"message": "Already registered"}
        servers.append(info.dict())
    return {"message": "Server registered"}

@app.post("/heartbeat")
def heartbeat(info: ServerInfo):
    with lock:
        for s in servers:
            if s["ip"] == info.ip and s["port"] == info.port:
                s["player_count"] = info.player_count
                return {"message": "Heartbeat updated"}
    return {"error": "Server not found"}

@app.post("/join-match")
def join_match():
    with lock:
        for server in servers:
            if server["player_count"] < server["max_players"]:
                server["player_count"] += 1  # 즉시 증가!
                return {
                    "ip": server["ip"],
                    "port": server["port"]
                }
    raise HTTPException(status_code=503, detail="No available server")
