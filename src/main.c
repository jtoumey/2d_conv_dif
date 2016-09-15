// Main function
#include <stdio.h>
#include <stdlib.h>

// Struct definitions

// Geometry structure: domain size, number of 
struct geometry
{
   // Geometry bounds
   float x_min;
   float x_max; 
   float y_min;
   float y_max;

   // Grid spacing
   int nx;
   int ny;
};

// Declarations
void geometry_print(struct geometry *geom);

int main(void)
{
   // Define structs
   struct geometry grid;
   struct geometry *grid_ptr;

   // Allocate memory
   grid_ptr = malloc(sizeof(struct geometry));

   // Initialize
   grid_ptr->x_min = 0.0;
   grid_ptr->x_max = 1.0;
   grid_ptr->y_min = 0.0;
   grid_ptr->y_max = 1.5;

   grid_ptr->nx = 10;
   grid_ptr->ny =  6;

   // Define grid arrays and variables
   int np;
   float dx, dy;
   float x_loc[grid_ptr->nx];
   float y_loc[grid_ptr->ny];
   int ii;
   
   np = grid_ptr->nx*grid_ptr->ny;
   dx = (grid_ptr->x_max - grid_ptr->x_min)/grid_ptr->nx;
   dy = (grid_ptr->y_max - grid_ptr->y_min)/grid_ptr->ny;

   printf("--- x Cell Centers ---\n");
   for(ii = 0; ii < grid_ptr->nx; ii++)
   {
      x_loc[ii] = (ii + 0.5)*dx;
      printf("%f\n",x_loc[ii]);
   }
   printf("--- y Cell Centers ---\n");
   for(ii = 0; ii < grid_ptr->ny; ii++)
   {
      y_loc[ii] = (ii + 0.5)*dy;
      printf("%f\n",y_loc[ii]);
   }
   // Print structure contents
   geometry_print(grid_ptr);

   // Set up the grid

}

void geometry_print(struct geometry *geom)
{
  printf("\nGrid dimensions\n---------------\n"); 
  printf("   (x_min, x_max) = (%f, %f)\n", geom->x_min, geom->x_max); 
  printf("   (y_min, y_max) = (%f, %f)\n", geom->y_min, geom->y_max); 

}
