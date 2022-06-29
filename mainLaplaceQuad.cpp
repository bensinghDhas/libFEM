#include <eigen-3.4.0/Eigen/Dense>
#include <eigen-3.4.0/Eigen/Sparse>

#include "C_GaussData.h"
#include "C_FEM_BasisFunction_2D_QUAD.h"
#include "C_Matrix_Sparse.h"
#include "C_Matrix_Dense.h"
#include "C_Mesh.h"

#include "f_StiffnessLaplace.h"
#include "f_SolverInterfaces.h"

int main()
{
    C_GaussData2DQuad gpData(2);
    C_Mesh2D mesh;
    mesh.meshRectangle({0, 1}, {0, 1}, 10, 10);
    std::vector<int> bcNodes;

    int itNd = 0;
    for (auto nd : mesh.nodes)
    {
        // Left nodes
        if (abs(nd[0]) < 0.000001)
        {
            bcNodes.push_back(itNd);
        }
        // Right nodes
        if (abs(nd[0]) > 0.999999)
        {
            bcNodes.push_back(itNd);
        }
        // Top nodes
        if (abs(nd[1]) > 0.999999)
        {
            bcNodes.push_back(itNd);
        }
        // Bottom nodes
        if (abs(nd[1]) < 0.0000001)
        {
            bcNodes.push_back(itNd);
        }
        itNd++;
    }

    // std::cout << "Nodes\n";
    // for (auto el : mesh.nodes) {
    //     for (int i = 0; i < 2; i++) {
    //         std::cout << el[i] << ' ';
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << "Elements\n";
    // for (auto el : mesh.elements) {
    //     for (int i = 0; i < 4; i++) {
    //         std::cout << el[i] << ' ';
    //     }
    //     std::cout << '\n';
    // }

    C_Matrix_Sparse kGlob;
    C_QuadrilateralBasis feL(1, gpData);
    int itEl = 0;

    for (const auto &elCon : mesh.elements) {
        // std::cout << itEl;
        std::vector<std::vector<double>> elNodes = mesh.getElNodes(itEl);
        stiffnessLaplace(elNodes, elCon, kGlob, feL, gpData);
        // itEl++;
    }
    Eigen::VectorXd fGlob(mesh.num_Nd);
    for (int i=0; i<mesh.num_Nd; i++){
        fGlob(i)=1.0;
    }
    for (auto nd : bcNodes) {
        kGlob.row_NonSparseAssign(0.0, nd);
        kGlob.col_NonSparseAssign(0.0, nd);
        kGlob(nd, nd) = 1;
        fGlob(nd)=0;
    }

    Eigen::SparseMatrix<double> kG_eigen(mesh.num_Nd, mesh.num_Nd);
    convert_to_Eigen(kGlob, kG_eigen);
    Eigen::SimplicialLDLT< Eigen::SparseMatrix<double> > chol;
    chol.compute(kG_eigen);
    Eigen::VectorXd sol = chol.solve(fGlob);
    std::cout<< sol;
    return 0;
}