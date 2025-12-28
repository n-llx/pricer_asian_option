#ifndef STOCHASTIC_MODEL_HPP
#define STOCHASTIC_MODEL_HPP

#include <vector>
#include <memory> 

namespace Core {

    class StochasticModel {
    public:
        virtual ~StochasticModel() = default;
        virtual std::vector<double> generatePath(double T, int steps) const = 0;
    };

    class BlackScholesModel : public StochasticModel {
        double S0;
        double r;
        double sigma;
    public:
        BlackScholesModel(double S0, double r, double sigma);
        std::vector<double> generatePath(double T, int steps) const override;
        
        // Getters for Greeks calculation later
        double getS0() const { return S0; }
        double getR() const { return r; }
        double getSigma() const { return sigma; }
    };

}

#endif
