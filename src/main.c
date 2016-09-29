// Main function
#include <stdio.h>
#include <stdlib.h>
#include "struct_list.h"


// Declarations of function prototypes
void calc_grid(struct block *grid_data, struct cell *cell_data);
void calc_fvm_coefficients(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop);

// Main driver function
int main(void)
{
   int ii, jj, kk;

   // Define structs
   struct cell *cell_data;
   struct block *grid_data;
   struct coeff *fvm_coeff;
   struct properties *phys_prop;

   grid_data = (struct block *)malloc(sizeof(struct block));
   phys_prop = (struct properties *)malloc(sizeof(struct properties));
   // Enter inputs (replace with file parser later)
   grid_data->nx = 4;
   grid_data->ny = 3;
   grid_data->np = grid_data->nx*grid_data->ny;

   grid_data->xmin = 0.0;
   grid_data->xmax = 1.0;
   grid_data->ymin = 0.0;
   grid_data->ymax = 0.6;

   phys_prop->rho = 1.4;
   phys_prop->gamma = 0.6;
   phys_prop->u = 0.8;
   phys_prop->v = 0.8;

   phys_prop->Fx = phys_prop->rho*phys_prop->u;
   phys_prop->Fy = phys_prop->rho*phys_prop->v;
   phys_prop->Difx = phys_prop->gamma/grid_data->dx;
   phys_prop->Dify = phys_prop->gamma/grid_data->dy;

   // Allocate memory
   cell_data = (struct cell *)malloc(grid_data->np * sizeof(struct cell));
   fvm_coeff = (struct coeff *)malloc(grid_data->np * sizeof(struct coeff));

   calc_grid(grid_data, cell_data);

   for(ii = 0; ii < grid_data->np; ii++)
   {
      printf("(%f, %f)\n",cell_data[ii].x, cell_data[ii].y);
   }
//   calc_fvm_coefficients()

   calc_fvm_coefficients(grid_data, fvm_coeff, phys_prop);
   return(0);
}
