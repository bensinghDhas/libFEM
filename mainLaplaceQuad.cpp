#include <eigen-3.4.0/Eigen/Dense> 
#include <eigen-3.4.0/Eigen/Sparse>

#include "C_GaussData.h" 
#include "C_Matrix_Sparse.h"
#include "C_Matrix_Dense.h"
#include "C_Mesh.h"

#include "f_ForcingVector.h"
#include "f_SolverInterfaces.h"


int main()
{
    C_GaussData2DQuad gpData(3);
    C_Mesh2D mesh;
    mesh.meshRectangle({0,1},{0,1},10,10);
    for (int i=0; i<gpData.num_GP; i++)
    {
        std::cout << gpData.ptx[i]<< ' ' << gpData.pty[i]<<' ' << gpData.wt[i]<<  '\n';
    }

    // for (const auto& node: mesh.nodes)
    // {
    //     std::cout << node[0]<< ';' << node[1]<<'\n';
    // }

    // for (const auto& element: mesh.elements)
    // {
    //     std::cout << element[0]<< ';' << element[1]<< ';'<< element[2]<< ';'<< element[3]<<'\n';
    // }
    


    return 0;
}