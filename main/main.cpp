#include "Math/StochasticModel.hpp"
#include "Instruments/Payoff.hpp"
#include <iostream>

int main(){
    double S0 = 100;
    double r = 0.03;
    double sigma = .25;
    double T = 1;
    int steps = 20;
    int N = 100;
    double K = 100;
    vector<double> path = generate_price_path(S0,r,sigma, T, steps);
    cout << "path :"<<"\n";
    for (double i:path) cout << i <<' ';
    cout <<"\n"<< "payoff with K ="<<K<<" :"<<"\n";
    cout<<"call EU: "<<payoff_eu_call(path, K)<<"\n";
    cout<<"call AS : "<<payoff_as_call(path, K)<<"\n";
    cout<<"put EU:"<<payoff_eu_put(path, K)<<"\n";
    cout<<"put AS :"<<payoff_as_put(path, K)<<"\n"<<"\n";
    cout << "GBM withK ="<<K<<" :"<<"\n";
    cout<<"call AS: "<<monte_carlo(N,S0,r, sigma,T, steps, &payoff_as_call, K )<<"\n";
    cout<<"put AS:"<<monte_carlo(N,S0,r, sigma,T, steps, &payoff_as_put, K )<<"\n"<<"\n";
    
    return 0;
}