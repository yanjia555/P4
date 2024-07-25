

#include <vector>
#include "caldof.h"

std::vector<std::vector<int>> caldof(const std::vector<std::vector<int>>& Enode, int ndof) { //需要传递的参数是，每个单元的节点组成、每个节点自由度数
    int Nele = Enode.size();  
    int Esize = Enode[0].size() - 1; 


    std::vector<std::vector<int>> Edof(Nele, std::vector<int>(ndof * Esize + 1));



    for (int i = 0; i < Nele; i++) {  //遍历每个单元
        Edof[i][0] = i + 1;            
        for (int j = 0; j < Esize; j++) {  //遍历每个节点，每个单元4个节点
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