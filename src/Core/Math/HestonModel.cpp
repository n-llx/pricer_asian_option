#include "HestonModel.hpp"
#include <cmath>
#include <random>
#include <algorithm>

namespace Core {

    HestonModel::HestonModel(double S0, double r, double v0, double kappa, double theta, double xi, double rho)
        : S0(S0), r(r), v0(v0), kappa(kappa), theta(theta), xi(xi), rho(rho) {}

    std::vector<double> HestonModel::generatePath(double T, int steps) const {
        std::vector<double> path(steps + 1);
        double dt = T / static_cast<double>(steps);
        double sqrt_dt = std::sqrt(dt);

        static thread_local std::random_device rd;
        static thread_local std::mt19937 gen(rd());
        std::normal_distribution<double> dist(0.0, 1.0);

        path[0] = S0;
        double v = v0;

        for (int i = 1; i <= steps; ++i) {
            double Z1 = dist(gen);
            double Z2 = dist(gen);
            double Z_S = Z1;
            double Z_v = rho * Z1 + std::sqrt(1.0 - rho * rho) * Z2;

            // Euler-Maruyama for S, Milstein or Full Truncation for v
            // Using Full Truncation for v to ensure positivity
            double v_plus = std::max(v, 0.0);
            
            double dS = r * path[i-1] * dt + std::sqrt(v_plus) * path[i-1] * sqrt_dt * Z_S;
            double dv = kappa * (theta - v_plus) * dt + xi * std::sqrt(v_plus) * sqrt_dt * Z_v;

            path[i] = path[i-1] + dS;
            v += dv; 
        }
        return path;
    }

}
