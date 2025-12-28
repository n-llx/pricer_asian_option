#include "StochasticModel.hpp"
#include <cmath>
#include <random>

namespace Core {

    BlackScholesModel::BlackScholesModel(double S0, double r, double sigma)
        : S0(S0), r(r), sigma(sigma) {}

    std::vector<double> BlackScholesModel::generatePath(double T, int steps) const {
        std::vector<double> path(steps + 1);
        double dt = T / static_cast<double>(steps);
        double drift = (r - 0.5 * sigma * sigma) * dt;
        double vol_sqrt_dt = sigma * std::sqrt(dt);

        static thread_local std::random_device rd;
        static thread_local std::mt19937 gen(rd());
        std::normal_distribution<double> dist(0.0, 1.0);

        path[0] = S0;
        for (int i = 1; i <= steps; ++i) {
            double Z = dist(gen);
            path[i] = path[i - 1] * std::exp(drift + vol_sqrt_dt * Z);
        }
        return path;
    }

}
