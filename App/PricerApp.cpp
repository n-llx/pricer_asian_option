#include "PricerApp.hpp"
#include <iostream>
#include <clocale>
#include <algorithm>
#include <iomanip>
#include <random>
#include <limits>
#include <cmath>

#include "../Math/StochasticModel.hpp"
#include "../Instruments/Payoff.hpp"
#include "../Math/Greeks.hpp"
#include "../Graphics/plot.hpp"

using namespace std;

void PricerApp::run()
{
    setlocale(LC_NUMERIC, "C");
    cout << "||--- Pricer Option Asiatique (Monte Carlo) ---||" << endl;

    while (true)
    {
        cout << "Choisissez le mode : [1] Mode manuel, [2] Mode reel (ticker) : ";
        int mode_choice;
        if (!(cin >> mode_choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (mode_choice == 1)
        {
            runManualMode();
            break; // Manual mode exits after run, preserving original behavior
        }
        else if (mode_choice == 2)
        {
            runAutomaticMode();
            // Original code fell through to "Choix invalide" which is weird, but we'll loop back nicely.
        }
        else
        {
            cout << "Choix invalide. Veuillez reessayer." << endl;
        }
    }
}

void PricerApp::runManualMode()
{
    double S0_input, r, sigma_input, T, K;
    int steps, N;

    cout << "Mode manuel :" << endl;
    cout << "Entrez S0 (entre 50 et 150) : ";
    cin >> S0_input;
    cout << "Entrez r (taux) : ";
    cin >> r;
    cout << "Entrez sigma (entre 0.05 et 0.5) : ";
    cin >> sigma_input;
    cout << "Entrez T (maturite) : ";
    cin >> T;
    cout << "Entrez K (strike) : ";
    cin >> K;
    cout << "Entrez le nombre de pas (steps) : ";
    cin >> steps;
    cout << "Entrez N (nombre de simulations) : ";
    cin >> N;

    cout << "\n\nMonte carlo avec strike " << K << " et " << N << " simulations :" << "\n";

    random_device rd;
    unsigned int random_seed = rd();
    cout << "\n     Asian Call Price: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_call, K, random_seed) << "\n";
    cout << "\n     Asian Put Price: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_put, K, random_seed) << "\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void PricerApp::runAutomaticMode()
{
    string ticker;
    cout << "Mode automatique : Entrez une action (ex: AAPL, TSLA, MSFT,...): ";
    cin >> ticker;

    StockData market = fetchMarketData(ticker);
    if (!market.success)
    {
        cout << "Echec recuperation donnees pour '" << ticker << "'. Reessayez ou choisissez le mode manuel." << endl;
        return;
    }

    double S0_input = market.price;
    double sigma_input = market.volatility;
    double r, T, K;
    int steps, N;

    cout << "Donnees recues pour " << ticker << " : dernier prix = " << S0_input << ", derniere volatilite historique = " << sigma_input << endl;
    cout << "Entrez r (taux dinteret sans risque) : ";
    cin >> r;
    cout << "Entrez T (maturite) (annees) : ";
    cin >> T;
    cout << "Entrez K (strike) : ";
    cin >> K;
    cout << "Entrez le nombre de pas (steps) : ";
    cin >> steps;
    cout << "Entrez N (nombre de simulations) : ";
    cin >> N;

    computeAndPlot(N, S0_input, r, sigma_input, T, steps, K, true);
}

void PricerApp::computeAndPlot(int N, double S0_input, double r, double sigma_input, double T, int steps, double K, bool isAutoMode)
{
    cout << "\n\nMonte carlo avec strike " << K << " et " << N << " simulations :" << "\n";

    random_device rd;
    unsigned int random_seed = rd();
    cout << "\n     Asian Call Price: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_call, K, random_seed) << "\n";
    cout << "\n     Asian Put Price: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_put, K, random_seed) << "\n\n";

    if (!isAutoMode) return;

    int grid_size = 50;
    int total_points = (grid_size + 1) * (grid_size + 1);
    
    double S0_start = S0_input * 0.75;
    double S0_end = S0_input * 1.25;
    double sigma_start = max(0.01, sigma_input - 0.2);
    double sigma_end = sigma_input + 0.2;
    double r_start = max(0.0, r - 0.05);
    double r_end = r + 0.05;
    double T_start = 0.1;
    double T_end = T + 2.5;

    double r_step = (r_end - r_start) / grid_size;
    double T_step = (T_end - T_start) / grid_size;
    double s_step = (S0_end - S0_start) / grid_size;
    double vol_step = (sigma_end - sigma_start) / grid_size;

    int completed = 0;

    // Surface storage
    vector<vector<double>> call_results_spot(grid_size + 1, vector<double>(grid_size + 1));
    vector<vector<double>> put_results_spot(grid_size + 1, vector<double>(grid_size + 1));
    vector<vector<double>> call_results_r(grid_size + 1, vector<double>(grid_size + 1));
    vector<vector<double>> put_results_r(grid_size + 1, vector<double>(grid_size + 1));

    cout << "\nCalcul des surfaces en cours... N simulations pour chaque point " << endl;
    for (int i = 0; i <= grid_size; ++i)
    {
        for (int j = 0; j <= grid_size; ++j)
        {
            double current_sigma = sigma_start + i * vol_step;
            double current_S0 = S0_start + j * s_step;
            double current_r = r_start + i * r_step;
            double current_T = T_start + j * T_step;

            call_results_spot[i][j] = monte_carlo(N, current_S0, r, current_sigma, T, steps, &payoff_as_call, K, 42);
            call_results_r[i][j] = monte_carlo(N, S0_input, current_r, sigma_input, current_T, steps, &payoff_as_call, K, 42);

            // Put-Call Parity
            double expected_average = current_S0 * (exp(r * T) - 1.0) / (r * T);
            put_results_spot[i][j] = call_results_spot[i][j] - exp(-r * T) * (expected_average - K);

            double expected_average_r;
            if (abs(current_r) < 1e-7) {
                expected_average_r = S0_input;
            } else {
                expected_average_r = S0_input * (exp(current_r * current_T) - 1.0) / (current_r * current_T);
            }
            put_results_r[i][j] = call_results_r[i][j] - exp(-current_r * current_T) * (expected_average_r - K);

            completed++;
            if (completed % 10 == 0 || completed == total_points)
            {
                float progress = (float)completed / total_points;
                int barWidth = 40;
                int pos = barWidth * progress;
                cout << "\rProgression : [";
                for (int k = 0; k < barWidth; ++k)
                {
                    if (k < pos) cout << "=";
                    else if (k == pos) cout << ">";
                    else cout << " ";
                }
                cout << "] " << int(progress * 100.0) << "% " << flush;
            }
        }
    }
    cout << "\nCalculs termines !" << endl;

    plot_surface(grid_size, call_results_spot, S0_start, s_step, sigma_start, vol_step,
                "Surface Prix Call Asiatique en fonction du Spot et de la Volatilité", "Prix", "Prix spot", "Volatilite", K, r, T, N);
    plot_surface(grid_size, put_results_spot, S0_start, s_step, sigma_start, vol_step,
                "Surface Prix Put Asiatique en fonction du Spot et de la Volatilité", "Prix", "Prix spot", "Volatilite", K, r, T, N);
    plot_surface(grid_size, call_results_r, T_start, T_step, r_start, r_step,
                "Surface Prix Call Asiatique en fonction de r et T", "Prix", "Maturite (annees)", "Taux dinteret", K, S0_input, sigma_input, N);
    plot_surface(grid_size, put_results_r, T_start, T_step, r_start, r_step,
                "Surface Prix Put Asiatique en fonction de r et T", "Prix", "Maturite (annees)", "Taux dinteret", K, S0_input, sigma_input, N);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Greeks Loop
    while (true)
    {
        cout << "\n Choisissez le Greeks a calculer : [1] Delta, [2] Vega, [3] Gamma, [4] Rho, [5] Theta  : ";
        int greek_choice;
        cin >> greek_choice;

        cout << "\n Choisissez call/put pour le Greeks : [1] Call, [2] Put : ";
        int option_type;
        cin >> option_type;

        if (greek_choice < 1 || greek_choice > 5 || option_type < 1 || option_type > 2)
        {
            cout << "Choix invalide." << endl;
            continue;
        }

        // Logic for each Greek
        if (greek_choice == 1) // Delta
        {
            vector<vector<double>> results_grid(grid_size + 1, vector<double>(grid_size + 1));
            const auto& source_grid = (option_type == 1) ? call_results_spot : put_results_spot;
            string title = (option_type == 1) ? "Surface Delta Call" : "Surface Delta Put";
            
            for (int i = 0; i <= grid_size; ++i) {
                for (int j = 0; j <= grid_size; ++j) {
                    results_grid[i][j] = calculate_delta(source_grid, i, j, s_step);
                }
            }
            
            cout << "\n\nDelta calcule :" << results_grid[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, results_grid, S0_start, s_step, sigma_start, vol_step,
                        title.c_str(), "Delta", "Prix spot", "Volatilite", K, r, T, N);
        }
        else if (greek_choice == 2) // Vega
        {
            vector<vector<double>> results_grid(grid_size + 1, vector<double>(grid_size + 1));
            const auto& source_grid = (option_type == 1) ? call_results_spot : put_results_spot;
            string title = (option_type == 1) ? "Surface Vega Call" : "Surface Vega Put";

            for (int i = 0; i <= grid_size; ++i) {
                for (int j = 0; j <= grid_size; ++j) {
                    results_grid[i][j] = calculate_vega(source_grid, i, j, vol_step);
                }
            }
             cout << "\n\nVega calcule :" << results_grid[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, results_grid, S0_start, s_step, sigma_start, vol_step,
                        title.c_str(), "Vega", "Prix spot", "Volatilite", K, r, T, N);
        }
        else if (greek_choice == 3) // Gamma
        {
            vector<vector<double>> results_grid(grid_size + 1, vector<double>(grid_size + 1));
            const auto& source_grid = (option_type == 1) ? call_results_spot : put_results_spot;
            string title = (option_type == 1) ? "Surface Gamma Call" : "Surface Gamma Put";

            for (int i = 0; i <= grid_size; ++i) {
                for (int j = 0; j <= grid_size; ++j) {
                    results_grid[i][j] = calculate_gamma(source_grid, i, j, s_step);
                }
            }
            cout << "\n\nGamma calcule :" << results_grid[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, results_grid, S0_start, s_step, sigma_start, vol_step,
                        title.c_str(), "Gamma", "Prix spot", "Volatilite", K, r, T, N);

        }
        else if (greek_choice == 4) // Rho
        {
            vector<vector<double>> results_grid(grid_size + 1, vector<double>(grid_size + 1));
            const auto& source_grid = (option_type == 1) ? call_results_r : put_results_r;
            string title = (option_type == 1) ? "Surface rhos Call" : "Surface rho Put";

            for (int i = 0; i <= grid_size; ++i) {
                for (int j = 0; j <= grid_size; ++j) {
                    results_grid[i][j] = calculate_rho(source_grid, i, j, r_step);
                }
            }
             cout << "\n\nRho calcule :" << results_grid[grid_size * (1 - ((r_end - r) / (r_end - r_start)))][grid_size * (1 - ((T_end - T) / (T_end - T_start)))] << endl;
            plot_surface(grid_size, results_grid, T_start, T_step, r_start, r_step,
                        title.c_str(), "Rho", "Maturite (annees)", "Taux dinteret", K, S0_input, sigma_input, N);
        }
        else if (greek_choice == 5) // Theta
        {
            vector<vector<double>> results_grid(grid_size + 1, vector<double>(grid_size + 1));
            const auto& source_grid = (option_type == 1) ? call_results_r : put_results_r;
            string title = (option_type == 1) ? "Surface Theta Call" : "Surface Theta Put";

            for (int i = 0; i <= grid_size; ++i) {
                for (int j = 0; j <= grid_size; ++j) {
                    results_grid[i][j] = calculate_theta(source_grid, i, j, T_step);
                }
            }
            cout << "\n\nTheta calcule :" << results_grid[grid_size * (1 - ((r_end - r) / (r_end - r_start)))][grid_size * (1 - ((T_end - T) / (T_end - T_start)))] << endl;
            plot_surface(grid_size, results_grid, T_start, T_step, r_start, r_step,
                        title.c_str(), "Theta", "Maturite (annees)", "Taux dinteret", K, S0_input, sigma_input, N);
        }

        cout << "\nAffichage termine." << endl;
        cout << "Appuyez sur Entree";
        cin.ignore(1000, '\n');
        cin.get();
    }
}
