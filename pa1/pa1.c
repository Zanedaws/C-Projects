#include "shell_array.h"
#include "shell_array.c"
#include <stdio.h>

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    fprintf(stderr,"arguments missing");
    return 0;
  }

  int size = NULL;

  long* array = NULL;
  array = Array_Load_From_File(argv[1], &size);
  
  if(array == NULL)
  {
    fprintf(stderr,"loading failed");
    return 0;
  }

  long n_comp = NULL;

  Array_Shellsort(array, size, &n_comp)

  
}