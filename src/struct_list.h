// Struct definitions

// Geometry structure: domain size, number of 
struct cell
{
   float x, y, z;
   float phi;
};

struct block
{
   int nx,ny,np;
   float xmin, xmax;
   float ymin, ymax;
   // Calculated
   float dx, dy;
};
