#include "Payoff.hpp"
#include <cmath>

namespace Core {

    // --- Asian Call ---
    AsianCallPayoff::AsianCallPayoff(double strike) : K(strike) {}

    double AsianCallPayoff::operator()(const std::vector<double>& path) const {
        if (path.empty()) return 0.0;
        double sum = std::accumulate(path.begin(), path.end(), 0.0);
        double avg = sum / path.size();
        return std::max(avg - K, 0.0);
    }

    std::unique_ptr<Payoff> AsianCallPayoff::clone() const {
        return std::make_unique<AsianCallPayoff>(*this);
    }

    // --- Asian Put ---
    AsianPutPayoff::AsianPutPayoff(double strike) : K(strike) {}

    double AsianPutPayoff::operator()(const std::vector<double>& path) const {
        if (path.empty()) return 0.0;
        double sum = std::accumulate(path.begin(), path.end(), 0.0);
        double avg = sum / path.size();
        return std::max(K - avg, 0.0);
    }

    std::unique_ptr<Payoff> AsianPutPayoff::clone() const {
        return std::make_unique<AsianPutPayoff>(*this);
    }

    // --- European Call ---
    EuropeanCallPayoff::EuropeanCallPayoff(double strike) : K(strike) {}

    double EuropeanCallPayoff::operator()(const std::vector<double>& path) const {
        if (path.empty()) return 0.0;
        return std::max(path.back() - K, 0.0);
    }

    std::unique_ptr<Payoff> EuropeanCallPayoff::clone() const {
        return std::make_unique<EuropeanCallPayoff>(*this);
    }

    // --- European Put ---
    EuropeanPutPayoff::EuropeanPutPayoff(double strike) : K(strike) {}

    double EuropeanPutPayoff::operator()(const std::vector<double>& path) const {
        if (path.empty()) return 0.0;
        return std::max(K - path.back(), 0.0);
    }

    std::unique_ptr<Payoff> EuropeanPutPayoff::clone() const {
        return std::make_unique<EuropeanPutPayoff>(*this);
    }

}