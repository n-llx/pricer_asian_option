#include "plot.hpp"
#include <cstdio>
#include <cmath>
#include <iostream>
#ifdef _WIN32
    #define POPEN _popen
    #define PCLOSE _pclose
#else
    #define POPEN popen
    #define PCLOSE pclose
#endif


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
    FILE *pipe = POPEN("gnuplot", "w");
    if (!pipe) return;

    const char *commonSetup =
        "set pm3d at s\n"
        "set hidden3d\n"
        "set xlabel 'Spot Price (S0)' offset 0,-1\n"
        "set ylabel 'Volatility (sigma)' offset 2,0\n"
        "set view 60, 30, 1.0, 1.1\n"
        "set dgrid3d %d,%d\n";

    #include <string>
    std::string titleStr = title; 
    #ifdef _WIN32
    fprintf(pipe, "set term wxt %d title '%s' enhanced noraise\n", window_id, titleStr.c_str());
    #else
    fprintf(pipe, "set term qt %d title '%s' enhanced\n", window_id, titleStr.c_str());
    #endif

    fprintf(pipe, commonSetup, grid_size + 1, grid_size + 1);
    fprintf(pipe, "set mouse\n");
    fprintf(pipe, "set pm3d at s\n");
    fprintf(pipe, "set zlabel '%s' offset 1,1,0\n", zlabel);
    fprintf(pipe, "set title '%s\\n{/*0.8 K=%.2f, r=%.2f, T=%.2f, N=%d}'\n", titleStr.c_str(), K, r, T, N);
    fprintf(pipe, "splot '-' u 1:2:3 with pm3d title '%s'\n", titleStr.c_str());
    

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
    fprintf(pipe, "pause mouse close\n");
    PCLOSE(pipe);
}
