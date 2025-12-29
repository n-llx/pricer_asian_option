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

void plot_surface(int grid_size,
                  const std::vector<std::vector<double>> &results,
                  double x_start, double x_step,
                  double y_start, double y_step,
                  const char *title,
                  const char *zlabel,
                  const char *xlabel,
                  const char *ylabel,
                  double K, double r, double T, int N)
{
    FILE *pipe = POPEN("gnuplot", "w");
    if (!pipe) return;

    // Use %s to make labels dynamic
    const char *commonSetup =
        "set pm3d at s\n"
        "set hidden3d\n"
        "set xlabel '%s' offset 0,-1\n"  // Dynamic
        "set ylabel '%s' offset 2,0\n"   // Dynamic
        "set view 60, 30, 1.0, 1.1\n"
        "set dgrid3d %d,%d\n";

    std::string titleStr = title;
#ifdef _WIN32
    fprintf(pipe, "set term wxt title '%s' enhanced noraise\n", titleStr.c_str());
#else
    fprintf(pipe, "set term qt title '%s' enhanced\n", titleStr.c_str());
#endif

    // Pass the xlabel and ylabel here
    fprintf(pipe, commonSetup, xlabel, ylabel, grid_size + 1, grid_size + 1);
    
    fprintf(pipe, "set mouse\n");
    fprintf(pipe, "set zlabel '%s' offset 1,1,0\n", zlabel);
    fprintf(pipe, "set title '%s\\n{/*0.8 K=%.2f, r=%.2f, T=%.2f, N=%d}'\n", titleStr.c_str(), K, r, T, N);
    fprintf(pipe, "splot '-' u 1:2:3 with pm3d title '%s'\n", titleStr.c_str());

    for (int i = 0; i <= grid_size; ++i) {
        for (int j = 0; j <= grid_size; ++j) {
            double val_y = y_start + i * y_step; // Usually the outer loop (rows)
            double val_x = x_start + j * x_step; // Usually the inner loop (cols)
            fprintf(pipe, "%f %f %f\n", val_x, val_y, results[i][j]);
        }
        fprintf(pipe, "\n");
    }

    fprintf(pipe, "e\n");
    fflush(pipe);
    fprintf(pipe, "pause mouse close\n");
    PCLOSE(pipe);
}