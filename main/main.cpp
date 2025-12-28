#include <iostream>
#include <clocale>
#include <clocale>
#include "../Math/StochasticModel.hpp"
#include "../Instruments/Payoff.hpp"
#include "../Math/Greeks.hpp"
#include <vector>
#include <cstdio>
#include <cmath>
#include <random>
#include <algorithm>
#include <iomanip> // for progress bar

#include "../Graphics/plot.hpp"

int main()
{
    std::setlocale(LC_NUMERIC, "C");
    int grid_size = 50;
    double S0_input, r, sigma_input, T, K;
    int steps, N;
    int total_points = (grid_size + 1) * (grid_size + 1);
    int completed_points = 0;

    std::cout << "||--- Asian Options Monte Carlo Pricer ---||" << std::endl;
    std::cout << "Enter S0 (between 50 and 150): ";
    std::cin >> S0_input;
    std::cout << "Enter r: ";
    std::cin >> r;
    std::cout << "Enter sigma (between 0.05 and 0.5): ";
    std::cin >> sigma_input;
    std::cout << "Enter T: ";
    std::cin >> T;
    std::cout << "Enter K: ";
    std::cin >> K;
    std::cout << "Enter steps: ";
    std::cin >> steps;
    std::cout << "Enter N: ";
    std::cin >> N;

    std::cout << "Monte carlo with strike " << K << "$ and " << N << " paths simulated :" << "\n";
    // here the prices are calculated using random seeds: confidence interval depends on N
    std::random_device rd;
    unsigned int random_seed = rd();
    std::cout << "Asian Call: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_call, K, random_seed) << "\n";
    std::cout << "Asian Put:" << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_put, K, random_seed) << "\n"
              << "\n";

    double sigma_start = 0.05, sigma_end = 0.50;
    double S0_start = 50.0, S0_end = 150.0;
    double s_step = (S0_end - S0_start) / grid_size;
    double vol_step = (sigma_end - sigma_start) / grid_size;
    int completed = 0;

    // start of the surfaces calculation
    std::vector<std::vector<double>> call_results(grid_size + 1, std::vector<double>(grid_size + 1));
    std::vector<std::vector<double>> put_results(grid_size + 1, std::vector<double>(grid_size + 1));
    std::vector<std::vector<double>> call_delta_call_results(grid_size + 1, std::vector<double>(grid_size + 1));
    std::vector<std::vector<double>> call_vega_call_results(grid_size + 1, std::vector<double>(grid_size + 1));

    std::cout << "\nCalculating Call, Put and Delta surfaces "<< std::endl;
    for (int i = 0; i <= grid_size; ++i) {
        for (int j = 0; j <= grid_size; ++j) {
        double current_sigma = sigma_start + i * vol_step;
        double current_S0 = S0_start + j * s_step;

        // random seed is fixed to 42 for smoothness of the surfaces
        call_results[i][j] = monte_carlo(N, current_S0, r, current_sigma, T, steps, &payoff_as_call, K, 42);
        // put surface is bootstrapped using put call parity for options: C - P = S0 - K exp(-rT)
        put_results[i][j] = call_results[i][j] - current_S0 + K * std::exp(-r * T);
        completed++;
        if (completed % 10 == 0 || completed == total_points) {
            float progress = (float)completed / total_points;
            int barWidth = 40;
            int pos = barWidth * progress;
            std::cout << "\rProgress: [";
            for (int k = 0; k < barWidth; ++k) {
                if (k < pos) std::cout << "=";
                else if (k == pos) std::cout << ">";
                else std::cout << " ";
            }
            std::cout << "] " << int(progress * 100.0) << "% " << std::flush;
            }
        }
    }
    std::cout << "\nCalculations complete!" << std::endl;
    for (int i = 0; i <= grid_size; ++i)
    {
        for (int j = 0; j <= grid_size; ++j)
        {
            // delta calculation is bootrstapped using the call price surface
            call_delta_call_results[i][j] = calculate_delta(call_results, i, j, s_step);
        }
    }

    for (int i = 0; i <= grid_size; ++i)
    {
        for (int j = 0; j <= grid_size; ++j)
        {
            // vega calculation is bootrstapped using the call price surface
            call_vega_call_results[i][j] = calculate_vega(call_results, i, j, s_step);
        }
    }

    // delta of the inputed option is given printed
    std::cout << "\n\nDelta of the option calculated:" << call_delta_call_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << std::endl;
    std::cout << "\n\nVega of the option calculated:" << call_vega_call_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << std::endl;
    std::cout << "\n\nCalculations complete. Sending data to Gnuplot..." << std::endl;

    // Delegate plotting to Graphics/plot.cpp (single-surface calls)
    plot_surface(grid_size, call_results, S0_start, s_step, sigma_start, vol_step,
                "Asian Call Price Surface", "Option Price", K, r, T, N, 0);
    plot_surface(grid_size, put_results, S0_start, s_step, sigma_start, vol_step,
                "Asian Put Price Surface", "Option Price", K, r, T, N, 1);
    plot_surface(grid_size, call_delta_call_results, S0_start, s_step, sigma_start, vol_step,
                "Asian Call Delta Surface", "Delta", K, r, T, N, 2);
    plot_surface(grid_size, call_vega_call_results, S0_start, s_step, sigma_start, vol_step,
                "Asian Call Vega Surface", "Vega", K, r, T, N, 3);

    return 0;
}