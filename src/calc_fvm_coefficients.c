#include <stdio.h>
#include "struct_list.h"

void calc_fvm_coefficients(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop)
{
   int ii;

   for(ii = 0; ii < grid_data.np; ii++)
   {
      fvm_coeff[ii].a_W = phys_prop->Difx*Aw + max(0,  phys_prop->Fx*Aw);
      fvm_coeff[ii].a_E = phys_prop->Difx*Ae + max(0, -phys_prop->Fx*Ae);
      fvm_coeff[ii].a_S = Ds*As + max(0,  Fs*As);
      fvm_coeff[ii].a_N = Dn*An + max(0, -Fn*An);

      fvm_coeff[ii].S_u = 0.0;
      fvm_coeff[ii].S_p = 0.0;
   }
}
