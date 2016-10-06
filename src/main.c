// Main function
#include <stdio.h>
#include <stdlib.h>
#include "struct_list.h"
//e

// Declarations of function prototypes
void read_input(struct block *grid_data, struct properties *phys_prop);
void calc_grid(struct block *grid_data, struct cell *cell_data);
void calc_fvm_coeff(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop);
void set_boundary_conditions(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop);
void solve_jacobi(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data);
void calc_residual(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data, float *resid, float *frp);

// Main driver function
int main(void)
{
   int ii, jj, kk;
   int debug_mode = 1;
   int iter = 0;
   float resid = 1.0;
   float frp;
   float tol = 0.001;

   // Define structs
   struct cell *cell_data;
   struct block *grid_data;
   struct coeff *fvm_coeff;
   struct properties *phys_prop;


   grid_data = (struct block *)malloc(sizeof(struct block));
   phys_prop = (struct properties *)malloc(sizeof(struct properties));

   read_input(grid_data, phys_prop);

   // Enter inputs (replace with file parser later)
   grid_data->np = grid_data->nx*grid_data->ny;
   grid_data->dx = (grid_data->xmax-grid_data->xmin)/grid_data->nx;
   grid_data->dy = (grid_data->ymax-grid_data->ymin)/grid_data->ny;

//   printf("dx: %f\n",grid_data->dx);
//   printf("dy: %f\n",grid_data->dy);

   phys_prop->Fx = phys_prop->rho*phys_prop->u;
   phys_prop->Fy = phys_prop->rho*phys_prop->v;
   phys_prop->Difx = phys_prop->gamma/grid_data->dx;
   phys_prop->Dify = phys_prop->gamma/grid_data->dy;
 
   phys_prop->Aw = grid_data->dy; 
   phys_prop->Ae = grid_data->dy; 
   phys_prop->As = grid_data->dx; 
   phys_prop->An = grid_data->dx; 

   // Allocate memory for 1D arrays of structs for cell and coefficient data structures
   cell_data = (struct cell *)malloc(grid_data->np * sizeof(struct cell));
   fvm_coeff = (struct coeff *)malloc(grid_data->np * sizeof(struct coeff));
 
   for(ii=0;ii<grid_data->np;ii++)
   {
      cell_data[ii].phi = 0.0;
   }

   // Set cell centers
   calc_grid(grid_data, cell_data);
 
   // Calculate FVM coefficients for all cells (in the same manner)
   calc_fvm_coeff(grid_data, fvm_coeff, phys_prop);

   // Overwrite boundary cell coefficients to apply boundary conditions
   set_boundary_conditions(grid_data, fvm_coeff, phys_prop);

   // Begin outer loop
   while(resid >= tol && iter < 10)
   {
      // Solve the system via jacobi iteration
      solve_jacobi(grid_data, fvm_coeff, cell_data);

      // Calculate the residual
      calc_residual(grid_data, fvm_coeff, cell_data, &resid, &frp);
      printf("raw residual: %8.4f\n",resid);
      
      if(iter < 1)
      {
         frp = 1.0; 
      }
  //    resid = resid/frp;
      iter++;
      printf("*** Iteration: %5i; Residual: %6.4f; Normalization (frp): %6.4f\n",iter, resid, frp);
      if(debug_mode !=0)
      {
         for(ii = 0; ii < grid_data->np; ii++)
         {
            printf("Phi solution: %f\n",cell_data[ii].phi);
         }
      }
   }


   // Test print statements
   if(debug_mode !=0)
   {
      // Print the cell centers
      printf("|  Cell Index  |  (x_cen, y_cen)  |\n");
      printf("|==============|==================|\n");
      for(ii = 0; ii < grid_data->np; ii++)
      {
         printf("      [%3i]       (%6.4f, %6.4f)\n",ii,cell_data[ii].x, cell_data[ii].y);
      }

      // Print the Coefficients 
      printf("|   a_W   |   a_E   |   a_S   |   a_N   |   S_u   |   S_p   |\n");
      printf("|=========|=========|=========|=========|=========|=========|\n");
      for(ii = 0; ii < grid_data->np; ii++)
      {
         printf("   %5.3f     %5.3f     %5.3f     %5.3f     %5.3f     %5.3f  \n",fvm_coeff[ii].a_W, fvm_coeff[ii].a_E, fvm_coeff[ii].a_S,fvm_coeff[ii].a_N,fvm_coeff[ii].S_u,fvm_coeff[ii].S_p);
      }
   }
   return(0);
}
