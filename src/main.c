#include <stdio.h>
#include <stdlib.h>
#include "struct_list.h"

// Declarations of function prototypes
void read_input(struct block *grid_data, struct properties *phys_prop);
void calc_grid(struct block *grid_data, struct cell *cell_data);
void calc_fvm_coeff(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop);
void set_boundary_conditions(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop);
void solve_jacobi(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data);
void calc_residual(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data, float *resid, float *frp);
void write_results(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data);

// Main driver function
int main(void)
{
   int ii, jj, kk;
   int iter = 0;
   float resid = 1.0;
   float frp;
   float tol = 0.0001;

   // Define structs
   struct cell *cell_data;
   struct block *grid_data;
   struct coeff *fvm_coeff;
   struct properties *phys_prop;

   // Allocate memory for the grid information and physical properties
   grid_data = (struct block *)malloc(sizeof(struct block));
   phys_prop = (struct properties *)malloc(sizeof(struct properties));

   // Read data from the input file
   read_input(grid_data, phys_prop);

   // Perform grid calculations and physical property shortcuts
   grid_data->np = grid_data->nx*grid_data->ny;
   grid_data->dx = (grid_data->xmax-grid_data->xmin)/grid_data->nx;
   grid_data->dy = (grid_data->ymax-grid_data->ymin)/grid_data->ny;

   // Compute flux and diffusion abbreviations
   phys_prop->Fx = phys_prop->rho*phys_prop->u;
   phys_prop->Fy = phys_prop->rho*phys_prop->v;
   phys_prop->Difx = phys_prop->gamma/grid_data->dx;
   phys_prop->Dify = phys_prop->gamma/grid_data->dy;
 
   // Specify cell face areas
   phys_prop->Aw = grid_data->dy; 
   phys_prop->Ae = grid_data->dy; 
   phys_prop->As = grid_data->dx; 
   phys_prop->An = grid_data->dx; 

   // Allocate memory for 1D arrays of structs for cell and coefficient data structures
   cell_data = (struct cell *)malloc(grid_data->np * sizeof(struct cell));
   fvm_coeff = (struct coeff *)malloc(grid_data->np * sizeof(struct coeff));
 
   // Initialize the calculation for scalar \phi
   for(ii=0;ii<grid_data->np;ii++)
   {
      cell_data[ii].phi = 0.0;
   }

   // Compute cell centers
   calc_grid(grid_data, cell_data);
 
   // Calculate FVM coefficients for all cells (in the same manner)
   calc_fvm_coeff(grid_data, fvm_coeff, phys_prop);

   // Overwrite boundary cell coefficients to apply boundary conditions
   set_boundary_conditions(grid_data, fvm_coeff, phys_prop);

   // Begin outer loop
   while(resid >= tol)
   {
      // Solve the system via jacobi iteration
      solve_jacobi(grid_data, fvm_coeff, cell_data);

      // Calculate the residual
      calc_residual(grid_data, fvm_coeff, cell_data, &resid, &frp);
      
      // Set the normalization factor to 1.0 on the first iteration. If the LHS is intialized as zero, this prevents divide-by-zero
      if(iter < 1)
      {
         frp = 1.0; 
      }
      // Calculate normalized global residual, increment the iteration count, print the iteration information
      resid = resid/frp;
      iter++;
      printf("*** Iteration: %5i; Residual: %6.4f; Normalization (frp): %6.4f\n",iter, resid, frp);
   }

   // Write the results to a file
   write_results(grid_data, fvm_coeff, cell_data); 

   return(0);
}
