#include <iostream>
#if defined(__MINGW32__) || defined(__MINGW64__)
#include "mingw.thread.h"
#include "mingw.mutex.h"
#include "mingw.condition_variable.h"
#endif

#include "httplib.h"
#include "nlohmann/json.hpp"
#include "Math/StochasticModel.hpp"
#include "Instruments/Payoff.hpp"
#include "Pricing/MonteCarloPricer.hpp"

using json = nlohmann::json;

int main() {
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Asian Option Pricer API is running. POST to /api/price", "text/plain");
    });

    svr.Post("/api/price", [](const httplib::Request &req, httplib::Response &res) {
        try {
            auto x = json::parse(req.body);
            
            // Extract parameters
            double S0 = x.value("S0", 100.0);
            double K = x.value("K", 100.0);
            double r = x.value("r", 0.05);
            double sigma = x.value("sigma", 0.2);
            double T = x.value("T", 1.0);
            int steps = x.value("steps", 100);
            int N = x.value("N", 10000);
            std::string type = x.value("type", "call");

            // Setup Model
            Core::BlackScholesModel model(S0, r, sigma);
            Core::MonteCarloPricer pricer(N);
            Core::PricingResult result;

            // Pricing
            if (type == "call") {
                Core::AsianCallPayoff payoff(K);
                result = pricer.price(model, payoff, T, steps);
            } else {
                Core::AsianPutPayoff payoff(K);
                result = pricer.price(model, payoff, T, steps);
            }

            // Response
            json res_json;
            res_json["price"] = result.price;
            res_json["delta"] = result.delta;
            res_json["gamma"] = result.gamma;
            res_json["vega"] = result.vega;
            res_json["theta"] = result.theta;
            res_json["rho"] = result.rho;
            
            res.set_content(res_json.dump(), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(e.what(), "text/plain");
        }
    });

    std::cout << "Server listening on http://localhost:18080" << std::endl;
    svr.listen("0.0.0.0", 18080);
}
