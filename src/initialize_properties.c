#include <stdio.h>
#include "struct_list.h"


void initialize_properties(struct block *grid_data, struct cell *cell_data, struct properties *phys_prop)
{
   int ii;

   // Specify cell face areas
   phys_prop->area_west  = grid_data->dy; 
   phys_prop->area_east  = grid_data->dy; 
   phys_prop->area_south = grid_data->dx; 
   phys_prop->area_north = grid_data->dx; 

   // Compute flux and diffusion abbreviations
   phys_prop->Fx = phys_prop->rho*phys_prop->u;
   phys_prop->Fy = phys_prop->rho*phys_prop->v;
   phys_prop->Difx = phys_prop->gamma/grid_data->dx;
   phys_prop->Dify = phys_prop->gamma/grid_data->dy;
 
   // Initialize the calculation for scalar \phi
   for(ii=0;ii<grid_data->np;ii++)
   {
      cell_data[ii].phi = 0.0;
   }

}
