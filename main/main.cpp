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
    double S0 = 100;
    double r = 0.03;
    double sigma = .25;
    double T = 1;
    int steps = 20;
    int N = 1000;
    double K = 100;
    int grid_size = 20;
    
    
    //cout << "Monte carlo with strike "<<K<<"$ and "<<N<<" paths simulated :"<<"\n";
    //cout<<"Asian Call: "<<monte_carlo(N,S0,r, sigma,T, steps, &payoff_as_call, K )<<"\n";
    //cout<<"Asian Put:"<<monte_carlo(N,S0,r, sigma,T, steps, &payoff_as_put, K )<<"\n"<<"\n";
    
    
    double sigma_start = 0.05, sigma_end = 0.50;
    double S0_start = 50.0, S0_end = 150.0;
    
    FILE *gnuplotPipe = _popen("gnuplot -persist", "w");
    if (!gnuplotPipe) {
        std::cerr << "CRITICAL ERROR: Gnuplot not found in system PATH." << std::endl;
        std::cerr << "Please run 'setup.bat' first to install dependencies." << std::endl;
        return -1;
    }
    fprintf(gnuplotPipe, "set title 'Asian Call Option Price (Monte Carlo)'\n");
    fprintf(gnuplotPipe, "set dgrid3d %d,%d\n", grid_size, grid_size); // Create a grid
    fprintf(gnuplotPipe, "set hidden3d\n"); // Hide lines behind the surface
    fprintf(gnuplotPipe, "set xlabel 'Underlying Price (S0)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Volatility (Sigma)'\n");
    fprintf(gnuplotPipe, "set zlabel 'Price'\n");
    fprintf(gnuplotPipe, "splot '-' using 1:2:3 with lines palette\n"); // 3D Plot command
    
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