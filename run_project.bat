@echo off
setlocal enabledelayedexpansion

:: 1. Precise Paths (No Admin needed)
set "COMPILER_PATH=%~dp0mingw64\bin"
set "GNUPLOT_PATH=%~dp0gnuplot\gnuplot\bin"
set "PATH=%COMPILER_PATH%;%GNUPLOT_PATH%;%PATH%"

echo [INFO] Environment set. Searching for your source files...

:: 2. Find ONLY project files, EXCLUDING compiler/gnuplot folders
set "SRCS="
for /R "%~dp0" %%f in (*.cpp) do (
    set "FILEPATH=%%f"
    :: This logic ignores any .cpp files found inside mingw64 or gnuplot
    echo !FILEPATH! | findstr /i "mingw64 gnuplot build" >nul
    if errorlevel 1 (
        set "SRCS=!SRCS! "%%f""
    )
)

echo.
echo Compiling: !SRCS!

:: 3. The Compile Command
:: -static-libgcc -static-libstdc++ ensures it runs on any PC without extra DLLs
:: -I"%~dp0include" tells g++ to look for the 'nlohmann' folder here
g++ -O3 -static -static-libgcc -static-libstdc++ -I"%~dp0include" !SRCS! -o "%~dp0pricer.exe" -lwininet

if %errorlevel% == 0 (
    echo [SUCCESS] pricer.exe created.
    "%~dp0pricer.exe"
) else (
    echo [ERROR] Compilation failed.
)
pause