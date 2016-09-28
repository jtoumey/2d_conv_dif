#include <stdio.h>
#include "struct_list.h"

void calc_fvm_coefficients(struct cell *cell_data)
{
   int ii = 5;
   printf("From calc_fvm_coefficients:\n   Cell %d coordinates = (%f, %f)\n",ii,cell_data[ii].x,cell_data[ii].y);
}
