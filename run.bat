@echo off
@echo run_run
echo make
make
IF %ERRORLEVEL% EQU 0 (
	echo "main.exe"
	"main.exe"
)