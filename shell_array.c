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
  fclose(fh);
  return arr;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
  //open file
  fh = fopen(filename, 'w');

  //check if file opened successfully
  if (size == NULL || size == 0)
  {
    fclose(fh);
    free(array); 
    return 0;
  }

  //number of written items
  int numWrit;

  //write to file
  numWrit = fwrite(arr, sizeof(long), size, fh);

  //close file
  fclose(fh);

  //free array
  free(array);

  //return number of written values
  return numWrit;
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
  //sequence value
  int h = 1;

  //indexing values
  int i = 0;
  int j = 0;

  //temp variables
  long tmp = 0;


  //getting max sequence value
  do
  {

    h = 3 * h + 1;

  } while (h < size);

  // while(h < size)
  // {
  //     h = 3 * h + 1;
  // }
  // h = (h - 1) / 3


  //shell sort --------------------------------------------------
  while (h > 0)
  {
    for (j = h; j < size; j++)
    {
      tmp = array[j];
      i = j
      while (i >= h && r[i-h] > tmp)
      {
        r[i] = r[i-h];
        i = i - h;
        r[i] = tmp;
      }
    }
    //decrement sequence
    h = (h - 1) / 3;
  }
  //shell sort --------------------------------------------------

  return;
}