#ifndef PAYOFF_HPP
#define PAYOFF_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>

namespace Core {

    class Payoff {
    public:
        virtual ~Payoff() = default;
        virtual double operator()(const std::vector<double>& path) const = 0;
        virtual std::unique_ptr<Payoff> clone() const = 0;
    };

    class AsianCallPayoff : public Payoff {
        double K;
    public:
        AsianCallPayoff(double strike);
        double operator()(const std::vector<double>& path) const override;
        std::unique_ptr<Payoff> clone() const override;
    };

    class AsianPutPayoff : public Payoff {
        double K;
    public:
        AsianPutPayoff(double strike);
        double operator()(const std::vector<double>& path) const override;
        std::unique_ptr<Payoff> clone() const override;
    };

    class EuropeanCallPayoff : public Payoff {
        double K;
    public:
        EuropeanCallPayoff(double strike);
        double operator()(const std::vector<double>& path) const override;
        std::unique_ptr<Payoff> clone() const override;
    };

    class EuropeanPutPayoff : public Payoff {
        double K;
    public:
        EuropeanPutPayoff(double strike);
        double operator()(const std::vector<double>& path) const override;
        std::unique_ptr<Payoff> clone() const override;
    };

}

#endif
