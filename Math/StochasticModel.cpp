#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;

void generate_price_path(double S0, double r, double sigma, double T, int steps, vector<double>& path, mt19937& gen)
{
    // path is assumed to be already resized to steps + 1
    double dt = T / static_cast<double>(steps);
    double drift = (r - 0.5 * sigma * sigma) * dt;
    double vol_sqrt_dt = sigma * sqrt(dt);

    normal_distribution<double> dist(0.0, 1.0);
    path[0] = S0;

    for (int i = 1; i <= steps; ++i)
    {
        double Z = dist(gen);
        path[i] = path[i - 1] * exp(drift + vol_sqrt_dt * Z);
    }
}

double monte_carlo(int N, double S0, double r, double sigma, double T, int steps, 
                   double (*f_payoff)(const std::vector<double>&, double), double K, 
                   unsigned int base_seed) 
{
    mt19937 gen(base_seed); 
    double sum = 0.0;
    std::vector<double> path(steps + 1); // Allocation unique
    
    for (int i = 0; i < N; i++)
    {
        generate_price_path(S0, r, sigma, T, steps, path, gen); // Réutilisation
        sum += f_payoff(path, K);
    }
    return (sum / N) * std::exp(-r * T);
}