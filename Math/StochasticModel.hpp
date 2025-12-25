#ifndef STOCHASTIC_MODEL_HPP
#define STOCHASTIC_MODEL_HPP
#include <vector>

std::vector<double> generate_price_path(double S0, double r, double sigma, double T, int steps);

#endif 

