#include "struct_list.h"
#include <math.h>
// Calculate the maximum of two inputs (C does not include this natively)
#define max(X,Y) (((X) > (Y)) ? (X) : (Y))

void calc_correction(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop, float *phi_prev, float *S_u_correct)
{
   int i, j, k;
   float theta_x, theta_y;
   float correction_w, correction_e, correction_s, correction_n;

   for(i = 1; i < grid_data->nx - 1; i++)
   {
      for(j = 1; j < grid_data->ny - 1; j++)
      {
         k = i*grid_data->ny + j;
         // remove the previous iteration's correction from the FVM coefficient array
         fvm_coeff[i].S_u -= S_u_correct[i];

         theta_x = max(0, phys_prop->Fx/fabs(phys_prop->Fx));


         correction_w = phys_prop->Fx*phys_prop->area_west*(0.5*(phi_prev[i] + phi_prev[i-grid_data->ny]) - (phi_prev[i]*theta_x + phi_prev[i+grid_data->ny]*(1-theta_x)));
         correction_e = phys_prop->Fx*phys_prop->area_east*(0.5*(phi_prev[i] + phi_prev[i+grid_data->ny]) - (phi_prev[i-grid_data->ny]*theta_x + phi_prev[i]*(1-theta_x)));

         theta_y = max(0, phys_prop->Fy/fabs(phys_prop->Fy));

         correction_s = phys_prop->Fy*phys_prop->area_south*(0.5*(phi_prev[i-1] + phi_prev[i]) - (phi_prev[i-1]*theta_y + phi_prev[i]*(1-theta_y)));
         correction_n = phys_prop->Fy*phys_prop->area_north*(0.5*(phi_prev[i+1] + phi_prev[i]) - (phi_prev[i]*theta_y + phi_prev[i+1]*(1-theta_y)));
;

         S_u_correct[i] = correction_w + correction_e + correction_s + correction_n;

         fvm_coeff[i].S_u += S_u_correct[i];
         write_coefficients(grid_data, fvm_coeff);
      }
   }

}
