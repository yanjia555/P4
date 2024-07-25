
#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <fstream>
#include "caldof.h"
#include "hooke.h"
#include "platere.h"
#include "assem.h"
#include "solveq.h"
#include "extract.h"
#include "output.h"
//using namespace std;





int main() {
    // Define the plate parameters
    int n_length = 10; // number of elements in the long side
    int m_width = 3;   // number of elements in the wide side
    double uni = 2.0;   // element size

    double E = 2.1e5;   // Young's modulus (MPa)
    double v = 0.3;     // Poisson's ratio
    double t = 1.0;     // thickness of the plate
    double ep = t;




    int num = 0;
    std::vector<std::vector<int>> Enode;
    std::vector<std::vector<double>> ex;   
    std::vector<std::vector<double>> ey;  

    // Generate grid
    for (int j = 1; j <= m_width; ++j) {
        for (int i = 1; i <= n_length; ++i) {
            num++;
            Enode.push_back({num, (j - 1) * (n_length + 1) + i, (j - 1) * (n_length + 1) + i + 1,
                            j * (n_length + 1) + i + 1, j * (n_length + 1) + i});
            
            ex.push_back({(i - 1) * uni, i * uni, i * uni, (i - 1) * uni});
            ey.push_back({(j - 1) * uni, (j - 1) * uni, j * uni, j * uni});
        }
    }


     int ndof = 3; 
    //生成单元自由度矩阵
    std::vector<std::vector<int>> Edof = caldof(Enode, ndof);

    std::vector<std::vector<double>>D=hooke(E, v);

    int nie =Enode.size();
    vector<vector<vector<double>>> Ke(nie);
    // 遍历每个元素
    for (int i = 0; i < nie; ++i) {
        // 调用 platere 函数计算刚度矩阵并将其赋值给 Ke[i]
         Ke[i] = platere(ex[i], ey[i], ep, D);
    }

    int maxEdof = 0;
    for (const auto& row : Edof) {
        for (int value : row) {
            maxEdof = std::max(maxEdof, value);
        }
    }
    // 总刚度矩阵
     std::vector<std::vector<double>> K(maxEdof, std::vector<double>(maxEdof, 0.0));
     K = assem(Edof, K, Ke);


    std::vector<double> f(ndof * ((m_width+1) * (n_length+1)), 0.0);

    std::vector<int> boundary_node(2 * (m_width + 1), 0); //宽度方向两侧约束。

    std::vector<std::vector<int>> bc(3 * boundary_node.size(), std::vector<int>(2, 0));

    f[60]=-400; 
    

       
     num = 0;

    // 找边界点
    for (int i = 0; i <= m_width; i++) {
        boundary_node[num] = i * (n_length + 1) + 1;
        num++;
        boundary_node[num] = (i + 1) * (n_length + 1);
        num++;
    }

    
      // 遍历 boundary_node
    for (int i = 0; i < boundary_node.size(); ++i) {
        // 计算索引
        int index = i * 3;

        // 在 bc 中添加对应的值
        bc[index][0] = 3 * (boundary_node[i] - 1) + 1;
        bc[index][1] = 0;

        bc[index + 1][0] = 3 * (boundary_node[i] - 1) + 2;
        bc[index + 1][1] = 0;

        bc[index + 2][0] = 3 * (boundary_node[i] - 1) + 3;
        bc[index + 2][1] = 0;
    }

    


      // Vector to store the solution
       std::vector<double> a = solveq(K,f,bc);





       std::vector<std::vector<double>> Ed=extract(Edof,a);//write disp in element form




//后处理


// Calculate deformation and prepare data for vtk file
    std::vector<double> XX, YY, ZZ, displacements;
  num = 0;

   for (int i = 1; i <= (m_width + 1); ++i) {
        for (int j = 1; j <= (n_length + 1); ++j) {
            num = num + 1;
            double xi = (j - 1) * uni;
            double yi = (i - 1) * uni;
            double zi = 0.0;  // Assuming a default value for displacement in the Z direction

            XX.push_back(xi);
            YY.push_back(yi);
            ZZ.push_back(zi);

            // Assuming 'a' contains enough data
            displacements.push_back(a[(num - 1) * 3]);
            displacements.push_back(a[(num - 1) * 3 + 1]);
            displacements.push_back(a[(num - 1) * 3 + 2]);
        }
    }

    // Write data to vtk file
    writeVTK(XX, YY, ZZ, displacements);



 return 0;
}