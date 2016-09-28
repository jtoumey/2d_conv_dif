// Main function
#include <stdio.h>
#include <stdlib.h>
#include "struct_list.h"


// Declarations of function prototypes
void calc_grid(struct block *grid_data, struct cell *cell_data);
void calc_fvm_coefficients(struct cell *cell_data);

// Main driver function
int main(void)
{
   int ii, jj, kk;

   // Define structs
   struct cell *cell_data;
   struct block *grid_data;

   grid_data = (struct block *)malloc(sizeof(struct block));
   // Enter inputs (replace with file parser later)
   grid_data->nx = 4;
   grid_data->ny = 3;
   grid_data->np = grid_data->nx*grid_data->ny;

   grid_data->xmin = 0.0;
   grid_data->xmax = 1.0;
   grid_data->ymin = 0.0;
   grid_data->ymax = 0.6;

   // Allocate memory
   cell_data = (struct cell *)malloc(grid_data->np * sizeof(struct cell));

   calc_grid(grid_data, cell_data);

   for(ii = 0; ii < grid_data->np; ii++)
   {
      printf("(%f, %f)\n",cell_data[ii].x, cell_data[ii].y);
   }
//   calc_fvm_coefficients()

   calc_fvm_coefficients(cell_data);
   return(0);
}
