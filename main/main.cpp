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

    // Choix du mode : manuel ou réel (boucle comme pour les Greeks)
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
            break;
        }

        if (mode_choice == 2)
        {
            cout << "Mode reel : Entrez une action (ex: AAPL, TSLA, MSFT,...): ";
            cin >> ticker;
            market = fetchMarketData(ticker);
            if (market.success)
            {
                S0_input = market.price;
                sigma_input = market.volatility;
                cout << "Donnees recues pour " << ticker << " : dernier prix = " << S0_input << ", derniere volatilite historique = " << sigma_input << endl;
                cout << "Entrez r (taux) : ";
                cin >> r;
                cout << "Entrez T (maturite) : ";
                cin >> T;
                cout << "Entrez K (strike) : ";
                cin >> K;
                cout << "Entrez le nombre de pas (steps) : ";
                cin >> steps;
                cout << "Entrez N (nombre de simulations) : ";
                cin >> N;
                usedMarket = true;
                break;
            }
            else
            {
                cout << "Echec recuperation donnees pour '" << ticker << "'. Reessayez ou choisissez le mode manuel." << endl;
            }
        }

        cout << "Choix invalide. Veuillez reessayer." << endl;
    }

    cout << "\n\nMonte carlo avec strike " << K << " et " << N << " simulations :" << "\n";

    // On utilise une seed aléatoire pour le calcul ponctuel
    random_device rd;
    unsigned int random_seed = rd();
    cout << "\n     Asian Call Price: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_call, K, random_seed) << "\n";
    cout << "\n     Asian Put Price: " << monte_carlo(N, S0_input, r, sigma_input, T, steps, &payoff_as_put, K, random_seed) << "\n"
         << "\n";

    cout << "||--- Calcul de surfaces automatique ---||" << endl;
    if (!usedMarket)
    {
        // Mode manuel : réutiliser les paramètres saisis précédemment sans demander de ticker
        cout << "Utilisation des parametres saisis manuellement : S0 = " << S0_input << ", sigma = " << sigma_input << endl;
    }
    else
    {
        cout << "Reutilisation des donnees de marche pour " << ticker << " : dernier prix = " << S0_input << ", derniere volatilite = " << sigma_input << endl;
    }

    double S0_start = S0_input * 0.75;
    double S0_end = S0_input * 1.25;
    double sigma_start = max(0.01, sigma_input - 0.2);
    double sigma_end = sigma_input + 0.2;
    double s_step = (S0_end - S0_start) / grid_size;
    double vol_step = (sigma_end - sigma_start) / grid_size;
    int completed = 0;

    // Calcul des surfaces (Call/Put/Greeks)
    vector<vector<double>> call_results(grid_size + 1, vector<double>(grid_size + 1));
    vector<vector<double>> put_results(grid_size + 1, vector<double>(grid_size + 1));

    cout << "\nCalcul des surfaces en cours... N simulations pour chaque point " << endl;
    for (int i = 0; i <= grid_size; ++i)
    {
        for (int j = 0; j <= grid_size; ++j)
        {
            double current_sigma = sigma_start + i * vol_step;
            double current_S0 = S0_start + j * s_step;

            // On fixe la graine à 42 pour avoir des surfaces bien lisses
            call_results[i][j] = monte_carlo(N, current_S0, r, current_sigma, T, steps, &payoff_as_call, K, 42);

            // On déduit le Put par parité Call-Put
            put_results[i][j] = call_results[i][j] - current_S0 + K * exp(-r * T);

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

    plot_surface(grid_size, call_results, S0_start, s_step, sigma_start, vol_step,
                 "Surface Prix Call Asiatique", "Prix", K, r, T, N);
    plot_surface(grid_size, put_results, S0_start, s_step, sigma_start, vol_step,
                 "Surface Prix Put Asiatique", "Prix", K, r, T, N);

    while (true)
    {
        cout << "\n Choisissez le Greeks à calculer : [1] Delta, [2] Vega, [3] Gamma, [4] Rho, [5] Theta  : ";
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
                    call_delta_call_results[i][j] = calculate_delta(call_results, i, j, s_step);
                }
            }
            cout << "\n\nDelta calcule :" << call_delta_call_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, call_delta_call_results, S0_start, s_step, sigma_start, vol_step,
                         "Surface Delta Call", "Delta", K, r, T, N);
        }

        if (greek_choice == 1 && option_type == 2)
        {
            vector<vector<double>> call_delta_put_results(grid_size + 1, vector<double>(grid_size + 1));

            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    // Calcul du Delta par méthode des différences finies
                    call_delta_put_results[i][j] = calculate_delta(put_results, i, j, s_step);
                }
            }
            cout << "\n\nDelta calcule :" << call_delta_put_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, call_delta_put_results, S0_start, s_step, sigma_start, vol_step,
                         "Surface Delta Put", "Delta", K, r, T, N);
        }

        if (greek_choice == 2 && option_type == 1)
        {
            vector<vector<double>> call_vega_call_results(grid_size + 1, vector<double>(grid_size + 1));
            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    // Calcul du Vega par méthode des différences finies
                    call_vega_call_results[i][j] = calculate_vega(call_results, i, j, vol_step);
                }
            }
            cout << "\n\nVega calcule :" << call_vega_call_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, call_vega_call_results, S0_start, s_step, sigma_start, vol_step,
                         "Surface Vega Call", "Vega", K, r, T, N);
        }

        if (greek_choice == 2 && option_type == 2)
        {
            vector<vector<double>> call_vega_put_results(grid_size + 1, vector<double>(grid_size + 1));
            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    // Calcul du Vega par méthode des différences finies
                    call_vega_put_results[i][j] = calculate_vega(put_results, i, j, vol_step);
                }
            }
            cout << "\n\nVega calcule :" << call_vega_put_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, call_vega_put_results, S0_start, s_step, sigma_start, vol_step,
                         "Surface Vega Put", "Vega", K, r, T, N);
        }

        if (greek_choice == 3 && option_type == 1)
        {

            vector<vector<double>> call_gamma_call_results(grid_size + 1, vector<double>(grid_size + 1));
            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    // Calcul du Gamma par méthode des différences finies
                    call_gamma_call_results[i][j] = calculate_gamma(call_results, i, j, s_step);
                }
            }
            cout << "\n\nGamma calcule :" << call_gamma_call_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, call_gamma_call_results, S0_start, s_step, sigma_start, vol_step,
                         "Surface Gamma Call", "Gamma", K, r, T, N);
        }

        if (greek_choice == 3 && option_type == 2)
        {

            vector<vector<double>> call_gamma_put_results(grid_size + 1, vector<double>(grid_size + 1));
            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    // Calcul du Gamma par méthode des différences finies
                    call_gamma_put_results[i][j] = calculate_gamma(put_results, i, j, s_step);
                }
            }
            cout << "\n\nGamma calcule :" << call_gamma_put_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, call_gamma_put_results, S0_start, s_step, sigma_start, vol_step,
                         "Surface Gamma Put", "Gamma", K, r, T, N);
        }

        if (greek_choice == 4 && option_type == 1)
        {

            vector<vector<double>> call_rho_call_results(grid_size + 1, vector<double>(grid_size + 1));
            vector<vector<double>> call_results_r_plus(grid_size + 1, vector<double>(grid_size + 1));
            double r_step = 1e-4;
            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    double current_sigma_r = sigma_start + i * vol_step;
                    double current_S0_r = S0_start + j * s_step;
                    call_results_r_plus[i][j] = monte_carlo(N, current_S0_r, r + r_step, current_sigma_r, T, steps, &payoff_as_call, K, 42);
                }
            }

            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    call_rho_call_results[i][j] = calculate_rho(call_results, call_results_r_plus, i, j, r_step);
                }
            }
            cout << "\n\nRho calcule :" << call_rho_call_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, call_rho_call_results, S0_start, s_step, sigma_start, vol_step,
                         "Surface Rho Call", "Rho", K, r, T, N);
        }

        if (greek_choice == 4 && option_type == 2)
        {

            vector<vector<double>> call_rho_put_results(grid_size + 1, vector<double>(grid_size + 1));
            vector<vector<double>> put_results_r_plus(grid_size + 1, vector<double>(grid_size + 1));

            double r_step = 1e-4;
            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    double current_sigma_r = sigma_start + i * vol_step;
                    double current_S0_r = S0_start + j * s_step;
                    put_results_r_plus[i][j] = monte_carlo(N, current_S0_r, r + r_step, current_sigma_r, T, steps, &payoff_as_put, K, 42);
                }
            }

            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    call_rho_put_results[i][j] = calculate_rho(put_results, put_results_r_plus, i, j, r_step);
                }
            }
            cout << "\n\nRho calcule :" << call_rho_put_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, call_rho_put_results, S0_start, s_step, sigma_start, vol_step,
                         "Surface Rho Put", "Rho", K, r, T, N);
        }

        if (greek_choice == 5 && option_type == 1)
        {

            vector<vector<double>> call_theta_call_results(grid_size + 1, vector<double>(grid_size + 1));
            vector<vector<double>> call_results_t_minus(grid_size + 1, vector<double>(grid_size + 1));
            double t_step = 1e-2 * T;
            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    double current_sigma_t = sigma_start + i * vol_step;
                    double current_S0_t = S0_start + j * s_step;
                    call_results_t_minus[i][j] = monte_carlo(N, current_S0_t, r, current_sigma_t, T - t_step, steps, &payoff_as_call, K, 42);
                }
            }

            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    call_theta_call_results[i][j] = calculate_theta(call_results, call_results_t_minus, i, j, t_step);
                }
            }
            cout << "\n\nTheta calcule :" << call_theta_call_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, call_theta_call_results, S0_start, s_step, sigma_start, vol_step,
                         "Surface Theta Call", "Theta", K, r, T, N);
        }

        if (greek_choice == 5 && option_type == 2)
        {

            vector<vector<double>> call_theta_put_results(grid_size + 1, vector<double>(grid_size + 1));
            vector<vector<double>> put_results_t_minus(grid_size + 1, vector<double>(grid_size + 1));

            // Use a consistent (and not too small) time step to limit MC noise amplification
            double t_step = 1e-2 * T;

            // Compute call_results at T - t_step and derive put by put-call parity
            vector<vector<double>> call_results_t_minus(grid_size + 1, vector<double>(grid_size + 1));
            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    double current_sigma_t = sigma_start + i * vol_step;
                    double current_S0_t = S0_start + j * s_step;
                    call_results_t_minus[i][j] = monte_carlo(N, current_S0_t, r, current_sigma_t, T - t_step, steps, &payoff_as_call, K, 42);
                    put_results_t_minus[i][j] = call_results_t_minus[i][j] - current_S0_t + K * exp(-r * (T - t_step));
                }
            }

            for (int i = 0; i <= grid_size; ++i)
            {
                for (int j = 0; j <= grid_size; ++j)
                {
                    call_theta_put_results[i][j] = calculate_theta(put_results, put_results_t_minus, i, j, t_step);
                }
            }
            cout << "\n\nTheta calcule :" << call_theta_put_results[grid_size * (1 - ((sigma_end - sigma_input) / (sigma_end - sigma_start)))][grid_size * (1 - ((S0_end - S0_input) / (S0_end - S0_start)))] << endl;
            plot_surface(grid_size, call_theta_put_results, S0_start, s_step, sigma_start, vol_step,
                         "Surface Theta Put", "Theta", K, r, T, N);
        }

        cout << "\nAffichage termine." << endl;
        cout << "Appuyez sur Entree";
        cin.ignore();
        cin.get();
    }
    return 0;
}