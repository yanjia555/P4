#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <fstream>
#include "caldof.h"
#include "platere.h"
using namespace std;


vector<vector<double>> assem(vector<vector<int>> edof, vector<vector<double>> K, vector<vector<vector<double>>> Ke) {
    int nie = edof.size();
    int n = edof[0].size();
    //vector<vector<int>> t(nie, vector<int>(n - 1));
    vector<vector<int>> t(nie, vector<int>(n - 1));

    for (int i = 0; i < nie; i++) {  //从第二列到最后一列的子矩阵提取到变量 t 中。
        for (int j = 1; j < n; j++) { // 创建了一个新的矩阵 t，其大小与 edof 相同，包含 edof 的第二列到最后一列的值。
            t[i][j - 1] = edof[i][j];
        }
    }
    

    for (int i = 0; i < nie; i++) {        
        for (int j = 0; j < n-1; j++) {    
            for (int k = 0; k <n-1; k++) {
                K [t[i][j]-1] [t[i][k]-1] += Ke[i][j][k]; 
              

            }
        }
    }


    return K;
}