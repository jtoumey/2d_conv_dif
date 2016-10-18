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
   fptr_input = fopen("input_alt.inp", "r");

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
      else if( !strncmp(var_name, "xmin", BUFFER_SIZE))
      {
         printf("   buffer matches xmin!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->xmin);

         printf("the min in x: %f\n", grid_data->xmin);
      }
      else if( !strncmp(var_name, "xmax", BUFFER_SIZE))
      {
         printf("   buffer matches xmax!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->xmax);

         printf("the max in x: %f\n", grid_data->xmax);
      }
      else if( !strncmp(var_name, "ymin", BUFFER_SIZE))
      {
         printf("   buffer matches ymin!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->ymin);

         printf("the min in y: %f\n", grid_data->ymin);
      }
      else if( !strncmp(var_name, "ymax", BUFFER_SIZE))
      {
         printf("   buffer matches ymax!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->ymax);

         printf("the max in y: %f\n", grid_data->ymax);
      }
      else if( !strncmp(var_name, "phi_A", BUFFER_SIZE))
      {
         printf("   buffer matches phi_A!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->phi_A);

         printf("the BC value at A: %f\n", grid_data->phi_A);
      }
      else if( !strncmp(var_name, "phi_B", BUFFER_SIZE))
      {
         printf("   buffer matches phi_B!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->phi_B);

         printf("the BC value at B: %f\n", grid_data->phi_B);
      }
      else if( !strncmp(var_name, "phi_C", BUFFER_SIZE))
      {
         printf("   buffer matches phi_C!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->phi_C);

         printf("the BC value at C: %f\n", grid_data->phi_C);
      }
      else if( !strncmp(var_name, "phi_D", BUFFER_SIZE))
      {
         printf("   buffer matches phi_D!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->phi_D);

         printf("the BC value at D: %f\n", grid_data->phi_D);
      }
      else if( !strncmp(var_name, "rho", BUFFER_SIZE))
      {
         printf("   buffer matches rho!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &phys_prop->rho);

         printf("the density rho: %f\n", phys_prop->rho);
      }
      else if( !strncmp(var_name, "gamma", BUFFER_SIZE))
      {
         printf("   buffer matches gamma!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &phys_prop->gamma);

         printf("the diffusion coeff gamma: %f\n", phys_prop->gamma);
      }
      else if( !strncmp(var_name, "u", BUFFER_SIZE))
      {
         printf("   buffer matches u vel!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &phys_prop->u);

         printf("the x-dir velocity: %f\n", phys_prop->u);
      }
      else if( !strncmp(var_name, "v", BUFFER_SIZE))
      {
         printf("   buffer matches v vel!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &phys_prop->v);

         printf("the v-dir velocity: %f\n", phys_prop->v);
      }
      else if( !strncmp(var_name, "tol", BUFFER_SIZE))
      {
         printf("   buffer matches tolerance!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &solv_settings->tol);

         printf("the tolerance: %f\n", solv_settings->tol);
      }
      else
      {
         printf("no match :(\n");
      }
   }
   printf("*** Successfully read input file. ***\n");

   fclose(fptr_input);
}
