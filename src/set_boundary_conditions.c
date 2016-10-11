#include <stdio.h>
#include "struct_list.h"
// Calculate the maximum of two inputs (C does not include this natively)
#define max(X,Y) (((X) > (Y)) ? (X) : (Y))

void set_boundary_conditions(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop)
{
   int ii, kk;

   // Adjust coefficients for West boundary, running S to N
   for(ii = 0; ii < grid_data->ny; ii++)
   {
//      printf("\nWest boundary index: %d\n", ii);
      fvm_coeff[ii].a_W = 0.0;
      fvm_coeff[ii].a_E = phys_prop->Difx * phys_prop->Ae + max(0, -phys_prop->Fx * phys_prop->Ae); 
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Difx * phys_prop->Aw * grid_data->phi_A + grid_data->phi_A * max(0, phys_prop->Fx * phys_prop->Aw);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Difx*phys_prop->Aw + max(0, phys_prop->Fx * phys_prop->Ae));

   }

   // Adjust coefficients for South boundary, running W to E
   kk = grid_data->np - grid_data->ny + 1;
   for(ii = 0; ii < kk; ii += grid_data->ny)
   {
 //     printf("\nSouth bndry index: %d\n", ii);
      fvm_coeff[ii].a_S = 0.0;
      fvm_coeff[ii].a_N = phys_prop->Dify * phys_prop->An + max(0, -phys_prop->Fy * phys_prop->An); 
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Dify * phys_prop->As * grid_data->phi_C + grid_data->phi_C * max(0, phys_prop->Fy * phys_prop->As);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Dify*phys_prop->As + max(0, phys_prop->Fy * phys_prop->As));
 

   }

   // Adjust coefficients for North boundary, running W to E
   for(ii = grid_data->ny - 1; ii < grid_data->np; ii += grid_data->ny)
   {
  //    printf("\nNorth bndry index: %d\n", ii);
      fvm_coeff[ii].a_S = phys_prop->Dify * phys_prop->As + max(0, phys_prop->Fy * phys_prop->As);
      fvm_coeff[ii].a_N = 0.0;
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Dify * phys_prop->An * grid_data->phi_D - grid_data->phi_D * max(0, -phys_prop->Fy * phys_prop->An);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Dify*phys_prop->An + max(0, -phys_prop->Fy * phys_prop->As));

   }

   // Adjust coefficients for East boundary, running S to N
   kk = kk - 1;
   for(ii = kk; ii < grid_data->np; ii++)
   {
   //   printf("\nEast bndry index: %d\n", ii);
      fvm_coeff[ii].a_W = phys_prop->Difx * phys_prop->Aw + max(0, phys_prop->Fx * phys_prop->Aw);
      fvm_coeff[ii].a_E = 0.0; 
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Difx * phys_prop->Ae * grid_data->phi_B - grid_data->phi_B * max(0, -phys_prop->Fx * phys_prop->Ae);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Difx*phys_prop->Ae + max(0, -phys_prop->Fx * phys_prop->Aw));

   }

   // Now that all coefficients are up to date, we can compute a_P
   for(ii = 0; ii < grid_data->np; ii++)
   {
      fvm_coeff[ii].a_P = fvm_coeff[ii].a_W + fvm_coeff[ii].a_E + fvm_coeff[ii].a_S + fvm_coeff[ii].a_N - fvm_coeff[ii].S_p;

   }
}
