// Main function
#include <stdio.h>
#include <stdlib.h>
#include "struct_list.h"


// Declarations of function prototypes
void calc_fvm_coefficients(struct cell *cell_data);


// Main driver function
int main(void)
{
   int np = 12;
   int nx = 4;
   int ny = 3;
   float x_max, y_max;
   int ii, jj, kk;
   float dx, dy;

   // Define structs
   struct cell *cell_data;

   // Allocate memory
   cell_data = (struct cell *)malloc(np * sizeof(struct cell));

   // Calculate grid
   x_max = 1.0;
   y_max = 0.6; 
   dx = x_max/nx;
   dy = y_max/ny;
   for(ii = 0; ii < nx; ii++)
   {
      for(jj = 0; jj < ny; jj++)
      {
         kk = ii*ny + jj;
         cell_data[kk].x = (ii + 0.5)*dx;
         cell_data[kk].y = (jj + 0.5)*dy;
      }
   }
   for(ii = 0; ii < np; ii++)
   {
      printf("(%f, %f)\n",cell_data[ii].x, cell_data[ii].y);
   }
//   calc_fvm_coefficients()

   calc_fvm_coefficients(cell_data);
   return(0);
}
