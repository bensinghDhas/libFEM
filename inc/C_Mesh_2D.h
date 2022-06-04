#ifndef C_MESH_H
#define C_MESH_H

#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "f_MiscellaneousFunctions.h"
#include "C_Mesh.h"

/*Base mesh class for all 1D, 2D and 3D mesh*/
class C_Mesh_2D: public C_Mesh{
    C_Mesh_2D() {}
    void readMesh();
    void readNodes();
    void readElements();
};

#endif