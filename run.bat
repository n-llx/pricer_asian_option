g++ main/main.cpp Math/StochasticModel.cpp Instruments/Payoff.cpp -o pricer.exe
if %errorlevel% eq 0 (
    .\pricer.exe
)
