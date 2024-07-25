#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <fstream>
#include "caldof.h"
#include "platere.h"
using namespace std;

// Function to solve the linear system K*u = F
std::vector<double> solveq(
    const std::vector<std::vector<double>>& K,
    const std::vector<double>& f,
    const std::vector<std::vector<int>>& bc
) {
    int nd = K.size();
    
    // Create fdof vector and initialize it
    std::vector<int> fdof(nd);
    for (int i = 0; i < nd; ++i) {
        fdof[i] = i + 1;         
    }
        

    // Initialize displacement vector
    std::vector<double> d(nd, 0.0); 
     

    // Extract pdof and dp from bc
    std::vector<int> pdof, dp; 
    for (const auto& row : bc) { //pdof和dp分别取bc的第1列，和第2列
        pdof.push_back(row[0]);
        dp.push_back(row[1]); 
    }
        
    // Remove pdof from fdof
    for (const auto& pd : pdof) {
        fdof.erase(std::remove(fdof.begin(), fdof.end(), pd), fdof.end());
    } 
         



    // Calculate intermediate_result = f(fdof) - K(fdof, pdof) * dp
    Eigen::VectorXd intermediate_result(fdof.size());
    for (int i = 0; i < fdof.size(); ++i) {
        int fdofi = fdof[i] - 1; // Adjusting index
        intermediate_result(i) = f[fdofi];
        for (int j = 0; j < pdof.size(); ++j) {
            int pdofj = pdof[j] - 1; // Adjusting index
            intermediate_result(i) -= K[fdofi][pdofj] * dp[j];
        }
    }
  
    

    // Calculate s = K(fdof, fdof)^(-1) * intermediate_result
    Eigen::MatrixXd Kfdof = Eigen::MatrixXd::Zero(fdof.size(), fdof.size());
    for (int i = 0; i < fdof.size(); ++i) {
        for (int j = 0; j < fdof.size(); ++j) {
            Kfdof(i, j) = K[fdof[i] - 1][fdof[j] - 1]; // Adjusting indices
        }
    }
     
    Eigen::VectorXd s = Kfdof.colPivHouseholderQr().solve(intermediate_result);

     


    // Assign values to d vector
    for (int i = 0; i < pdof.size(); ++i) {
        d[pdof[i] - 1] = dp[i]; // Adjusting index
    }
         


    for (int i = 0; i < fdof.size(); ++i) {
        d[fdof[i] - 1] = s(i); // Adjusting index
    }

             
        

    return d;
}