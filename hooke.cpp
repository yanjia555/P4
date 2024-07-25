

#include <vector>

#include "hooke.h"
using namespace std;


std::vector<std::vector<double>> hooke(double E, double v) {
    double factor = E / (1 - v * v);

    std::vector<std::vector<double>> D(3, std::vector<double>(3));

    D[0][0] = factor;
    D[0][1] = factor * v;
    D[0][2] = 0;

    D[1][0] = factor * v;
    D[1][1] = factor;
    D[1][2] = 0;

    D[2][0] = 0;
    D[2][1] = 0;
    D[2][2] = factor * (1 - v) / 2;

    return D;
}