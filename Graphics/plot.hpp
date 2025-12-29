#pragma once
#include <vector>

void plot_surface(int grid_size,
                  const std::vector<std::vector<double>> &results,
                  double S0_start, double s_step,
                  double sigma_start, double vol_step,
                  const char *title,
                  const char *zlabel,
                  double K, double r, double T, int N);
