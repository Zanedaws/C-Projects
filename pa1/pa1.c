#include "shell_array.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    fprintf(stderr,"arguments missing");
    return 0;
  }

  int size = 0;

  long* array = NULL;
  array = Array_Load_From_File(argv[2], &size);
  

  long n_comp = 0;


  if(!strcmp(argv[1],"-a"))
  {
    Array_Shellsort(array, size, &n_comp);
  }


  int writ = 0;

  writ = Array_Save_To_File(argv[3],array,size);

  if(writ != size)
  {
    fprintf(stderr, "written != size of array");
    return 0;
  }

  printf("%ld\n",n_comp);

  return 0;
}