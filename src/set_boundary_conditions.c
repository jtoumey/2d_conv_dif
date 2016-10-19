#include <stdio.h>
#include "struct_list.h"
// Calculate the maximum of two inputs (C does not include this natively)
#define max(X,Y) (((X) > (Y)) ? (X) : (Y))

void set_boundary_conditions(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop)
{
   int ii, kk;

   float a_w_conv, a_e_conv, a_s_conv, a_n_conv;
   float a_w_diff, a_e_diff, a_s_diff, a_n_diff;

   // Adjust coefficients for West boundary, running S to N
   for(ii = 0; ii < grid_data->ny; ii++)
   {
//      printf("\nWest boundary index: %d\n", ii);
      a_e_conv = max(0, -phys_prop->Fx * phys_prop->area_east); 
      a_e_diff = phys_prop->Difx * phys_prop->area_east;

      fvm_coeff[ii].a_W = 0.0;
      fvm_coeff[ii].a_E = a_e_diff + a_e_conv;
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Difx * phys_prop->area_west * grid_data->phi_A + grid_data->phi_A * max(0, phys_prop->Fx * phys_prop->area_west);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Difx*phys_prop->area_west + max(0, phys_prop->Fx * phys_prop->area_east));

   }

   // Adjust coefficients for South boundary, running W to E
   kk = grid_data->np - grid_data->ny + 1;
   for(ii = 0; ii < kk; ii += grid_data->ny)
   {
 //     printf("\nSouth bndry index: %d\n", ii);
      a_n_conv = max(0, -phys_prop->Fy * phys_prop->area_north); 
      a_n_diff = phys_prop->Dify * phys_prop->area_north;

      fvm_coeff[ii].a_S = 0.0;
      fvm_coeff[ii].a_N = a_n_conv + a_n_diff;
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Dify * phys_prop->area_south * grid_data->phi_C + grid_data->phi_C * max(0, phys_prop->Fy * phys_prop->area_south);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Dify*phys_prop->area_south + max(0, phys_prop->Fy * phys_prop->area_south));

   }

   // Adjust coefficients for North boundary, running W to E
   for(ii = grid_data->ny - 1; ii < grid_data->np; ii += grid_data->ny)
   {
  //    printf("\nNorth bndry index: %d\n", ii);
      a_s_conv = max(0, phys_prop->Fy * phys_prop->area_south);
      a_s_diff = phys_prop->Dify * phys_prop->area_south; 

      fvm_coeff[ii].a_S = a_s_conv + a_s_diff;
      fvm_coeff[ii].a_N = 0.0;
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Dify * phys_prop->area_north * grid_data->phi_D + grid_data->phi_D * max(0, -phys_prop->Fy * phys_prop->area_north);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Dify*phys_prop->area_north + max(0, -phys_prop->Fy * phys_prop->area_south));

   }

   // Adjust coefficients for East boundary, running S to N
   kk = kk - 1;
   for(ii = kk; ii < grid_data->np; ii++)
   {
   //   printf("\nEast bndry index: %d\n", ii);
      a_w_conv = max(0, phys_prop->Fx * phys_prop->area_west);
      a_w_diff = phys_prop->Difx * phys_prop->area_west;

      fvm_coeff[ii].a_W = a_w_conv + a_w_diff;
      fvm_coeff[ii].a_E = 0.0; 
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Difx * phys_prop->area_east * grid_data->phi_B + grid_data->phi_B * max(0, -phys_prop->Fx * phys_prop->area_east);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Difx*phys_prop->area_east + max(0, -phys_prop->Fx * phys_prop->area_west));

   }

   // Now that all coefficients are up to date, we can compute a_P
   for(ii = 0; ii < grid_data->np; ii++)
   {
      fvm_coeff[ii].a_P = fvm_coeff[ii].a_W + fvm_coeff[ii].a_E + fvm_coeff[ii].a_S + fvm_coeff[ii].a_N - fvm_coeff[ii].S_p;

   }
}
