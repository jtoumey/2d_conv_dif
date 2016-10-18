#include <stdio.h>
#include "struct_list.h"
#include <string.h>

#define BUFFER_SIZE 100

void read_input(struct block *grid_data, struct properties *phys_prop, struct settings *solv_settings)
{

   FILE *fptr_input;
   char buffer[BUFFER_SIZE];
   char var_name[BUFFER_SIZE];
   char *buffer_ptr_reset;

   // Open the input file
   fptr_input = fopen("input.inp", "r");

   if(fptr_input == NULL)
   { 
      printf("*** Error opening the input file. ***\n");
   }

   while(fgets(buffer, BUFFER_SIZE, fptr_input))
   {
      buffer_ptr_reset = buffer;
      sscanf(buffer, "%s%*[^\n]", var_name);
      
      printf("buffer is: %s\n", var_name);

      if( !strncmp(var_name, "nx", BUFFER_SIZE))
      {
         printf("   buffer matches nx!\n");
         sscanf(buffer_ptr_reset, "%*s %d", &grid_data->nx);


         printf("the number of elements in x-dir: %i\n", grid_data->nx);
      }
      else if( !strncmp(var_name, "ny", BUFFER_SIZE))
      {
         printf("   buffer matches ny!\n");
         sscanf(buffer_ptr_reset, "%*s %d", &grid_data->ny);

         printf("the number of elements in y-dir: %i\n", grid_data->ny);
      }
      else
      {
         printf("no match :(\n");
      }



   }

/*

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
   fgets(buffer, 100, fptr_input);
   if(buffer != NULL)
   {
      sscanf(buffer, "%*s %f", &solv_settings->tol);
   }
*/
   printf("*** Successfully read input file. ***\n");

   fclose(fptr_input);
}
