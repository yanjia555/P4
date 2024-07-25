#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


// Function to write vtk file
void writeVTK(const std::vector<double>& XX, const std::vector<double>& YY, const std::vector<double>& ZZ,
              const std::vector<double>& displacements) {
    std::ofstream vtkFile("output.vtk");

    if (!vtkFile) {
        std::cerr << "Error opening vtk file." << std::endl;
        return;
    }

    vtkFile << "# vtk DataFile Version 3.0" << std::endl;
    vtkFile << "vtk output" << std::endl;
    vtkFile << "ASCII" << std::endl;
    vtkFile << "DATASET POLYDATA" << std::endl;
    vtkFile << "POINTS " << XX.size() << " double" << std::endl;

    for (size_t i = 0; i < XX.size(); ++i) {
        vtkFile << XX[i] << " " << YY[i] << " " << ZZ[i] << std::endl;
    }

    //vtkFile << "POLYGONS " << XX.size() / 3 << " " << XX.size() / 3 * 4 << std::endl;

    //for (size_t i = 0; i < XX.size(); i += 3) {
    //    vtkFile << "3 " << i << " " << i + 1 << " " << i + 2 << std::endl;
    //}

      vtkFile << "POINT_DATA " << XX.size() << std::endl;
    vtkFile << "VECTORS Displacements double" << std::endl;

    for (size_t i = 0; i < displacements.size(); i += 3) {
        vtkFile << displacements[i] << " " << displacements[i + 1] << " " << displacements[i + 2] << std::endl;
    }

    vtkFile.close();
}