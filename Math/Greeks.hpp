#ifdef GREEKS_HPP
#define GREEKS_HPP

#include <vector>
double calculate_delta(double S0, double r, double sigma, double T, int steps, double K, double(*f_payoff)(std::vector<double>,double),)
#endif 
