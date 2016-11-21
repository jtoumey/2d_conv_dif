#include <stdio.h>
#include "struct_list.h"


void write_results(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data)
{
   int ii, jj, kk;
   int debug_mode = 0;
   FILE *fptr_output;
   FILE *fptr_coeff;
   FILE *fptr_diag;

   // Print the value of \phi at each cell center in the domain
   fptr_output = fopen("phi.dat","w");
   for(ii = 1; ii < grid_data->nx+1; ii++)
   {
      for(jj = 1; jj < grid_data->ny + 1; jj++)
      {
         // Cells are in a 1D array, so convert the (i, j) indices to a cell index
         kk = ii*grid_data->nyp + jj;
         fprintf(fptr_output, "%12.6f\t%12.6f\t%12.6f\n", cell_data[kk].x, cell_data[kk].y, cell_data[kk].phi);
      }
      fprintf(fptr_output, "\n");
   }
   fclose(fptr_output);

   // For debugging, print the FVM coefficient data to a file
   if(debug_mode != 0)
   {

      fptr_coeff = fopen("fvm_coeff.dat","w");
      // Print the Coefficients 
      fprintf(fptr_coeff,"|   a_W   |   a_E   |   a_S   |   a_N   |   S_u   |   S_p   |\n");
      fprintf(fptr_coeff,"|=========|=========|=========|=========|=========|=========|\n");
      for(ii = 0; ii < grid_data->np; ii++)
      {
         fprintf(fptr_coeff,"   %5.3f     %5.3f     %5.3f     %5.3f     %5.3f     %5.3f  \n",fvm_coeff[ii].a_W, fvm_coeff[ii].a_E, fvm_coeff[ii].a_S,fvm_coeff[ii].a_N,fvm_coeff[ii].S_u,fvm_coeff[ii].S_p);
      }
   }
 
   // Print the value of \phi along the diagonal to examine numerical viscosity
   fptr_diag = fopen("phi_diag.dat", "w");
   for(ii = 0; ii < grid_data->nx; ii++)
   {
      jj = (ii + 1)*grid_data->ny - 1;
      kk = jj - ii;
      fprintf(fptr_diag,"%12.6f\t%12.6f\n", cell_data[kk].y, cell_data[kk].phi);

   }
}
