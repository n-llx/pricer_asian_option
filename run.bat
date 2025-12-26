echo.
echo Compiling with OpenMP Optimization...
g++ -O3 -fopenmp main/main.cpp Math/StochasticModel.cpp Math/Greeks.cpp Instruments/Payoff.cpp -o pricer.exe
pause
