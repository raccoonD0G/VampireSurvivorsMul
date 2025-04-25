@echo off
setlocal

:: 서버 실행 파일 경로
set SERVER_PATH="WindowsServer\VampireSurvivorsMulServer.exe"

:: 맵 이름
set MAP_NAME=DungeonLevel

:: 공통 인자
set COMMON_ARGS=?listen -log -nosteam

:: 매치메이커 서버 주소
set MATCHMAKER_URL=http://127.0.0.1:8000/register

:: 서버 1 실행
start "" %SERVER_PATH% %MAP_NAME%?port=7777%COMMON_ARGS%

:: 서버 2 실행
start "" %SERVER_PATH% %MAP_NAME%?port=7778%COMMON_ARGS%

:: 서버 3 실행
start "" %SERVER_PATH% %MAP_NAME%?port=7779%COMMON_ARGS%

timeout /t 2 > nul

:: 서버 등록 요청
echo Registering servers to matchmaker...

:: 서버 1 등록
curl -X POST %MATCHMAKER_URL% -H "Content-Type: application/json" -d "{\"ip\":\"127.0.0.1\",\"port\":7777,\"player_count\":0,\"max_players\":2}"

:: 서버 2 등록
curl -X POST %MATCHMAKER_URL% -H "Content-Type: application/json" -d "{\"ip\":\"127.0.0.1\",\"port\":7778,\"player_count\":0,\"max_players\":2}"

:: 서버 3 등록
curl -X POST %MATCHMAKER_URL% -H "Content-Type: application/json" -d "{\"ip\":\"127.0.0.1\",\"port\":7779,\"player_count\":0,\"max_players\":2}"

endlocal
pause
