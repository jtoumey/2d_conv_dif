// Struct definitions

// Geometry structure: domain size, number of 
struct cell
{
   float x, y, z;
   float phi;
};

struct block
{
   int nx, ny, np;
   float xmin, xmax;
   float ymin, ymax;
   // Calculated
   float dx, dy;
};

struct coeff
{
   float a_P, a_W, a_E, a_S, a_N;
   float S_u, S_p;
};

struct properties
{
   float Fx, Fy;
   float Difx, Dify;
   float u, v;
   float rho, gamma;
   float Aw, Ae, As, An;
};
