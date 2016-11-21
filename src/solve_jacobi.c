#include <stdio.h>
#include "struct_list.h"

void solve_jacobi(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data)
{
   int ii, jj, kk;
   float phi_adj_W, phi_adj_E, phi_adj_S, phi_adj_N;
   float eps = 0.0; // 10e-8;

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

         // Now perform the actual Jacobi iteration step
         cell_data[kk].phi = (fvm_coeff[kk].a_W * phi_adj_W + fvm_coeff[kk].a_E * phi_adj_E + fvm_coeff[kk].a_S * phi_adj_S + fvm_coeff[kk].a_N * phi_adj_N + fvm_coeff[kk].S_u)/(fvm_coeff[kk].a_P + eps);
      }
   }


}
