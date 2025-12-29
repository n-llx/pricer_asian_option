#ifndef GREEKS_HPP
#define GREEKS_HPP
#include <vector>
double calculate_delta(const std::vector<std::vector<double>> &call_results, int i, int j, double s_step);
double calculate_vega(const std::vector<std::vector<double>> &call_results, int i, int j, double s_step);
double calculate_gamma(const std::vector<std::vector<double>> &call_results, int i, int j, double s_step);
void gamma_plot(const std::vector<std::vector<double>> &call_results, int grid_size, double s_step,
                double S0_start, double sigma_start, double vol_step,
                double K, double r, double T, int N);
#endif