#include <iostream>
#include <clocale>
#include <omp.h>
#include "../Math/StochasticModel.hpp"
#include "../Instruments/Payoff.hpp"
#include "../Math/Greeks.hpp"
#include <vector>
#include <cstdio>
#include <cmath>
#include <random>
#include <algorithm>
#include <iomanip> // for progress bar


int main()
{
    std::setlocale(LC_NUMERIC, "C");

    int grid_size = 50;
    double S0_input, r, sigma_input, T, K;
    int steps, N;
    int total_points = (grid_size + 1) * (grid_size + 1);
    int completed_points = 0;

    std::cout << "||--- Asian Options Monte Carlo Pricer ---||" << std::endl;
    std::cout << "Enter S0: ";
    std::cin >> S0_input;
    std::cout << "Enter r: ";
    std::cin >> r;
    std::cout << "Enter sigma: ";
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

    //start of the surfaces calculation
    std::vector<std::vector<double>> call_results(grid_size + 1, std::vector<double>(grid_size + 1));
    std::vector<std::vector<double>> put_results(grid_size + 1, std::vector<double>(grid_size + 1));
    std::vector<std::vector<double>> call_delta_call_results(grid_size + 1, std::vector<double>(grid_size + 1));

    std::cout << "\nCalculating Call, Put and Delta surfaces ";
        for (int i = 0; i <= grid_size; ++i)
        {
            for (int j = 0; j <= grid_size; ++j)
            {
                double current_sigma = sigma_start + i * vol_step;
                double current_S0 = S0_start + j * s_step;

                //random seed is fixed to 42 for smoothness of the surfaces
                call_results[i][j] = monte_carlo(N, current_S0, r, current_sigma, T, steps, &payoff_as_call, K, 42);
                // put surface is bootstrapped using put call parity for options: C - P = S0 - K exp(-rT)
                put_results[i][j] = call_results[i][j] - current_S0 + K * std::exp(-r * T);
                completed++;

                if (completed % 20 == 0)
                {
                    float progress = (float)completed / total_points;
                    int barWidth = 40;
                    std::cout << "\rProgress: [";
                    int pos = barWidth * progress;
                    for (int k = 0; k < barWidth; ++k)
                    {
                        if (k < pos)
                            std::cout << "=";
                        else if (k == pos)
                            std::cout << ">";
                        else
                            std::cout << " ";
                    }
                    std::cout << "] " << int(progress * 100.0) << "% " << std::flush;
                }
            }
        }
        for (int i = 0; i <= grid_size; ++i) {
            for (int j = 0; j <= grid_size; ++j) {
                // delta calculation is bootrstapped using the call price surface
                call_delta_call_results[i][j] = calculate_delta(call_results, i, j, s_step);
             }
        }
    std::cout << "\n\nCalculations complete. Sending data to Gnuplot..." << std::endl;

    // --- Gnuplot Plotting ---
    FILE *pipeCall = _popen("gnuplot -persist", "w");
    FILE *pipePut = _popen("gnuplot -persist", "w");
    FILE *pipeDeltaCall = _popen("gnuplot -persist", "w");

    if (pipeCall && pipePut && pipeDeltaCall)
    {
        // Common setup string to avoid repetition
        const char *commonSetup =
            "set pm3d at s\n"
            "set hidden3d\n"
            "set xlabel 'Spot Price (S0)' offset 0,-1\n"   // Move label down slightly
            "set ylabel 'Volatility (sigma)' offset 2,0\n" // Move label right slightly
            "set view 60, 30, 1.0, 1.1\n"                  // Adjust view scale to make room
            "set dgrid3d %d,%d\n";

        // --- Setup Call Window (Window 0) ---
        fprintf(pipeCall, "set term wxt 0 title 'Asian Call Surface' enhanced noraise\n");
        fprintf(pipeCall, commonSetup, grid_size + 1, grid_size + 1);
        fprintf(pipeCall, "set pm3d at s\n");                          // Surface color
        fprintf(pipeCall, "set zlabel 'Option Price' offset 1,1,0\n"); // Z-axis label with offset
        // Dynamic Title for Call
        fprintf(pipeCall, "set title 'Asian Call Price Surface\\n{/*0.8 K=%.2f, r=%.2f, T=%.2f, N=%d}'\n", K, r, T, N);
        fprintf(pipeCall, "splot '-' u 1:2:3 with pm3d title 'Call Price'\n");

        // --- Setup Put Window (Window 1) ---
        fprintf(pipePut, "set term wxt 1 title 'Asian Put Surface' enhanced noraise\n");
        fprintf(pipePut, commonSetup, grid_size + 1, grid_size + 1);
        fprintf(pipePut, "set pm3d at s\n");                          // Surface color
        fprintf(pipePut, "set zlabel 'Option Price' offset 1,1,0\n"); // Z-axis label with offset
        // Dynamic Title for Put
        fprintf(pipePut, "set title 'Asian Put Price Surface\\n{/*0.8 K=%.2f, r=%.2f, T=%.2f, N=%d}'\n", K, r, T, N);
        fprintf(pipePut, "splot '-' u 1:2:3 with pm3d title 'Put Price'\n");

        // Setuo Delta Call Window (Window 2)
        fprintf(pipeDeltaCall, "set term wxt 2 title 'Asian Call Delta Surface' enhanced noraise\n");
        fprintf(pipeDeltaCall, commonSetup, grid_size + 1, grid_size + 1);
        fprintf(pipeDeltaCall, "set pm3d at s\n");                   // Surface color
        fprintf(pipeDeltaCall, "set zlabel 'Delta' offset 1,1,0\n"); // Z-axis label with offset
        // Dynamic Title for Call Delta
        fprintf(pipeDeltaCall, "set title 'Asian Call Delta Surface\\n{/*0.8 K=%.2f, r=%.2f, T=%.2f, N=%d}'\n", K, r, T, N);
        fprintf(pipeDeltaCall, "splot '-' u 1:2:3 with pm3d title 'Call Delta'\n");

        // --- Data Transmission ---
        for (int i = 0; i <= grid_size; ++i)
        {
            for (int j = 0; j <= grid_size; ++j)
            {
                double current_sigma = sigma_start + i * vol_step;
                double current_S0 = S0_start + j * s_step;
                fprintf(pipeCall, "%f %f %f\n", current_S0, current_sigma, call_results[i][j]);
                fprintf(pipePut, "%f %f %f\n", current_S0, current_sigma, put_results[i][j]);
                fprintf(pipeDeltaCall, "%f %f %f\n", current_S0, current_sigma, call_delta_call_results[i][j]);
            }
            fprintf(pipeCall, "\n");
            fprintf(pipePut, "\n");
            fprintf(pipeDeltaCall, "\n");
        }

        fprintf(pipeCall, "e\n");
        fprintf(pipePut, "e\n");
        fprintf(pipeDeltaCall, "e\n");
        fflush(pipeCall);
        fflush(pipePut);
        fflush(pipeDeltaCall);
    }

    _pclose(pipeCall);
    _pclose(pipePut);
    _pclose(pipeDeltaCall);
    return 0;
}