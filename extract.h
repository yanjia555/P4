#pragma once

#include <vector>
// Function to extract element displacements from the global displacement vector

std::vector<std::vector<double>> extract(const std::vector<std::vector<int>>& edof, const std::vector<double>& a);