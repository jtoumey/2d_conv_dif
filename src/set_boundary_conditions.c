#include "struct_list.h"

void set_boundary_conditions(struct block *grid_data)
{
   int ii, kk;

   // Adjust coefficients for West boundary, running S to N
   for(ii = 0; ii < ny; ii++)
   {
      fvm_coeff->a_W = 0.0;
      fvm_coeff->a_E = 

   }

   // Adjust coefficients for North boundary, running W to E
   for(ii = ny; ii < np; ii+ny)
   {

   kk = np - ny + 1;
   }
   // Adjust coefficients for South boundary, running W to E
   for(ii = 0; ii < kk; ii+ny)
   {


   }
   // Adjust coefficients for West boundary, running S to N
   for(ii = kk; ii < np; ii++)
   {


   }
}
