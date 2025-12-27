#include "plot.hpp"
#include <cstdio>
#include <cmath>
#include <iostream>

// Note: only `plot_surface` is exported/used. Keep implementation minimal.

void plot_surface(int grid_size,
                  const std::vector<std::vector<double>> &results,
                  double S0_start, double s_step,
                  double sigma_start, double vol_step,
                  const char *title,
                  const char *zlabel,
                  double K, double r, double T, int N,
                  int window_id)
{
    FILE *pipe = _popen("gnuplot -persist", "w");
    if (!pipe) return;

    const char *commonSetup =
        "set pm3d at s\n"
        "set hidden3d\n"
        "set xlabel 'Spot Price (S0)' offset 0,-1\n"
        "set ylabel 'Volatility (sigma)' offset 2,0\n"
        "set view 60, 30, 1.0, 1.1\n"
        "set dgrid3d %d,%d\n";

    fprintf(pipe, "set term wxt %d title '%s' enhanced noraise\n", window_id, title);
    fprintf(pipe, commonSetup, grid_size + 1, grid_size + 1);
    fprintf(pipe, "set pm3d at s\n");
    fprintf(pipe, "set zlabel '%s' offset 1,1,0\n", zlabel);
    fprintf(pipe, "set title '%s\\n{/*0.8 K=%.2f, r=%.2f, T=%.2f, N=%d}'\n", title, K, r, T, N);
    fprintf(pipe, "splot '-' u 1:2:3 with pm3d title '%s'\n", title);

    for (int i = 0; i <= grid_size; ++i)
    {
        for (int j = 0; j <= grid_size; ++j)
        {
            double current_sigma = sigma_start + i * vol_step;
            double current_S0 = S0_start + j * s_step;
            fprintf(pipe, "%f %f %f\n", current_S0, current_sigma, results[i][j]);
        }
        fprintf(pipe, "\n");
    }

    fprintf(pipe, "e\n");
    fflush(pipe);
    _pclose(pipe);
}
