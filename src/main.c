#include <stdio.h>
#include <stdlib.h>
#include "struct_list.h"
#include "function_prototypes.h"

// Main driver function
int main(void)
{
   int ii, jj, kk;
   int iter = 0;
   float resid = 1.0;
   float frp;

   float *phi_prev;
   float *S_u_correct;

   int neumann_bc = 1;

   // Define structs
   struct cell *cell_data;
   struct block *grid_data;
   struct coeff *fvm_coeff;
   struct properties *phys_prop;
   struct settings *solv_settings;

   // Allocate memory for the grid information and physical properties
   grid_data = (struct block *)malloc(sizeof(struct block));
   phys_prop = (struct properties *)malloc(sizeof(struct properties));
   solv_settings = (struct settings *)malloc(sizeof(struct settings));

   // Read data from the input file
   read_input(grid_data, phys_prop, solv_settings);
   grid_data->np = grid_data->nx*grid_data->ny; // Calculate total number of cells in the domain
 
   // Calculate padded ('p') indices
   grid_data->nxp = grid_data->nx + 2;
   grid_data->nyp = grid_data->ny + 2;
   grid_data->npp = grid_data->nxp * grid_data->nyp;

   printf("spatial_scheme = %i\n", solv_settings->spatial_scheme);

   // Allocate memory for 1D arrays of structs for cell and coefficient data structures
   cell_data = (struct cell *)malloc(grid_data->npp * sizeof(struct cell));
   fvm_coeff = (struct coeff *)malloc(grid_data->npp * sizeof(struct coeff));

   phi_prev    = (float *)malloc(grid_data->npp * sizeof(float));
   S_u_correct = (float *)malloc(grid_data->npp * sizeof(float));

   // Perform grid calculations
   calc_grid(grid_data, cell_data);

   // Calculate physical property abbreviations 
   initialize_properties(grid_data, cell_data, phys_prop, phi_prev, S_u_correct);
 
   // Calculate FVM coefficients for all cells (in the same manner)
   calc_fvm_coeff(grid_data, fvm_coeff, phys_prop);

   // Overwrite boundary cell coefficients to apply boundary conditions
   set_boundary_conditions(grid_data, fvm_coeff, phys_prop);

   // write_coefficients(grid_data, fvm_coeff);

   // Begin outer loop
   while(resid >= solv_settings->tol) 
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
      printf("*** Iteration: %5i; Residual: %12.8f; Normalization (frp): %12.8f\n",iter, resid, frp);
     
      if(solv_settings->spatial_scheme == 1)
      {
         calc_correction(grid_data, fvm_coeff, cell_data, phys_prop, phi_prev, S_u_correct);
      }

      if(neumann_bc == 1)
      {
         for(ii = grid_data->nyp*2 - 2; ii < grid_data->npp-grid_data->nyp; ii += grid_data->nyp)
         {
            cell_data[ii+1].phi = cell_data[ii].phi;
         }
   
      }
   }

   // Write the results to a file
   write_results(grid_data, fvm_coeff, cell_data); 

   return(0);
}
