#include <vector>

// Function to solve the linear system K*u = F
std::vector<double> solveq(
    const std::vector<std::vector<double>>& K,
    const std::vector<double>& f,
    const std::vector<std::vector<int>>& bc
) ;
