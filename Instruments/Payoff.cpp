#include "Payoff.hpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>


using namespace std;

double payoff_eu_call(vector<double> path, double K){
    double final_S = path.back();
    double payoff = max(final_S-K, 0.0);
    return payoff;
    
}

double payoff_eu_put(vector<double> path, double K){
    double final_S = path.back();
    double payoff = max(K-final_S, 0.0);
    return payoff;
}

double payoff_as_call(vector<double> path, double K){
    double avg_S = 0.0;
    for (double s : path) avg_S += s;
    avg_S /= path.size();
    double payoff = max(avg_S-K, 0.0);
    return payoff;
    
}

double payoff_as_put(vector<double> path, double K){
    double avg_S = 0.0;
    for (double s : path) avg_S += s;
    avg_S /= path.size();
    double payoff = max(K-avg_S, 0.0);
    return payoff;
}