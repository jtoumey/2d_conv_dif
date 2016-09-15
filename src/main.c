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

   // Print structure contents
   geometry_print(grid_ptr);

}

void geometry_print(struct geometry *geom)
{
  printf("\nGrid dimensions\n---------------\n"); 
  printf("   (x_min, x_max) = (%f, %f)\n", geom->x_min, geom->x_max); 
  printf("   (y_min, y_max) = (%f, %f)\n", geom->y_min, geom->y_max); 

}
