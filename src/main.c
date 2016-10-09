#include <stdio.h>
#include <stdlib.h>
#include "struct_list.h"

// Declarations of function prototypes
void read_input(struct block *grid_data, struct properties *phys_prop);
void calc_grid(struct block *grid_data, struct cell *cell_data);
void initialize_properties(struct block *grid_data, struct cell *cell_data, struct properties *phys_prop);
void calc_fvm_coeff(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop);
void set_boundary_conditions(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop);
void solve_jacobi(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data);
void calc_residual(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data, float *resid, float *frp);
void write_results(struct block *grid_data, struct coeff *fvm_coeff, struct cell *cell_data);
// Debug
void write_coefficients(struct block *grid_data, struct coeff *fvm_coeff);

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
   grid_data->np = grid_data->nx*grid_data->ny; // Calculate total number of cells in the domain

   // Allocate memory for 1D arrays of structs for cell and coefficient data structures
   cell_data = (struct cell *)malloc(grid_data->np * sizeof(struct cell));
   fvm_coeff = (struct coeff *)malloc(grid_data->np * sizeof(struct coeff));

   // Perform grid calculations
   calc_grid(grid_data, cell_data);

   // Calculate physical property abbreviations 
   initialize_properties(grid_data, cell_data, phys_prop);
 
   // Calculate FVM coefficients for all cells (in the same manner)
   calc_fvm_coeff(grid_data, fvm_coeff, phys_prop);
   // Print the Coefficients 
// write_coefficients(grid_data, fvm_coeff);
 
   // Overwrite boundary cell coefficients to apply boundary conditions
   set_boundary_conditions(grid_data, fvm_coeff, phys_prop);

   write_coefficients(grid_data, fvm_coeff);
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
