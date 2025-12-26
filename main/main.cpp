#include <iostream>
#include <clocale>
#include <omp.h> 
#include "../Math/StochasticModel.hpp"
#include "../Instruments/Payoff.hpp"
#include <vector>
#include <cstdio> 
#include <cmath>
#include <random>
#include <algorithm>
#include <iomanip> // For progress bar formatting



double monte_carlo(int N, double S0, double r, double sigma, double T, int steps, double(*f_payoff)(std::vector<double>,double), double K ){
    double sum = 0.0;
    for (int i = 0; i < N; i++){
        std::vector<double> path = generate_price_path(S0,r,sigma,T,steps);
        double payoff = f_payoff(path,K);
        sum = sum + payoff;
        }
    return (sum / N)*std::exp(-r*T);
    }


int main(){
    std::setlocale(LC_NUMERIC, "C");
    int grid_size = 50;
    double S0_input, r, sigma_input, T, K;
    int steps, N;
    int total_points = (grid_size + 1) * (grid_size + 1);
    int completed_points = 0;

    std::cout << "\\--- Asian Options Monte Carlo Pricer ---//" << std::endl;
    std::cout << "Enter S0: "; std::cin >> S0_input;
    std::cout << "Enter r: "; std::cin >> r;
    std::cout << "Enter sigma: "; std::cin >> sigma_input;
    std::cout << "Enter T: "; std::cin >> T;
    std::cout << "Enter K: "; std::cin >> K;
    std::cout << "Enter steps: "; std::cin >> steps;
    std::cout << "Enter N: "; std::cin >> N;
    
    std::cout << "Monte carlo with strike "<<K<<"$ and "<<N<<" paths simulated :"<<"\n";
    std::cout<<"Asian Call: "<<monte_carlo(N,S0_input,r, sigma_input,T, steps, &payoff_as_call, K )<<"\n";
    std::cout<<"Asian Put:"<<monte_carlo(N,S0_input,r, sigma_input,T, steps, &payoff_as_put, K )<<"\n"<<"\n";
    
    
    double sigma_start = 0.05, sigma_end = 0.50;
    double S0_start = 50.0, S0_end = 150.0;
    double s_step = (S0_end - S0_start) / grid_size;
    double vol_step = (sigma_end - sigma_start) / grid_size;
    int completed = 0;

    // 1. DATA STORAGE: 2D vectors to store results safely during parallel computation
    std::vector<std::vector<double>> call_results(grid_size + 1, std::vector<double>(grid_size + 1));
    std::vector<std::vector<double>> put_results(grid_size + 1, std::vector<double>(grid_size + 1));

    std::cout << "\nCalculating Call and Put surfaces using " << omp_get_max_threads() << " threads...\n";

    // --- Parallel Calculation with Progress Bar ---
    #pragma omp parallel
    {
        // Get the thread ID so only the first thread prints the UI
        int thread_id = omp_get_thread_num();

        #pragma omp for collapse(2)
        for (int i = 0; i <= grid_size; ++i) {
            for (int j = 0; j <= grid_size; ++j) {
                double current_sigma = sigma_start + i * vol_step;
                double current_S0 = S0_start + j * s_step;
                
                call_results[i][j] = monte_carlo(N, current_S0, r, current_sigma, T, steps, &payoff_as_call, K);
                put_results[i][j] = monte_carlo(N, current_S0, r, current_sigma, T, steps, &payoff_as_put, K);

                #pragma omp atomic
                completed++;

                // Only thread 0 updates the bar to avoid "nesting" errors
                if (thread_id == 0 && completed % 10 == 0) {
                    float progress = (float)completed / total_points;
                    int barWidth = 40;
                    std::cout << "\rProgress: [";
                    int pos = barWidth * progress;
                    for (int k = 0; k < barWidth; ++k) {
                        if (k < pos) std::cout << "=";
                        else if (k == pos) std::cout << ">";
                        else std::cout << " ";
                    }
                    std::cout << "] " << int(progress * 100.0) << "% " << std::flush;
                }
            }
        }
    }
    std::cout << "\n\nCalculations complete. Sending data to Gnuplot..." << std::endl;

    // --- Gnuplot Plotting ---
    FILE *pipeCall = _popen("gnuplot -persist", "w");
    FILE *pipePut = _popen("gnuplot -persist", "w");

    if (pipeCall && pipePut) {
        // Common setup string to avoid repetition
        const char* commonSetup = 
            "set pm3d\n"
            "set hidden3d\n"
            "set xlabel 'Spot Price (S0)'\n"
            "set ylabel 'Volatility (sigma)'\n"
            "set zlabel 'Option Price'\n"
            "set dgrid3d %d,%d\n";

        // --- Setup Call Window (Window 0) ---
        fprintf(pipeCall, "set term wxt 0 title 'Asian Call Surface' enhanced noraise\n");
        fprintf(pipeCall, commonSetup, grid_size + 1, grid_size + 1);
        // Dynamic Title for Call
        fprintf(pipeCall, "set title 'Asian Call Price Surface\\n{/*0.8 K (Strike, unit currency)=%.2f, r=%.2f, T(years)=%.2f, N=%d}'\n", K, r, T, N);
        fprintf(pipeCall, "splot '-' u 1:2:3 with pm3d title 'Call Price'\n");

        // --- Setup Put Window (Window 1) ---
        fprintf(pipePut, "set term wxt 1 title 'Asian Put Surface' enhanced noraise\n");
        fprintf(pipePut, commonSetup, grid_size + 1, grid_size + 1);
        // Dynamic Title for Put
        fprintf(pipePut, "set title 'Asian Put Price Surface\\n{/*0.8 K (Strike, unit currency)=%.2f, r=%.2f, T(years)=%.2f, N=%d}'\n", K, r, T, N);
        fprintf(pipePut, "splot '-' u 1:2:3 with pm3d title 'Put Price'\n");

        // --- Data Transmission ---
        for (int i = 0; i <= grid_size; ++i) {
            for (int j = 0; j <= grid_size; ++j) {
                double current_sigma = sigma_start + i * vol_step;
                double current_S0 = S0_start + j * s_step;
                fprintf(pipeCall, "%f %f %f\n", current_S0, current_sigma, call_results[i][j]);
                fprintf(pipePut, "%f %f %f\n", current_S0, current_sigma, put_results[i][j]);
            }
            fprintf(pipeCall, "\n");
            fprintf(pipePut, "\n");
        }
        
        fprintf(pipeCall, "e\n");
        fprintf(pipePut, "e\n");
        fflush(pipeCall);
        fflush(pipePut);
    }

    _pclose(pipeCall);
    _pclose(pipePut);
    return 0;
}