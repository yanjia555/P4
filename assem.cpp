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

    for (int i = 0; i < nie; i++) {  //�ӵڶ��е����һ�е��Ӿ�����ȡ������ t �С�
        for (int j = 1; j < n; j++) { // ������һ���µľ��� t�����С�� edof ��ͬ������ edof �ĵڶ��е����һ�е�ֵ��
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