#include <stdio.h>
#include "struct_list.h"
#include <math.h>
// Calculate the maximum of two inputs (C does not include this natively)
#define max(X,Y) (((X) > (Y)) ? (X) : (Y))

void calc_correction(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data, struct properties *phys_prop, float *phi_prev, float *S_u_correct)
{
   int i, j, k;
   float theta_x, theta_y;
   float correction_w, correction_e, correction_s, correction_n;
   float correction_cds, correction_uds;

   // Store the previous iterations's solution
   for(i = 0; i < grid_data->npp; i++)
   {
      phi_prev[i] = cell_data[i].phi;
   }

   // Loop over interior cells only
   for(i=1; i<grid_data->nx+1; i++)
   {
      for(j = 1; j < grid_data->ny+1; j++)
      {
         k = i*grid_data->nyp + j;

         // remove the previous iteration's correction from the FVM coefficient array
         fvm_coeff[k].S_u -= S_u_correct[k];

         // Calculate factor theta_x to determine the flow direction in x-direction
         theta_x = max(0, phys_prop->Fx/fabs(phys_prop->Fx));

         // West correction
         correction_cds = 0.5*(phi_prev[k] + phi_prev[k-grid_data->nyp]);
         correction_uds = phi_prev[k]*theta_x + phi_prev[k+grid_data->nyp]*(1-theta_x);
         correction_w   = phys_prop->Fx*phys_prop->area_west*(correction_uds - correction_cds);
 
         // East correction
         correction_cds = 0.5*(phi_prev[k] + phi_prev[k+grid_data->nyp]);
         correction_uds = phi_prev[k-grid_data->nyp]*theta_x + phi_prev[k]*(1-theta_x);
         correction_e   = phys_prop->Fx*phys_prop->area_east*(correction_uds - correction_cds);

         // Calculate factor theta_y to determine the flow direction in y-direction
         theta_y = max(0, phys_prop->Fy/fabs(phys_prop->Fy));

         // South correction
         correction_cds = 0.5*(phi_prev[k-1] + phi_prev[k]);
         correction_uds = phi_prev[k-1]*theta_y + phi_prev[k]*(1-theta_y);
         correction_s   = phys_prop->Fy*phys_prop->area_south*(correction_uds - correction_cds);

         // North correction
         correction_cds = 0.5*(phi_prev[k+1] + phi_prev[k]);
         correction_uds = phi_prev[k]*theta_y + phi_prev[k+1]*(1-theta_y);
         correction_n   = phys_prop->Fy*phys_prop->area_north*(correction_uds - correction_cds);

         // Sum the corrections from each cardinal direction
         S_u_correct[k] = correction_w + correction_e + correction_s + correction_n;
        
         // Add the correction to the source term in the FVM coefficient matrix
         fvm_coeff[k].S_u += S_u_correct[k];

      }
   }

}
