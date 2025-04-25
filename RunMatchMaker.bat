@echo off
setlocal

:: 가상환경 경로 (필요하면 수정)
:: set VENV_PATH=C:\Users\admin\anaconda3\python.exe

:: 파이썬 실행 경로
set PYTHON_EXE=python

:: 실행할 서버 스크립트 (matchmaker.py)
set SERVER_SCRIPT=matchmaker:app

:: 포트 번호
set PORT=8000

:: (옵션) 가상환경 활성화
:: call %VENV_PATH%

:: 서버 실행
echo Starting FastAPI Matchmaker Server...
%PYTHON_EXE% -m uvicorn %SERVER_SCRIPT% --host 0.0.0.0 --port %PORT% --reload

endlocal
pause
