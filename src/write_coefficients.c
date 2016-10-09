#include <stdio.h>
#include "struct_list.h"


void write_coefficients(struct block *grid_data, struct coeff *fvm_coeff)
{
   int ii;
   FILE *fptr_coeff;

   fptr_coeff = fopen("fvm_coeff.dat","w");
   fprintf(fptr_coeff,"|   a_W   |   a_E   |   a_S   |   a_N   |   S_u   |   S_p   |   a_P   \n");
   fprintf(fptr_coeff,"|=========|=========|=========|=========|=========|=========|=========|\n");
   for(ii = 0; ii < grid_data->np; ii++)
   {
      fprintf(fptr_coeff,"   %5.3f     %5.3f     %5.3f     %5.3f     %5.3f     %5.3f     %5.3f  \n",fvm_coeff[ii].a_W, fvm_coeff[ii].a_E, fvm_coeff[ii].a_S,fvm_coeff[ii].a_N,fvm_coeff[ii].S_u,fvm_coeff[ii].S_p, fvm_coeff[ii].a_P);
   }
   fclose(fptr_coeff);

}
