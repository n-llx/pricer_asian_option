#ifndef HESTON_MODEL_HPP
#define HESTON_MODEL_HPP

#include "StochasticModel.hpp"

namespace Core {

    class HestonModel : public StochasticModel {
        double S0;
        double r;
        double v0;     // Initial variance
        double kappa;  // Mean reversion speed
        double theta;  // Long-term variance
        double xi;     // Vol of vol
        double rho;    // Correlation
    public:
        HestonModel(double S0, double r, double v0, double kappa, double theta, double xi, double rho);
        std::vector<double> generatePath(double T, int steps) const override;
    };

}

#endif
