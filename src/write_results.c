#include <stdio.h>
#include <math.h>
#include "struct_list.h"


void write_results(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data)
{
   int ii, jj, kk;
   int plane_idx;
   FILE *fptr_output;
   FILE *fptr_coeff;
   FILE *fptr_diag;
   FILE *fptr_plane;

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


   // Print the value of \phi along the diagonal to examine numerical viscosity
   fptr_diag = fopen("phi_diag.dat", "w");
   for(ii = 1; ii < grid_data->nxp - 1; ii++)
   {
      kk = (ii + 1)*grid_data->nyp - 1 - ii;

      fprintf(fptr_diag,"%12.6f\t%12.6f\n", cell_data[kk].y, cell_data[kk].phi);

   }
   fclose(fptr_diag);


   // Print the value of \phi along the middle plane to examine numerical viscosity
   fptr_plane = fopen("phi_plane.dat", "w");
   plane_idx = floor(grid_data->nx/2)*grid_data->nyp + 1;
   for(ii = plane_idx; ii < plane_idx + grid_data->ny; ii++)
   {

      fprintf(fptr_plane, "%12.6f\t%12.6f\n", cell_data[ii].phi, cell_data[ii].y);

   }
   fclose(fptr_plane);
}
