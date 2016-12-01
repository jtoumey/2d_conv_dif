#include <stdio.h>
#include "struct_list.h"
#include <string.h>
#include <stdlib.h>

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
      exit(EXIT_FAILURE);
   }

   // Loop over the lines in the file, reading, testing, and saving each
   while(fgets(buffer, BUFFER_SIZE, fptr_input))
   {
      buffer_ptr_reset = buffer;
      sscanf(buffer, "%s%*[^\n]", var_name);

      // Find out which input parameter is on the current line and save it to the correct place in memory
      if( !strncmp(var_name, "nx", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %d", &grid_data->nx);
      }
      else if( !strncmp(var_name, "ny", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %d", &grid_data->ny);
      }
      else if( !strncmp(var_name, "xmin", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->xmin);
      }
      else if( !strncmp(var_name, "xmax", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->xmax);
      }
      else if( !strncmp(var_name, "ymin", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->ymin);
      }
      else if( !strncmp(var_name, "ymax", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->ymax);
      }
      else if( !strncmp(var_name, "phi_A", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->phi_A);
      }
      else if( !strncmp(var_name, "phi_B", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->phi_B);
      }
      else if( !strncmp(var_name, "phi_C", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->phi_C);
      }
      else if( !strncmp(var_name, "phi_D", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &grid_data->phi_D);
      }
      else if( !strncmp(var_name, "rho", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &phys_prop->rho);
      }
      else if( !strncmp(var_name, "gamma", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &phys_prop->gamma);
      }
      else if( !strncmp(var_name, "u", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &phys_prop->u);
      }
      else if( !strncmp(var_name, "v", BUFFER_SIZE))
      {
         sscanf(buffer_ptr_reset, "%*s %f", &phys_prop->v);
      }
      else if( !strncmp(var_name, "tol", BUFFER_SIZE))
      {
         // printf("   buffer matches tolerance!\n");
         sscanf(buffer_ptr_reset, "%*s %f", &solv_settings->tol);
         // printf("the tolerance: %f\n", solv_settings->tol);
      }
      else if( !strncmp(var_name, "spatial_scheme", BUFFER_SIZE))
      {
         // printf("   buffer matches tolerance!\n");
         sscanf(buffer_ptr_reset, "%*s %d", &solv_settings->spatial_scheme);
         // printf("the tolerance: %f\n", solv_settings->tol);
      }
      else
      {
         printf("*** Warning: Parameter %20s does not match any input parameters required by the code. ***\n", var_name);
         printf("***          Please examine your input file.                                          ***\n");
         exit(EXIT_FAILURE);
      }
   }
   if(feof(fptr_input))
   {
      // fgets terminated due to reaching EOF
      printf("*** End of file.                  ***\n");
      printf("*** Successfully read input file. ***\n");
   }
 
   fclose(fptr_input);
}
