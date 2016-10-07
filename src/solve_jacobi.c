#include <stdio.h>
#include "struct_list.h"

void solve_jacobi(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data)
{
   int ii;
   float phi_adj_W, phi_adj_E, phi_adj_S, phi_adj_N;

   // Loop through all cells
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

      // Now perform the actual Jacobi iteration step
      cell_data[ii].phi = (fvm_coeff[ii].a_W * phi_adj_W + fvm_coeff[ii].a_E * phi_adj_E + fvm_coeff[ii].a_S * phi_adj_S + fvm_coeff[ii].a_N * phi_adj_N + fvm_coeff[ii].S_u)/fvm_coeff[ii].a_P;

   }

}
