#include "Greeks.hpp"

double calculate_delta(const std::vector<std::vector<double>>& call_results, int i, int j, double s_step) {
    int grid_max_s = call_results[0].size() - 1;
    if (j > 0 && j < grid_max_s) {
        return (call_results[i][j + 1] - call_results[i][j - 1]) / (2.0 * s_step);
    } 
    else if (j == 0) {
        return (call_results[i][j + 1] - call_results[i][j]) / s_step;
    } 
    else {
        return (call_results[i][j] - call_results[i][j - 1]) / s_step;
    }
}