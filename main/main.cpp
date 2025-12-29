#include <iostream>
#include <clocale>
#include "../Math/StochasticModel.hpp"
#include "../Instruments/Payoff.hpp"
#include "../Math/Greeks.hpp"
#include "../MarketData/MarketData.hpp"
#include <vector>
#include <cstdio>
#include <cmath>
#include <random>
#include <algorithm>
#include <iomanip> // pour la barre de progression

#include "../Graphics/plot.hpp"

using namespace std;

int main()
{
    setlocale(LC_NUMERIC, "C");
    int grid_size = 50;
    double S0_input, r, sigma_input, T, K;
    int steps, N;
    int total_points = (grid_size + 1) * (grid_size + 1);
    int completed_points = 0;
    string ticker;
    StockData market;
    bool usedMarket = false;

    cout << "||--- Pricer Option Asiatique (Monte Carlo) ---||" << endl;

    // Choix du mode : manuel ou réel
    while (true)
    {
        cout << "Choisissez le mode : [1] Mode manuel, [2] Mode reel (ticker) : ";
        int mode_choice;
        cin >> mode_choice;

        if (mode_choice == 1)
        {
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
            usedMarket = false;

            cout << "\n\nMonte carlo avec strike " << K << " et " << N << " simulations :" << "\n";

            // On utilise une seed aléatoire pour le calcul ponctuel
            random_device rd;
            unsigned int random_seed = rd();
            cout << "\n     Asian Call Price: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_call, K, random_seed) << "\n";
            cout << "\n     Asian Put Price: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_put, K, random_seed) << "\n"
                << "\n";

            break;
        }

        if (mode_choice == 2)
        {
            cout << "Mode automatique : Entrez une action (ex: AAPL, TSLA, MSFT,...): ";
            cin >> ticker;
            market = fetchMarketData(ticker);
            if (market.success)
            {
                S0_input = market.price;
                sigma_input = market.volatility;
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
                usedMarket = true;
            cout << "\n\nMonte carlo avec strike " << K << " et " << N << " simulations :" << "\n";

            // On utilise une seed aléatoire pour le calcul ponctuel
            random_device rd;
            unsigned int random_seed = rd();
            cout << "\n     Asian Call Price: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_call, K, random_seed) << "\n";
            cout << "\n     Asian Put Price: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_put, K, random_seed) << "\n"
                << "\n";

            double S0_start = S0_input * 0.75;
            double S0_end = S0_input * 1.25;
            double sigma_start = max(0.01, sigma_input - 0.2);
            double sigma_end = sigma_input + 0.2;
            double r_start = max(0.0, r - 0.05);
            double r_end = r + 0.05;
            double T_start = max(0.1, T - 1);
            double T_end = T + 2;
            double r_input = r;
            double r_step = (r_end - r_start) / grid_size;
            double T_step = (T_end - T_start) / grid_size;
            double s_step = (S0_end - S0_start) / grid_size;
            double vol_step = (sigma_end - sigma_start) / grid_size;
            int completed = 0;

            // Calcul des surfaces (Call/Put/Greeks)
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

                    // On fixe la graine à 42 pour avoir des surfaces bien lisses
                    call_results_spot[i][j] = monte_carlo(N, current_S0, r, current_sigma, T, steps, &payoff_as_call, K, 42);
                    call_results_r[i][j] = monte_carlo(N, S0_input, current_r, sigma_input, current_T, steps, &payoff_as_call, K, 42);

                    // On déduit le Put par parité Call-Put
                    double expected_average = current_S0 * (exp(r * T) - 1.0) / (r * T);
                    put_results_spot[i][j] = call_results_spot[i][j] - exp(-r * T) * (expected_average - K);
                    double expected_average_r;
                    if (abs(current_r) < 1e-7) {
                        expected_average_r = S0_input; // Limite lorsque r -> 0
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
                            if (k < pos)
                                cout << "=";
                            else if (k == pos)
                                cout << ">";
                            else
                                cout << " ";
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
                }

                if (greek_choice == 1 && option_type == 1)
                {
                    vector<vector<double>> call_delta_call_results(grid_size + 1, vector<double>(grid_size + 1));

                    for (int i = 0; i <= grid_size; ++i)
                    {
                        for (int j = 0; j <= grid_size; ++j)
                        {
                            // Calcul du Delta par méthode des différences finies
                            call_delta_call_results[i][j] = calculate_delta(call_results_spot, i, j, s_step);
                        }
                    }
                    cout << "\n\nDelta calcule :" << call_delta_call_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
                    plot_surface(grid_size, call_delta_call_results, S0_start, s_step, sigma_start, vol_step,
                                "Surface Delta Call", "Delta", "Prix spot", "Volatilite", K, r, T, N);
                }

                if (greek_choice == 1 && option_type == 2)
                {
                    vector<vector<double>> call_delta_put_results(grid_size + 1, vector<double>(grid_size + 1));

                    for (int i = 0; i <= grid_size; ++i)
                    {
                        for (int j = 0; j <= grid_size; ++j)
                        {
                            // Calcul du Delta par méthode des différences finies
                            call_delta_put_results[i][j] = calculate_delta(put_results_spot, i, j, s_step);
                        }
                    }
                    cout << "\n\nDelta calcule :" << call_delta_put_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
                    plot_surface(grid_size, call_delta_put_results, S0_start, s_step, sigma_start, vol_step,
                                "Surface Delta Put", "Delta", "Prix spot", "Volatilite", K, r, T, N);
                }

                if (greek_choice == 2 && option_type == 1)
                {
                    vector<vector<double>> call_vega_call_results(grid_size + 1, vector<double>(grid_size + 1));
                    for (int i = 0; i <= grid_size; ++i)
                    {
                        for (int j = 0; j <= grid_size; ++j)
                        {
                            // Calcul du Vega par méthode des différences finies
                            call_vega_call_results[i][j] = calculate_vega(call_results_spot, i, j, vol_step);
                        }
                    }
                    cout << "\n\nVega calcule :" << call_vega_call_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
                    plot_surface(grid_size, call_vega_call_results, S0_start, s_step, sigma_start, vol_step,
                                "Surface Vega Call", "Vega", "Prix spot", "Volatilite", K, r, T, N);
                }

                if (greek_choice == 2 && option_type == 2)
                {
                    vector<vector<double>> call_vega_put_results(grid_size + 1, vector<double>(grid_size + 1));
                    for (int i = 0; i <= grid_size; ++i)
                    {
                        for (int j = 0; j <= grid_size; ++j)
                        {
                            // Calcul du Vega par méthode des différences finies
                            call_vega_put_results[i][j] = calculate_vega(put_results_spot, i, j, vol_step);
                        }
                    }
                    cout << "\n\nVega calcule :" << call_vega_put_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
                    plot_surface(grid_size, call_vega_put_results, S0_start, s_step, sigma_start, vol_step,
                                "Surface Vega Put", "Vega", "Prix spot", "Volatilite", K, r, T, N);
                }

                if (greek_choice == 3 && option_type == 1)
                {

                    vector<vector<double>> call_gamma_call_results(grid_size + 1, vector<double>(grid_size + 1));
                    for (int i = 0; i <= grid_size; ++i)
                    {
                        for (int j = 0; j <= grid_size; ++j)
                        {
                            // Calcul du Gamma par méthode des différences finies
                            call_gamma_call_results[i][j] = calculate_gamma(call_results_spot, i, j, s_step);
                        }
                    }
                    cout << "\n\nGamma calcule :" << call_gamma_call_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
                    plot_surface(grid_size, call_gamma_call_results, S0_start, s_step, sigma_start, vol_step,
                                "Surface Gamma Call", "Gamma", "Prix spot", "Volatilite", K, r, T, N);
                }

                if (greek_choice == 3 && option_type == 2)
                {

                    vector<vector<double>> call_gamma_put_results(grid_size + 1, vector<double>(grid_size + 1));
                    for (int i = 0; i <= grid_size; ++i)
                    {
                        for (int j = 0; j <= grid_size; ++j)
                        {
                            // Calcul du Gamma par méthode des différences finies
                            call_gamma_put_results[i][j] = calculate_gamma(put_results_spot, i, j, s_step);
                        }
                    }
                    cout << "\n\nGamma calcule :" << call_gamma_put_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
                    plot_surface(grid_size, call_gamma_put_results, S0_start, s_step, sigma_start, vol_step,
                                "Surface Gamma Put", "Gamma", "Prix spot", "Volatilite", K, r, T, N);
                }

                if (greek_choice == 4 && option_type == 1)
                {
                    vector<vector<double>> call_rho_call_results(grid_size + 1, vector<double>(grid_size + 1));
                    for (int i = 0; i <= grid_size; ++i)
                    {
                        for (int j = 0; j <= grid_size; ++j)
                        {
                            // Calcul du Rho par méthode des différences finies
                            call_rho_call_results[i][j] = calculate_rho(call_results_r, i, j, r_step);

                        }
                    }
                    cout << "\n\nRho calcule :" << call_rho_call_results[grid_size * (1 - ((r_end - r) / (r_end - r_start)))][grid_size * (1 - ((T_end - T) / (T_end - T_start)))] << endl;
                    plot_surface(grid_size, call_rho_call_results, T_start, T_step, r_start, r_step,
                        "Surface rho Call", "Rho", "Maturite (annees)", "Taux dinteret", K, S0_input, sigma_input, N);
                }

                if (greek_choice == 4 && option_type == 2)
                {
                    vector<vector<double>> call_rho_put_results(grid_size + 1, vector<double>(grid_size + 1));
                    for (int i = 0; i <= grid_size; ++i)
                    {
                        for (int j = 0; j <= grid_size; ++j)
                        {
                            // Calcul du Rho par méthode des différences finies
                            call_rho_put_results[i][j] = calculate_rho(put_results_r, i, j, r_step);

                        }
                    }
                    cout << "\n\nRho calcule :" << call_rho_put_results[grid_size * (1 - ((r_end - r) / (r_end - r_start)))][grid_size * (1 - ((T_end - T) / (T_end - T_start)))] << endl;
                    plot_surface(grid_size, call_rho_put_results, T_start, T_step, r_start, r_step,
                        "Surface rho Put", "Rho", "Maturite (annees)", "Taux dinteret", K, S0_input, sigma_input, N);
                }

                if (greek_choice == 5 && option_type == 1)
                {
                    vector<vector<double>> call_theta_call_results(grid_size + 1, vector<double>(grid_size + 1));
                    for (int i = 0; i <= grid_size; ++i)
                    {
                        for (int j = 0; j <= grid_size; ++j)
                        {
                            // Calcul du Theta par méthode des différences finies
                            call_theta_call_results[i][j] = calculate_theta(call_results_r, i, j, T_step);
                        }
                    }
                    cout << "\n\nTheta calcule :" << call_theta_call_results[grid_size * (1 - ((r_end - r) / (r_end - r_start)))][grid_size * (1 - ((T_end - T) / (T_end - T_start)))] << endl;
                    plot_surface(grid_size, call_theta_call_results, T_start, T_step, r_start, r_step,
                        "Surface Theta Call", "Theta", "Maturite (annees)", "Taux dinteret", K, S0_input, sigma_input, N);
                }

                if (greek_choice == 5 && option_type == 2)
                {
                    vector<vector<double>> call_theta_put_results(grid_size + 1, vector<double>(grid_size + 1));
                    for (int i = 0; i <= grid_size; ++i)
                    {
                        for (int j = 0; j <= grid_size; ++j)
                        {
                            call_theta_put_results[i][j] = calculate_theta(put_results_r, i, j, T_step);
                        }
                    }
                    cout << "\n\nTheta calcule :" << call_theta_put_results[grid_size * (1 - ((r_end - r) / (r_end - r_start)))][grid_size * (1 - ((T_end - T) / (T_end - T_start)))] << endl;
                    plot_surface(grid_size, call_theta_put_results, T_start, T_step, r_start, r_step,
                                "Surface Theta Put", "Theta", "Maturite (annees)", "Taux dinteret", K, S0_input, sigma_input, N);
                }

                cout << "\nAffichage termine." << endl;
                cout << "Appuyez sur Entree";
                cin.ignore(1000, '\n');
                cin.get();
            }

            }
            else
            {
                cout << "Echec recuperation donnees pour '" << ticker << "'. Reessayez ou choisissez le mode manuel." << endl;
            }
        }

        cout << "Choix invalide. Veuillez reessayer." << endl;
    }
return 0;
}