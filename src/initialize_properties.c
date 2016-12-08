#include <stdio.h>
#include "struct_list.h"


void initialize_properties(struct block *grid_data, struct cell *cell_data, struct properties *phys_prop, float *phi_prev, float *S_u_correct)
{
   int ii, jj, kk;

   int neumann = 1;

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
   // Loop over all cells (boundary and interior)
   for(ii = 0; ii < grid_data->npp; ii++)
   {
      cell_data[ii].phi = 0.0;
      
      phi_prev[ii]    = 0.0;
      S_u_correct[ii] = 0.0;
   }
   // Overwrite West dummy cells with Dirichlet condition
   for(ii = 0; ii < grid_data->nyp; ii++)
   {
      cell_data[ii].phi = grid_data->phi_A;
   }

   // Overwrite East dummy cells with Dirichlet condition
   for(ii = grid_data->npp-grid_data->nyp-1; ii < grid_data->npp; ii++)
   {
      cell_data[ii].phi = grid_data->phi_B;
   }

   // Overwrite South dummy cells with Dirichlet condition
   for(ii = 0; ii < grid_data->npp-1; ii+=grid_data->nyp)
   {
      cell_data[ii].phi = grid_data->phi_C;
   }

   if(neumann == 0)
   {
   // Overwrite North dummy cells with Dirichlet condition
   for(ii = grid_data->nyp-1; ii < grid_data->npp; ii+=grid_data->nyp)
   {
      cell_data[ii].phi = grid_data->phi_D;
   }
   }
   else if(neumann == 1)
   {
   for(ii = grid_data->nyp-1; ii < grid_data->npp; ii+=grid_data->nyp)
   {
      cell_data[ii].phi = cell_data[ii-1].phi;
   }
   }

}
