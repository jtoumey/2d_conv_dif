// Struct definitions

// Cell structure. Location and scalar value \phi
struct cell
{
   float x, y;
   float phi;
};

// Geometry structure 
struct block
{
   int nx, ny, np;
   float xmin, xmax;
   float ymin, ymax;
   // Boundary condition
   float phi_A, phi_B, phi_C, phi_D;
   // Calculated
   float dx, dy;
};

// Stores FVM coefficients associated with each cell
struct coeff
{
   float a_P, a_W, a_E, a_S, a_N;
   float S_u, S_p;
};

// Physical properties and convection/diffusion abbreviations
struct properties
{
   float Fx, Fy;
   float Difx, Dify;
   float u, v;
   float rho, gamma;
   // Cell face areas
   float area_west, area_east, area_south, area_north;
};

// Solver and numerical method information
struct settings
{
   int spatial_scheme;
   float tol;
};
