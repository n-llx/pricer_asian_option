#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <vector>
double payoff_eu_call(std::vector<double> path, double K);
double payoff_eu_put(std::vector<double> path, double K);
double payoff_as_call(std::vector<double> path, double K);
double payoff_as_put(std::vector<double> path, double K);
#endif 
