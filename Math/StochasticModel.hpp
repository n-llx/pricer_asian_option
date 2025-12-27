#ifndef STOCHASTIC_MODEL_HPP
#define STOCHASTIC_MODEL_HPP
#include <vector>

std::vector<double> generate_price_path(double S0, double r, double sigma, double T, int steps);
double monte_carlo(int N, double S0, double r, double sigma, double T, int steps, double (*f_payoff)(std::vector<double>, double), double K, unsigned int base_seed = 42);
#endif
