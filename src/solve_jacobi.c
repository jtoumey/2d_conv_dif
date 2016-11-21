#include <stdio.h>
#include "struct_list.h"

void solve_jacobi(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data)
{
   int ii, jj, kk;
   float phi_adj_W, phi_adj_E, phi_adj_S, phi_adj_N;
   float eps = 0.0; // 10e-8;

   // Loop through all cells
/*
   for(ii = 0; ii < grid_data->np; ii++)
   {
      // As we step through the cells, identify those on the boundary and set the values of \phi beyond the boundary to 0.0

      // Identify West cells 
      if(ii < grid_data->ny)
      {
         phi_adj_W = 0.0;
      }
      else
      {
         phi_adj_W = cell_data[ii-grid_data->ny].phi;
      }

      // Identify East cells
      if(ii > (grid_data->np - grid_data->ny) && ii < grid_data->np)
      {
         phi_adj_E = 0.0;
      }
      else
      {
         phi_adj_E = cell_data[ii+grid_data->ny].phi;
      }

      // Identify South cells
      if(ii % grid_data->ny == 0) 
      {
         phi_adj_S = 0.0;
      }
      else
      {
         phi_adj_S = cell_data[ii-1].phi;
      }

      // Identify North cells
      if((ii+1) % grid_data->ny == 0) 
      {
         phi_adj_N = 0.0;
      }
      else
      {
         phi_adj_N = cell_data[ii+1].phi;
      }
*/
      // Now perform the actual Jacobi iteration step
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

         cell_data[kk].phi = (fvm_coeff[kk].a_W * phi_adj_W + fvm_coeff[kk].a_E * phi_adj_E + fvm_coeff[kk].a_S * phi_adj_S + fvm_coeff[kk].a_N * phi_adj_N + fvm_coeff[kk].S_u)/(fvm_coeff[kk].a_P + eps);
      }
   }


}
