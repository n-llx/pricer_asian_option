#ifndef STOCHASTIC_MODEL_HPP
#define STOCHASTIC_MODEL_HPP
#include <vector>
#include <random>

void generate_price_path(double S0, double r, double sigma, double T, int steps, std::vector<double>& path, std::mt19937& gen);
double monte_carlo(int N, double S0, double r, double sigma, double T, int steps, double (*f_payoff)(const std::vector<double>&, double), double K, unsigned int base_seed);
#endif
