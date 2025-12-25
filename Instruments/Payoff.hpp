#ifndef PAYOFF_HPP
#define PAYOFF_HPP

class Payoff {
public:
    static double payoff_eu_call(const std::vector<double>& path, double K);
    static double payoff_as_call(const std::vector<double>& path, double K);
    static double payoff_eu_put(const std::vector<double>& path, double K);
    static double payoff_as_put(const std::vector<double>& path, double K);
};

#endif // PAYOFF_HPP
