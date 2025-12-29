#pragma once

#include <vector>
#include <string>
#include "../MarketData/MarketData.hpp"

class PricerApp {
public:
    void run();

private:
    void runManualMode();
    void runAutomaticMode();
    void computeAndPlot(int N, double S0, double r, double sigma, double T, int steps, double K, bool isAutoMode);
};
