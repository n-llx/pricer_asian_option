#ifndef MARKET_DATA_HPP
#define MARKET_DATA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <windows.h>
#include <wininet.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct StockData {
    double price = 0.0;
    double volatility = 0.0;
    bool success = false;
};

std::string windowsHttpsGet(const std::string& url) {
    std::string response;
    HINTERNET hSession = InternetOpenA("PricerAgent", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hSession) {
        HINTERNET hUrl = InternetOpenUrlA(hSession, url.c_str(), NULL, 0, INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD, 0);
        if (hUrl) {
            char buffer[4096];
            DWORD bytesRead;
            while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
                response.append(buffer, bytesRead);
            }
            InternetCloseHandle(hUrl);
        }
        InternetCloseHandle(hSession);
    }
    return response;
}

StockData fetchMarketData(std::string ticker) {
    StockData data;
    // Request 1 month of daily data to calculate volatility
    std::string url = "https://query1.finance.yahoo.com/v8/finance/chart/" + ticker + "?interval=1d&range=1mo";
    std::string jsonRaw = windowsHttpsGet(url);

    if (jsonRaw.empty()) return data;

    try {
        auto j = json::parse(jsonRaw);
        auto& result = j["chart"]["result"][0];
        
        // 1. Get Current Price
        data.price = result["meta"]["regularMarketPrice"];
        
        // 2. Extract Closing Prices for Volatility
        std::vector<double> closes = result["indicators"]["quote"][0]["close"].get<std::vector<double>>();
        
        // Remove nulls if any (Yahoo sometimes returns nulls for holidays)
        closes.erase(std::remove_if(closes.begin(), closes.end(), [](double d){ return d == 0; }), closes.end());

        if (closes.size() > 1) {
            std::vector<double> logReturns;
            for (size_t i = 1; i < closes.size(); ++i) {
                logReturns.push_back(std::log(closes[i] / closes[i - 1]));
            }

            // Standard Deviation of log returns
            double sum = std::accumulate(logReturns.begin(), logReturns.end(), 0.0);
            double mean = sum / logReturns.size();
            double sq_sum = std::inner_product(logReturns.begin(), logReturns.end(), logReturns.begin(), 0.0);
            double stdev = std::sqrt(sq_sum / logReturns.size() - mean * mean);

            // Annualize (sqrt of ~252 trading days)
            data.volatility = stdev * std::sqrt(252);
            data.success = true;
            
            std::cout << "[DATA] " << ticker << " | Price: " << data.price 
                      << " | Vol hist (Ann): " << (data.volatility * 100) << "%" << std::endl;
        }
    } catch (...) {
        std::cerr << "[ERROR] Volatility calculation failed." << std::endl;
    }
    return data;
}

#endif