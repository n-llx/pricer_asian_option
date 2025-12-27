#ifndef GREEKS_HPP
#define GREEKS_HPP
#include <vector>
double calculate_delta(const std::vector<std::vector<double>>& call_results, int i, int j, double s_step);
double calculate_vega(const std::vector<std::vector<double>>& call_results, int i, int j, double s_step);
#endif