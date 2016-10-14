#include <stdio.h>
#include "struct_list.h"
// Calculate the maximum of two inputs (C does not include this natively)
#define max(X,Y) (((X) > (Y)) ? (X) : (Y))

void calc_fvm_coeff(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop)
{
   int ii;
   // Transport coefficients
   float a_Wc, a_Ec, a_Sc, a_Nc;
   float a_Wd, a_Ed, a_Sd, a_Nd;

   // Calculate convection transport coefficients 
   a_Wc = max(0,  phys_prop->Fx*phys_prop->Aw);
   a_Ec = max(0, -phys_prop->Fx*phys_prop->Ae);
   a_Sc = max(0,  phys_prop->Fy*phys_prop->As);
   a_Nc = max(0, -phys_prop->Fy*phys_prop->An);

   // Calculate diffusion transport coefficients
   a_Wd = phys_prop->Difx*phys_prop->Aw;
   a_Ed = phys_prop->Difx*phys_prop->Ae;
   a_Sd = phys_prop->Dify*phys_prop->As;
   a_Nd = phys_prop->Dify*phys_prop->An;

   // Loop over all cells, including boundary cells, and set the FVM coefficients for each
   // Additional routines overwrite the coefficient values at boundary cells
   for(ii = 0; ii < grid_data->np; ii++)
   {
      fvm_coeff[ii].a_W = a_Wc + a_Wd;
      fvm_coeff[ii].a_E = a_Ec + a_Ed;
      fvm_coeff[ii].a_S = a_Sc + a_Sd;
      fvm_coeff[ii].a_N = a_Nc + a_Nd;

      fvm_coeff[ii].S_u = 0.0;
      fvm_coeff[ii].S_p = 0.0;
   }
}
