#include <stdio.h>
#include "struct_list.h"
#include <string.h>

void read_input(struct block *grid_data, struct properties *phys_prop)
{

   FILE *fptr_input;
   char buffer[100];

   fptr_input = fopen("input.inp", "r");

   if(fptr_input == NULL)
   { 
      printf("*** Error opening the input file. ***\n");
   }
   // The input file is fixed format, so move through line-by-line
   else
   {
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         puts(buffer);
         sscanf(buffer, "%*s %f", &grid_data->xmin);
         printf("The value from file is %f\n", grid_data->xmin);
//         if(strncmp()

      }

   }   

   fclose(fptr_input);
}
