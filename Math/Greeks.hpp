#ifndef GREEKS_HPP
#define GREEKS_HPP
#include <vector>
double calculate_delta(const std::vector<std::vector<double>> &call_results, int i, int j, double s_step);
double calculate_vega(const std::vector<std::vector<double>> &call_results, int i, int j, double s_step);
double calculate_gamma(const std::vector<std::vector<double>> &call_results, int i, int j, double s_step);
double calculate_rho(const std::vector<std::vector<double>> &call_results, const std::vector<std::vector<double>> &call_results_r_plus, int i, int j, double r_step);
double calculate_theta(const std::vector<std::vector<double>> &call_results, const std::vector<std::vector<double>> &call_results_t_minus, int i, int j, double t_step);
#endif