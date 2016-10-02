#include <stdio.h>

#include "struct_list.h"

void solve_jacobi(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data)
{
   int ii;

   for(ii = 0; ii < grid_data->np; ii++)
   {
   
      cell_data[ii].phi = (fvm_coeff[ii].a_W * cell_data[ii-grid_data->ny].phi + fvm_coeff[ii].a_E * cell_data[ii+grid_data->ny].phi + fvm_coeff[ii].a_S * cell_data[ii-1].phi + fvm_coeff[ii].a_N * cell_data[ii+1].phi)/fvm_coeff[ii].a_P;

   }


}
