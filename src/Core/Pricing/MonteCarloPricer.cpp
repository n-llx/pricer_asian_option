#include "MonteCarloPricer.hpp"
#include <iostream>
#include <cmath>
#include <omp.h>

namespace Core {

    MonteCarloPricer::MonteCarloPricer(int simulations) : N(simulations) {}
    
    // specialized for BS to access r
    double run_simulation_bs(const BlackScholesModel& model, const Payoff& payoff, double T, int steps, int N) {
        double sum = 0.0;
        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < N; ++i) {
            auto path = model.generatePath(T, steps);
            sum += payoff(path);
        }
        return sum / N * std::exp(-model.getR() * T);
    }

    PricingResult MonteCarloPricer::price(const BlackScholesModel& model, const Payoff& payoff, double T, int steps) const {
        PricingResult result;
        double S0 = model.getS0();
        double r = model.getR();
        double sigma = model.getSigma();

        // Base Price
        result.price = run_simulation_bs(model, payoff, T, steps, N);

        // Finite Difference Steps
        double h_S = S0 * 0.01;
        double h_sigma = sigma * 0.01;
        double h_T = T * 0.01; // For Theta
        double h_r = 0.0001;   // 1 bp for Rho

        // Delta & Gamma
        BlackScholesModel upS(S0 + h_S, r, sigma);
        BlackScholesModel dnS(S0 - h_S, r, sigma);
        double pUp = run_simulation_bs(upS, payoff, T, steps, N);
        double pDn = run_simulation_bs(dnS, payoff, T, steps, N);
        
        result.delta = (pUp - pDn) / (2 * h_S);
        result.gamma = (pUp - 2 * result.price + pDn) / (h_S * h_S);

        // Vega
        BlackScholesModel upVol(S0, r, sigma + h_sigma);
        BlackScholesModel dnVol(S0, r, sigma - h_sigma);
        double pUpVol = run_simulation_bs(upVol, payoff, T, steps, N);
        double pDnVol = run_simulation_bs(dnVol, payoff, T, steps, N);
        result.vega = (pUpVol - pDnVol) / (2 * h_sigma);

        // Theta (Time Decay - usually negative)
        // We simulate with T-h_T (option closer to maturity)
        // Note: steps should adjust? For simplicity keep steps same, dt changes.
        if (T > h_T) {
             double pTime = run_simulation_bs(model, payoff, T - h_T, steps, N);
             result.theta = (pTime - result.price) / h_T;
        } else {
            result.theta = 0.0;
        }

        // Rho
        BlackScholesModel upR(S0, r + h_r, sigma);
        BlackScholesModel dnR(S0, r - h_r, sigma);
        double pUpR = run_simulation_bs(upR, payoff, T, steps, N);
        double pDnR = run_simulation_bs(dnR, payoff, T, steps, N);
        result.rho = (pUpR - pDnR) / (2 * h_r);

        return result;
    }

}
