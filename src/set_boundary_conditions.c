#include <stdio.h>
#include "struct_list.h"
// Calculate the maximum of two inputs (C does not include this natively)
#define max(X,Y) (((X) > (Y)) ? (X) : (Y))

void set_boundary_conditions(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data, struct properties *phys_prop)
{
   int ii, jj, kk;

   float a_w_conv, a_e_conv, a_s_conv, a_n_conv;
   float a_w_diff, a_e_diff, a_s_diff, a_n_diff;

   int neumann = 1;

   // Adjust coefficients for West boundary, running S to N
   for(ii = grid_data->nyp+1; ii < grid_data->nyp*2-1; ii++)
   {
      //printf("\nWest boundary index: %d\n", ii);
      a_e_conv = max(0, -phys_prop->Fx * phys_prop->area_east); 
      a_e_diff = phys_prop->Difx * phys_prop->area_east;

      fvm_coeff[ii].a_W = 0.0;
      fvm_coeff[ii].a_E = a_e_diff + a_e_conv;
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Difx * phys_prop->area_west * grid_data->phi_A + grid_data->phi_A * max(0, phys_prop->Fx * phys_prop->area_west);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Difx*phys_prop->area_west + max(0, phys_prop->Fx * phys_prop->area_east));

   }

   // Adjust coefficients for South boundary, running W to E
   kk = grid_data->npp - grid_data->nyp + 1; // index of solved cell just E of SE cell in the corner of the domain
   for(ii = grid_data->nyp+1; ii < kk; ii += grid_data->nyp)
   {
      //printf("\nSouth bndry index: %d\n", ii);
      a_n_conv = max(0, -phys_prop->Fy * phys_prop->area_north); 
      a_n_diff = phys_prop->Dify * phys_prop->area_north;

      fvm_coeff[ii].a_S = 0.0;
      fvm_coeff[ii].a_N = a_n_conv + a_n_diff;
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Dify * phys_prop->area_south * grid_data->phi_C + grid_data->phi_C * max(0, phys_prop->Fy * phys_prop->area_south);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Dify*phys_prop->area_south + max(0, phys_prop->Fy * phys_prop->area_south));

   }

// neumann test infrastructure
   if(neumann == 0)
   {
   // Adjust coefficients for North boundary, running W to E
   for(ii = grid_data->nyp*2 - 2; ii < grid_data->npp-grid_data->nyp; ii += grid_data->nyp)
   {
      //printf("\nNorth bndry index: %d\n", ii);
      a_s_conv = max(0, phys_prop->Fy * phys_prop->area_south);
      a_s_diff = phys_prop->Dify * phys_prop->area_south; 

      fvm_coeff[ii].a_S = a_s_conv + a_s_diff;
      fvm_coeff[ii].a_N = 0.0;
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Dify * phys_prop->area_north * grid_data->phi_D + grid_data->phi_D * max(0, -phys_prop->Fy * phys_prop->area_north);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Dify*phys_prop->area_north + max(0, -phys_prop->Fy * phys_prop->area_south));

   }
   }
   else if(neumann == 1)
   {

   // Adjust coefficients for North boundary, running W to E
   for(ii = grid_data->nyp*2 - 2; ii < grid_data->npp-grid_data->nyp; ii += grid_data->nyp)
   {
      //printf("\nNorth bndry index: %d\n", ii);
      a_s_conv = max(0, phys_prop->Fy * phys_prop->area_south);
      a_s_diff = phys_prop->Dify * phys_prop->area_south; 

      fvm_coeff[ii].a_S = a_s_conv + a_s_diff;
      fvm_coeff[ii].a_N = 0.0;
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Dify * phys_prop->area_north * cell_data[ii+1].phi + cell_data[ii+1].phi * max(0, phys_prop->Fy * phys_prop->area_north);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Dify*phys_prop->area_north + max(0, -phys_prop->Fy * phys_prop->area_south));

   }

   }

   // Adjust coefficients for East boundary, running S to N
   kk = grid_data->npp - 2*grid_data->nyp + 1; // index of solved cell in SE corner of the domain
   for(ii = kk; ii < grid_data->npp - grid_data->nyp - 1; ii++)
   {
      //printf("\nEast bndry index: %d\n", ii);
      a_w_conv = max(0, phys_prop->Fx * phys_prop->area_west);
      a_w_diff = phys_prop->Difx * phys_prop->area_west;

      fvm_coeff[ii].a_W = a_w_conv + a_w_diff;
      fvm_coeff[ii].a_E = 0.0; 
      fvm_coeff[ii].S_u = fvm_coeff[ii].S_u + 2*phys_prop->Difx * phys_prop->area_east * grid_data->phi_B + grid_data->phi_B * max(0, -phys_prop->Fx * phys_prop->area_east);
      fvm_coeff[ii].S_p = fvm_coeff[ii].S_p + -(2*phys_prop->Difx*phys_prop->area_east + max(0, -phys_prop->Fx * phys_prop->area_west));

   }

   // Now that all coefficients are up to date, we can compute a_P for interior cells
   for(ii = 1; ii < grid_data->nx+1; ii++)
   {
      for(jj = 1; jj < grid_data->ny+1; jj++)
      {
         kk = ii*grid_data->nyp + jj;
         fvm_coeff[kk].a_P = fvm_coeff[kk].a_W + fvm_coeff[kk].a_E + fvm_coeff[kk].a_S + fvm_coeff[kk].a_N - fvm_coeff[kk].S_p;
      }
   }
}
