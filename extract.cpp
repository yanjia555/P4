
#include <vector>

using namespace std;

// Function to extract element displacements from the global displacement vector
std::vector<std::vector<double>> extract(const std::vector<std::vector<int>>& edof, const std::vector<double>& a) {
    int nie = edof.size();
    int n = edof[0].size();

    // Initialize the element displacement matrix
    std::vector<std::vector<double>> ed(nie, std::vector<double>(n - 1, 0.0));

    // Extract element displacements
    for (int i = 0; i < nie; ++i) {
        for (int j = 1; j < n; ++j) {
            int index = edof[i][j] - 1; 
            ed[i][j - 1] = a[index];
        }
    }

    return ed;
}