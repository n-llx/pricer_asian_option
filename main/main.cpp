#include <iostream>
#include "../Math/StochasticModel.hpp"
#include "../Instruments/Payoff.hpp"
#include <vector>
#include <cstdio> 
#include <cmath>
#include <random>
#include <algorithm>

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
int grid_size = 20;
    double S0_input, r, sigma_input, T, K;
    int steps, N;

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
    
    FILE *gnuplotPipe = _popen("gnuplot -persist", "w");
    if (!gnuplotPipe) {
        std::cerr << "CRITICAL ERROR: Gnuplot not found in system PATH." << std::endl;
        std::cerr << "Please run 'setup.bat' first to install dependencies." << std::endl;
        return -1;
    }
    fprintf(gnuplotPipe, "set terminal wxt enhanced\n");
    fprintf(gnuplotPipe, "set mouse\n");
    fprintf(gnuplotPipe, "set title 'Asian Call Option Price with \\n{/*0.8 K=%.2f, r=%.2f, T=%.2f}'\n", K, r, T);
    fprintf(gnuplotPipe, "set dgrid3d %d,%d\n", grid_size, grid_size); // Create a grid
    fprintf(gnuplotPipe, "set hidden3d\n"); // Hide lines behind the surface
    fprintf(gnuplotPipe, "set xlabel 'Underlying Price (S0)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Volatility (Sigma)'\n");
    fprintf(gnuplotPipe, "set zlabel 'Price'\n");
    fprintf(gnuplotPipe, "set pm3d at s\n");
    fprintf(gnuplotPipe, "set hidden3d\n");
    fprintf(gnuplotPipe, "splot '-' using 1:2:3 with pm3d notitle\n");
    
    double s_step = (S0_end - S0_start) / grid_size;
    double vol_step = (sigma_end - sigma_start) / grid_size;
    
    std::cout << "Calculating and plotting..." << std::endl;
    
    for (int i = 0; i <= grid_size; ++i) {
        double sigma = sigma_start + i * vol_step;
        
        for (int j = 0; j <= grid_size; ++j) {
            double S0 = S0_start + j * s_step;
            
            // Calculate price
            double price = monte_carlo(N, S0, r, sigma, T, steps, &payoff_as_call, K);
            
            // Send x, y, z coordinates to Gnuplot
            fprintf(gnuplotPipe, "%f %f %f\n", S0, sigma, price);
        }
    }
    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);
    pclose(gnuplotPipe);
    
    std::cout << "Done." << std::endl;
    
    
    
    return 0;
}