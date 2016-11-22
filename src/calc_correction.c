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
   // Loop over interior cells only
   for(i=1; i<grid_data->nx+1; i++)
   {
      for(j = 1; j < grid_data->ny+1; j++)
      {
         k = i*grid_data->nyp + j;

  // for(i = 1; i < grid_data->nx - 1; i++)
 //  {
 //     for(j = 1; j < grid_data->ny - 1; j++)
 //     {
//         phi_prev[k] = cell_data[k].phi;

  //       k = i*grid_data->ny + j;
         phi_prev[k] = cell_data[k].phi;
         // remove the previous iteration's correction from the FVM coefficient array
         fvm_coeff[k].S_u -= S_u_correct[k];

         theta_x = max(0, phys_prop->Fx/fabs(phys_prop->Fx));

         correction_cds = 0.5*(phi_prev[k] + phi_prev[k-grid_data->nyp]);
         correction_uds = phi_prev[k]*theta_x + phi_prev[k+grid_data->nyp]*(1-theta_x);
         correction_w   = phys_prop->Fx*phys_prop->area_west*(correction_cds - correction_uds);
 
//         printf("CDS D-C*: %8.4f; UDS D-C*: %8.4f; Ttl Crtn: %8.4f\n", correction_cds, correction_uds, correction_w);

         correction_cds = 0.5*(phi_prev[k] + phi_prev[k+grid_data->nyp]);
         correction_uds = phi_prev[k-grid_data->nyp]*theta_x + phi_prev[k]*(1-theta_x);
         correction_e   = phys_prop->Fx*phys_prop->area_east*(correction_cds - correction_uds);
//         correction_e   = phys_prop->Fx*phys_prop->area_east*(0.5*(phi_prev[k] + phi_prev[k+grid_data->ny]) - (phi_prev[k-grid_data->ny]*theta_x + phi_prev[k]*(1-theta_x)));

         theta_y = max(0, phys_prop->Fy/fabs(phys_prop->Fy));

         correction_cds = 0.5*(phi_prev[k-1] + phi_prev[k]);
         correction_uds = phi_prev[k-1]*theta_y + phi_prev[k]*(1-theta_y);
         correction_s   = phys_prop->Fy*phys_prop->area_south*(correction_cds - correction_uds);
       //  correction_s = phys_prop->Fy*phys_prop->area_south*(0.5*(phi_prev[k-1] + phi_prev[k]) - (phi_prev[k-1]*theta_y + phi_prev[k]*(1-theta_y)));
         correction_cds = 0.5*(phi_prev[k+1] + phi_prev[k]);
         correction_uds = phi_prev[k]*theta_y + phi_prev[k+1]*(1-theta_y);
         correction_n   = phys_prop->Fy*phys_prop->area_north*(correction_cds - correction_uds);
//         correction_n = phys_prop->Fy*phys_prop->area_north*(0.5*(phi_prev[k+1] + phi_prev[k]) - (phi_prev[k]*theta_y + phi_prev[k+1]*(1-theta_y)));
;

         S_u_correct[k] = correction_w + correction_e + correction_s + correction_n;
        
          
 //        printf("correction at gp %4i = %12.9f\n", k, S_u_correct[i]);

         fvm_coeff[k].S_u += S_u_correct[k];
//         write_coefficients(grid_data, fvm_coeff);
      }
   }

}
