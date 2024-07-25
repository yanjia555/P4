

#include <vector>
#include "caldof.h"

std::vector<std::vector<int>> caldof(const std::vector<std::vector<int>>& Enode, int ndof) { //��Ҫ���ݵĲ����ǣ�ÿ����Ԫ�Ľڵ���ɡ�ÿ���ڵ����ɶ���
    int Nele = Enode.size();  
    int Esize = Enode[0].size() - 1; 


    std::vector<std::vector<int>> Edof(Nele, std::vector<int>(ndof * Esize + 1));



    for (int i = 0; i < Nele; i++) {  //����ÿ����Ԫ
        Edof[i][0] = i + 1;            
        for (int j = 0; j < Esize; j++) {  //����ÿ���ڵ㣬ÿ����Ԫ4���ڵ�
            //Edof[i][3 * j + 1] = 3 * (Enode[i][j + 1] - 1) + 1;
            //Edof[i][3 * j + 2] = 3 * (Enode[i][j + 1] - 1) + 2;
            //Edof[i][3 * j + 3] = 3 * (Enode[i][j + 1] - 1) + 3;
            Edof[i][ndof * j + 1] = ndof * (Enode[i][j + 1] - 1) + 1; 
            Edof[i][ndof * j + 2] = ndof * (Enode[i][j + 1] - 1) + 2;
            Edof[i][ndof * j + 3] = ndof * (Enode[i][j + 1] - 1) + 3;
        }

    }


   


    return Edof;
}