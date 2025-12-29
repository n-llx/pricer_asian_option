#pragma once
#include <vector>

void plot_surface(int grid_size,
                  const std::vector<std::vector<double>> &results,
                  double x_start, double x_step,
                  double y_start, double y_step,
                  const char *title,
                  const char *zlabel,
                  const char *xlabel,  
                  const char *ylabel,  
                  double K, double r, double T, int N);