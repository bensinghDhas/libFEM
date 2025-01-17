#ifndef C_FEM_BASISFUNCTION_2D_TRIA_H
#define C_FEM_BASISFUNCTION_2D_TRIA_H

#include <vector>
#include <math.h>
#include <iostream>
#include <tuple>

#include "C_FEM_GaussPoint_2D_TRIA.h" 
#include "C_Matrix_Dense.h"

//! This class produces Lagrange basis functions at Gauss Points for a triangular element. It takes the polynomial order and a triangular Gauss point object as input.
class C_TriangleBasis
{
    public:
        int num_sp;
        C_Matrix_Dense* sp;
        C_Matrix_Dense* dsp;

        //! Class Constructor
        /*!
        \param order the order of the requested interpolation functions. 
        \param GP_Data object containing Gauss Point information, such as coordinate data.
        */

    C_TriangleBasis (int order, C_GaussPoint_2D_TRIA GP_Data)
    {
        if (order == 1)
        {
            num_sp = 3; 
            (*this).sp=new C_Matrix_Dense [GP_Data.num_GP];
            (*this).dsp=new C_Matrix_Dense [GP_Data.num_GP];
            for (int ii = 0; ii < GP_Data.num_GP; ii++)
            {
                double s = GP_Data.ptx[ii], t = GP_Data.pty[ii];
                (*this).sp[ii].reshape(1,num_sp);
                (*this).dsp[ii].reshape(2,num_sp);
                (*this).sp[ii]={1-s-t, s, t };

                (this -> dsp)[ii](0,0) = -1.0;
                (this -> dsp)[ii](0,1) = 1.0;
                (this -> dsp)[ii](0,2) = 0.0;

                (this -> dsp)[ii](1,0) = -1.0;
                (this -> dsp)[ii](1,1) = 0.0;
                (this -> dsp)[ii](1,2) = 1.0;

            }
            (*this).num_sp=num_sp;
        }
        else
        {
           // Quadratic
            num_sp = 6; 

            // Assign new, correctly-sized dense matrices to member variables
            (*this).sp = new C_Matrix_Dense [GP_Data.num_GP];
            (*this).dsp = new C_Matrix_Dense [GP_Data.num_GP];

            for (int ii = 0; ii < GP_Data.num_GP; ii++)
            {
                double s = GP_Data.ptx[ii];
                double t = GP_Data.pty[ii];
                (this -> sp)[ii].reshape(1,num_sp);
                (this -> dsp)[ii].reshape(2,num_sp);

                (this -> sp)[ii](0,0) = s*(2*s - 1);
                (this -> sp)[ii](0,1) = 4*s*t;
                (this -> sp)[ii](0,2) = 4*s*(1 - s - t);
                (this -> sp)[ii](0,3) = t*(2*t - 1);
                (this -> sp)[ii](0,4) = 4*t*(1 - s - t);
                (this -> sp)[ii](0,5) = (1 - s - t)*(2*(1 - s - t) - 1);

                (this -> dsp)[ii](0,0) = 4*s - 1;
                (this -> dsp)[ii](0,1) = 4*t;
                (this -> dsp)[ii](0,2) = 4 - 8*s - 4*t;
                (this -> dsp)[ii](0,3) = 0;
                (this -> dsp)[ii](0,4) = -4*t;
                (this -> dsp)[ii](0,5) = 4*t + 4*s - 3;

                (this -> dsp)[ii](1,0) = 0;
                (this -> dsp)[ii](1,1) = 4*s;
                (this -> dsp)[ii](1,2) = -4*s;
                (this -> dsp)[ii](1,3) = 4*t - 1;
                (this -> dsp)[ii](1,4) = 4 - 8*t - 4*s;
                (this -> dsp)[ii](1,5) = 4*t + 4*s - 3; 
            } 
        }
    }
    ~C_TriangleBasis()
    {
        delete [] (*this).sp;
        delete [] (*this).dsp;
    }
};
    
#endif