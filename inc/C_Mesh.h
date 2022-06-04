#ifndef C_MESH_H
#define C_MESH_H

#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "f_MiscellaneousFunctions.h"

/*Base mesh class for all 1D, 2D and 3D mesh*/
class C_Mesh{
    public:
        std::vector< std::vector<double> > nodes;
        std::vector< std::vector<int> >    elements;
        int num_NPE; //! Nodes per element
        int num_Nd; //! Total number of nodes
        int num_El; //! Total number of elements
        int dim;     //! Dimension of mesh

    C_Mesh() {}
};

#endif