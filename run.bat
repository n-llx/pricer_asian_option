echo.
echo Compiling with OpenMP Optimization...
g++ -O3 -fopenmp main/main.cpp Math/StochasticModel.cpp Instruments/Payoff.cpp -o pricer.exe
pause
