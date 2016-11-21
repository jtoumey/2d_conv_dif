#include <stdio.h>
#include <math.h>
#include "struct_list.h"



void calc_residual(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data, float *resid, float *frp)
{
   int ii, jj, kk;
   float phi_adj_W, phi_adj_E, phi_adj_S, phi_adj_N;
   float aP_phiP;
    
   // Initialize the residual and normalization factor sums to zero for the current iteration
   *resid = 0.0;
   *frp   = 0.0;
/*
   // Loop through all cells
   for(i = 0; i < grid_data->np; i++)
   {
      // As we step through the cells, identify those on the boundary and set the values of \phi beyond the boundary to 0.0

      // Identify West cells 
      if(i < grid_data->ny)
      {
         phi_adj_W = 0.0;
      }
      else
      {
         phi_adj_W = cell_data[i-grid_data->ny].phi;
      }

      // Identify East cells
      if(i > (grid_data->np - grid_data->ny) && i < grid_data->np)
      {
         phi_adj_E = 0.0;
      }
      else
      {
         phi_adj_E = cell_data[i+grid_data->ny].phi;
      }

      // Identify South cells
      if(i % grid_data->ny == 0) 
      {
         phi_adj_S = 0.0;
      }
      else
      {
         phi_adj_S = cell_data[i-1].phi;
      }

      // Identify North cells
      if((i+1) % grid_data->ny == 0) 
      {
         phi_adj_N = 0.0;
      }
      else
      {
         phi_adj_N = cell_data[i+1].phi;
      }
*/

   // Loop over interior cells only
   for(ii=1; ii<grid_data->nx+1; ii++)
   {
      for(jj = 1; jj < grid_data->ny+1; jj++)
      {
         kk = ii*grid_data->nyp + jj;

         phi_adj_W = cell_data[kk-grid_data->nyp].phi;
         phi_adj_E = cell_data[kk+grid_data->nyp].phi;
         phi_adj_S = cell_data[kk-1].phi;
         phi_adj_N = cell_data[kk+1].phi;

         // Sum the residuals 
         aP_phiP = fvm_coeff[kk].a_P * cell_data[kk].phi;
         *resid += fabs(fvm_coeff[kk].a_W * phi_adj_W + fvm_coeff[kk].a_E * phi_adj_E + fvm_coeff[kk].a_S * phi_adj_S + fvm_coeff[kk].a_N * phi_adj_N + fvm_coeff[kk].S_u - aP_phiP);

         // Sum the normalization factor
         *frp += fabs(aP_phiP);
      }
   }
  
}
