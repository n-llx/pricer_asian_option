#ifndef MONTE_CARLO_PRICER_HPP
#define MONTE_CARLO_PRICER_HPP

#include "../Math/StochasticModel.hpp"
#include "../Instruments/Payoff.hpp"

namespace Core {

    struct PricingResult {
        double price;
        double delta;
        double gamma;
        double vega;
        double theta;
        double rho;
    };

    class MonteCarloPricer {
        int N;
    public:
        MonteCarloPricer(int simulations);
        PricingResult price(const BlackScholesModel& model, const Payoff& payoff, double T, int steps) const;
        // Keep it specific to BS for now for Greeks simplicity, or use dynamic casting/cloning for generic models
    };

}

#endif
