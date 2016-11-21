#include <stdio.h>
#include "struct_list.h"

void calc_grid(struct block *grid_data, struct cell *cell_data)
{
   int ii, jj, kk;

   grid_data->dx = (grid_data->xmax-grid_data->xmin)/grid_data->nx;
   grid_data->dy = (grid_data->ymax-grid_data->ymin)/grid_data->ny;
   
   // Discretize the domain
   // Use the kk index to treat only interior (solved) cells 
   for(ii = 1; ii < grid_data->nx+1; ii++)
   {
      for(jj = 1; jj < grid_data->ny + 1; jj++)
      {
         // Cells are in a 1D array, so convert the (i, j) indices to a cell index
         kk = ii*grid_data->nyp + jj;
 
         // Store the cell center of each cell
         cell_data[kk].x = (ii - 0.5)*grid_data->dx;
         cell_data[kk].y = (jj - 0.5)*grid_data->dy;
      }
   }
   
}
