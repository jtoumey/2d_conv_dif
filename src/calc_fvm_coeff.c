#include <stdio.h>
#include "struct_list.h"
// Calculate the maximum of two inputs (C does not include this natively)
#define max(X,Y) (((X) > (Y)) ? (X) : (Y))

void calc_fvm_coeff(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop)
{
   int ii, jj, kk;
   float a_w_conv, a_e_conv, a_s_conv, a_n_conv;
   float a_w_diff, a_e_diff, a_s_diff, a_n_diff;

   // Loop over interior cells and set the FVM coefficients for each
   // Additional routines overwrite the coefficient values at boundary cells
   for(ii=1; ii<grid_data->nx+1; ii++)
   {
      for(jj = 1; jj < grid_data->ny+1; jj++)
      {
         kk = ii*grid_data->nyp + jj;

      // Transport coefficient: convection
      a_w_conv = max(0,  phys_prop->Fx*phys_prop->area_west);
      a_e_conv = max(0, -phys_prop->Fx*phys_prop->area_east);
      a_s_conv = max(0,  phys_prop->Fy*phys_prop->area_south);
      a_n_conv = max(0, -phys_prop->Fy*phys_prop->area_north);

      // Transport coefficient: diffusion 
      a_w_diff = phys_prop->Difx*phys_prop->area_west;
      a_e_diff = phys_prop->Difx*phys_prop->area_east;
      a_s_diff = phys_prop->Dify*phys_prop->area_south; 
      a_n_diff = phys_prop->Dify*phys_prop->area_north;

      // Calculate coefficients
      fvm_coeff[kk].a_W = a_w_conv + a_w_diff; 
      fvm_coeff[kk].a_E = a_e_conv + a_e_diff; 
      fvm_coeff[kk].a_S = a_s_conv + a_s_diff; 
      fvm_coeff[kk].a_N = a_n_conv + a_n_diff; 

      fvm_coeff[kk].S_u = 0.0;
      fvm_coeff[kk].S_p = 0.0;
   }
   }
}
