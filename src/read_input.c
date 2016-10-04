#include <stdio.h>
#include "struct_list.h"

void read_input(struct block *grid_data, struct properties *phys_prop)
{

   FILE *fptr_input;
   char buffer[100];

   fptr_input = fopen("input.inp", "r");
   printf("open input file\n");
//   fgets(buffer, 100, fptr_input);
/*
   if(fptr_input == NULL)
   { 
      printf("*** Error opening the input file. ***");
   }
*/
   fclose(fptr_input);
}
