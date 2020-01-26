#include "shell_array.h"
#include <stdio.h>

long *Array_Load_From_File(char *filename, int *size)
{
  //init array
  long *arr = NULL;

  //open file
  FILE *fh = open(filename, 'r');
  if (fh == NULL)
  {
    fclose(fh);
    return NULL;
  }

  //get size of file in bytes
  fseek(fh, 0, SEEK_END);
  *size = ftell(fh) / sizeof(long);
  rewind(fh);

  //allocate array space
  arr = malloc(size);

  //read the file
  ver = fread(arr, sizeof(long), (*size), fh);
    if(ver != size
    {
    fclose(fh);
    free(arr);
    return NULL;
    }

    //close file and return
    fclose(fh)
    return arr;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
  fh = fopen(filename, 'w');

  if (size == NULL || size == 0)
  {
    fclose(fh);
    free(array) return 0;
  }

  numWrit = fwrite(arr, sizeof(long), size, fh);

  fclose(fh)
    free(array) return numWrit;
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
  int h = 1;
  int i = 0;
  int j = 0;
  long tmp = 0;

  do
  {

    h = 3 * h + 1;

  } while (h < size);

  // while(h < size)
  // {
  //     h = 3 * h + 1;
  // }
  // h = (h - 1) / 3

  while (h > 0)
  {
    for (j = h; j < size; j++)
    {
      tmp =
    }
  }
}