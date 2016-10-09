#include <stdio.h>
#include "struct_list.h"

void calc_grid(struct block *grid_data, struct cell *cell_data)
{
   int ii, jj, kk;

   grid_data->dx = (grid_data->xmax-grid_data->xmin)/grid_data->nx;
   grid_data->dy = (grid_data->ymax-grid_data->ymin)/grid_data->ny;
   
   // Discretize the domain
   for(ii = 0; ii < grid_data->nx; ii++)
   {
      for(jj = 0; jj < grid_data->ny; jj++)
      {
         // Cells are in a 1D array, so convert the (i, j) indices to a cell index
         kk = ii*grid_data->ny + jj;
 
         // Store the cell center of each cell
         cell_data[kk].x = (ii + 0.5)*grid_data->dx;
         cell_data[kk].y = (jj + 0.5)*grid_data->dy;
      }
   }
   
}
