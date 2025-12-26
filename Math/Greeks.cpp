#include "Payoff.hpp"
#include "Payoff.cpp"
#include "StochasticModel.hpp"
#include "StochasticModel.cpp"


using namespace std;

double calculate_delta(double S0, double r, double sigma, double T, int steps, double K, double(*f_payoff)(std::vector<double>,double), int N){
    double pi = monte_carlo(N, S0, r, sigma, T, steps, f_payoff, K);
    double epsilon = 1e-5*pi;
    double pi_up = monte_carlo(N, S0 + epsilon/2, r, sigma, T, steps, f_payoff, K);
    double pi_down = monte_carlo(N, S0 - epsilon/2, r, sigma, T, steps, f_payoff, K);
    return (pi_up - pi_down)/epsilon;
}