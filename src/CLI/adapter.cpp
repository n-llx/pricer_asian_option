#include <iostream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "Math/StochasticModel.hpp"
#include "Instruments/Payoff.hpp"
#include "Pricing/MonteCarloPricer.hpp"

using json = nlohmann::json;

// Helper to read all stdin
std::string read_stdin() {
    std::string content;
    std::string line;
    while (std::getline(std::cin, line)) {
        content += line;
    }
    return content;
}

int main() {
    try {
        // 1. Read input JSON from stdin
        std::string input_str = read_stdin();
        if (input_str.empty()) {
            std::cerr << "Error: No input provided" << std::endl;
            return 1;
        }

        auto x = json::parse(input_str);

        // 2. Extract parameters
        double S0 = x.value("S0", 100.0);
        double K = x.value("K", 100.0);
        double r = x.value("r", 0.05);
        double sigma = x.value("sigma", 0.2);
        double T = x.value("T", 1.0);
        int steps = x.value("steps", 100);
        int N = x.value("N", 10000);
        std::string type = x.value("type", "call");

        // 3. Setup Financial Model
        // Currently using BlackScholes as default for V2 MVP
        // Extensions: Logic to switch to Heston if params provided
        Core::BlackScholesModel model(S0, r, sigma);
        Core::MonteCarloPricer pricer(N);
        Core::PricingResult result;

        // 4. Pricing
        if (type == "call") {
             // Asian Call
            Core::AsianCallPayoff payoff(K);
            result = pricer.price(model, payoff, T, steps);
        } else {
             // Asian Put
            Core::AsianPutPayoff payoff(K);
            result = pricer.price(model, payoff, T, steps);
        }

        // 5. Output JSON to stdout
        json res_json;
        res_json["price"] = result.price;
        res_json["delta"] = result.delta;
        res_json["gamma"] = result.gamma;
        res_json["vega"] = result.vega;
        res_json["theta"] = result.theta;
        res_json["rho"] = result.rho;

        std::cout << res_json.dump() << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
