// Main function
#include <stdio.h>

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
void geometry_print(struct geometry);

int main(void)
{
   // Define structs
   struct geometry grid;

   // Initialize
   grid.x_min = 0.0;
   grid.x_max = 1.0;
   grid.y_min = 0.0;
   grid.y_max = 1.5;

   grid.nx = 10;
   grid.ny =  6;

   // Print structure contents
   geometry_print(grid);

}

void geometry_print(struct geometry geom_info)
{
  printf("\nGrid dimensions\n---------------\n"); 
  printf("   (x_min, x_max) = (%f, %f)\n", geom_info.x_min, geom_info.x_max); 
  printf("   (y_min, y_max) = (%f, %f)\n", geom_info.y_min, geom_info.y_max); 

}
