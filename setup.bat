@echo off
echo Checking for Gnuplot...

:: Check if gnuplot is already installed
where gnuplot >nul 2>nul
if %errorlevel% == 0 (
    echo Gnuplot is already installed.
) else (
    echo Gnuplot not found. Installing via Winget...
    :: This uses the official Windows Package Manager
    winget install gnuplot.gnuplot --source winget
    if %errorlevel% neq 0 (
        echo Failed to install Gnuplot automatically. 
        echo Please install it manually from http://www.gnuplot.info/
        pause
        exit /b
    )
    echo Gnuplot installed successfully! 
    echo NOTE: You may need to restart your terminal or VS Code for changes to take effect.
)

echo.
echo Compiling the C++ Asian Option Pricer...
g++ main/main.cpp Math/StochasticModel.cpp Instruments/Payoff.cpp -o pricer.exe

if %errorlevel% == 0 (
    echo Compilation successful! Running program...
    .\pricer.exe
) else (
    echo Compilation failed.
)
pause