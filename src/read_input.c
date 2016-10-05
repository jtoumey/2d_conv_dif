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
         sscanf(buffer, "%*s %d", &grid_data->nx);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %d", &grid_data->ny);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &grid_data->xmin);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &grid_data->xmax);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &grid_data->ymin);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &grid_data->ymax);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &grid_data->phi_A);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &grid_data->phi_B);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &grid_data->phi_C);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &grid_data->phi_D);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &phys_prop->rho);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &phys_prop->gamma);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &phys_prop->u);
      }
      fgets(buffer, 100, fptr_input);
      if(buffer != NULL)
      {
         sscanf(buffer, "%*s %f", &phys_prop->v);
      }
   }   

   fclose(fptr_input);
}
