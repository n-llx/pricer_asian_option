#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <vector>
double payoff_eu_call(const std::vector<double>& path, double K);
double payoff_eu_put(const std::vector<double>& path, double K);
double payoff_as_call(const std::vector<double>& path, double K);
double payoff_as_put(const std::vector<double>& path, double K);
#endif 
