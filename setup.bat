@echo off
setlocal
echo Checking system dependencies...

:: 1. Check for Winget and install if missing
echo Checking for Winget...
where winget >nul 2>nul
if %errorlevel% neq 0 (
    echo [INFO] Winget not found. Attempting to bootstrap Winget...
    echo [INFO] Downloading Microsoft.DesktopAppInstaller bundle...
    
    :: Use PowerShell to download the latest bundle and its dependencies
    powershell -Command "Invoke-WebRequest -Uri https://github.com/microsoft/winget-cli/releases/latest/download/Microsoft.DesktopAppInstaller_8wekyb3d8bbwe.msixbundle -OutFile winget.msixbundle"
    
    if exist winget.msixbundle (
        echo [INFO] Installing Winget bundle...
        powershell -Command "Add-AppxPackage -Path winget.msixbundle"
        del winget.msixbundle
        echo [SUCCESS] Winget installed.
        echo [NOTE] You may need to restart this script for Winget to be recognized.
    ) else (
        echo [ERROR] Could not download Winget automatically.
        echo Please install 'App Installer' from the Microsoft Store.
        pause
        exit /b
    )
) else (
    echo [OK] Winget is available.
)

:: 2. Check for Gnuplot
echo Checking for Gnuplot...
where gnuplot >nul 2>nul
if %errorlevel% == 0 (
    echo [OK] Gnuplot is already installed.
) else (
    echo [INFO] Gnuplot not found. Installing via Winget...
    winget install gnuplot.gnuplot --source winget --accept-source-agreements --accept-package-agreements
    
    if %errorlevel% neq 0 (
        echo [ERROR] Winget install failed.
        echo Try manual install: http://www.gnuplot.info/
        pause
        exit /b
    )
    echo [SUCCESS] Gnuplot installed.
)

:: 3. Compile code
echo.
echo Compiling pricer...
g++ main/main.cpp Math/StochasticModel.cpp Instruments/Payoff.cpp -o pricer.exe

if %errorlevel% == 0 (
    echo [SUCCESS] The program can be run with 'pricer.exe'. !
) else (
    echo [ERROR] Compilation failed.
)

pause
endlocal