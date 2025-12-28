#!/bin/bash
# Move to the script's directory
cd "$(dirname "$0")"

# 1. Define the base path for your portable Gnuplot
# Make sure this matches exactly where you unzipped Gnuplot
GP_BASE="$PWD/gnuplot_mac/gnuplot/6.0.4"

# 1. Point to the portable Mac Gnuplot
export PATH="$GP_BASE/bin:$PATH"
export DYLD_LIBRARY_PATH="$GP_BASE/lib:$GP_BASE/libexec:$DYLD_LIBRARY_PATH"
export GNUPLOT_LIB="$PWD/gnuplot_mac/share/gnuplot/6.0.4/share"
export QT_QPA_PLATFORM_PLUGIN_PATH="$GP_BASE/libexec/qtplugins"
export PATH="$GP_BASE/bin:$PATH"
export QT_QPA_PLATFORM=cocoa
echo "--- Portable Asian Option Pricer (macOS) ---"

# 2. Check for Compiler
if ! command -v g++ &> /dev/null; then
    echo "[INFO] No compiler found. Opening installer..."
    xcode-select --install
    exit 1
fi

# 3. Check for Local Gnuplot (Updated path to match Step 1)
if [ ! -f "$GP_BASE/bin/gnuplot" ]; then
    echo "[ERROR] Portable Gnuplot not found at: $GP_BASE/bin/gnuplot"
    echo "Please check that you unzipped the files correctly into gnuplot_mac"
    exit 1
fi

# 4. Find and Compile
# We ignore the tool folders so we don't compile the compiler's own code
SRCS=$(find . -maxdepth 3 -name "*.cpp" ! -path "*/mingw64/*" ! -path "*/gnuplot/*" ! -path "*/gnuplot_mac/*")

echo "[INFO] Compiling..."
g++ -O3 -std=c++17 -Iinclude $SRCS -o pricer_mac

if [ $? -eq 0 ]; then
    echo "[SUCCESS] Running program..."
    # Ensure the compiled binary has execution rights
    chmod +x ./pricer_mac
    ./pricer_mac
else
    echo "[ERROR] Compilation failed."
fi