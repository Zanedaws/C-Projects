#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

long *Array_Load_From_File(char *filename, int *size);
int Array_Save_To_File(char *filename, long *array, int size);
void medianQuick(long* array, int start, int end);
int medianPartition(long* array, int start, int end);
long median(long x, long y, long z);

long *Array_Load_From_File(char *filename, int *size)
{

    //open file
    FILE *fh = fopen(filename, "r");
    if (fh == NULL)
    {
        fprintf(stderr, "failed to open file properly\n");
        *size = 0;
        return NULL;
    }

    //get size of file in bytes
    fseek(fh, 0, SEEK_END);
    *size = ftell(fh) / sizeof(long);
    rewind(fh);

    //allocate array space
    long* arr = NULL;
    arr = malloc(sizeof(long) * (*size));

    //read the file
    int ver;
    ver = fread(arr, sizeof(long), (*size), fh);

    if(ver != *size)
    {
        fclose(fh);
        free(arr);
        exit(EXIT_FAILURE);
        return NULL;
    }

    //close file and return
    fclose(fh);
    return arr;
}


int Array_Save_To_File(char *filename, long *array, int size) 
{
  //open file
  FILE * fh = NULL;

  fh = fopen(filename, "wb");

  //check if file opened successfully
  if (size == 0)
  {
    fclose(fh);
    free(array); 
    return 0;
  }

  //number of written items
  int numWrit;


  //write to file
  numWrit = fwrite(array, sizeof(long), size, fh);

  //close file
  fclose(fh);

  //free array
  free(array);

  //return number of written values
  return numWrit;
}

void Quick_Sort(long* Array, int Size)
{
    medianQuick(Array, 0, Size - 1);
    return;
}

void medianQuick(long* array, int start, int end)
{   
    int med;
    if(start < end)
    {
        med = medianPartition(array, start, end);
        medianQuick(array,start, med - 1);
        medianQuick(array,med + 1, end);
    }
}

//returns the median index after sorting the partitions
int medianPartition(long* array, int start, int end)
{

    long pivot = array[end];

    long tmp;

    int i = start - 1;

    int j;
    for(j = start; j <= end; j++)
    {
        if(array[j] < pivot)
        {
            i++;
            tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
        }
    }
    tmp = array[i + 1];
    array[i + 1] = array[end];
    array[end] = tmp;
    return i + 1;

    // long x = array[start];
    // long y = array[(start + end) / 2];
    // long z = array[end];
    // int i = start - 1;
    // int j = end;
    // long tmp;

    // x = median(x,y,z);
    
    // while(1)
    // {
    //     do{
    //         j--;
    //     }while(array[j] > x);
    //     do{
    //         i++;
    //     }while(array[i] < x);
    //     if(i < j)
    //     {
    //         tmp = array[i];
    //         array[i] = array[j];
    //         array[j] = tmp;
    //     }
    //     else
    //         return j + 1;
    // }

}

long median(long x, long y, long z)
{
    if((x < y) != (x < z))
        return x;
    else if((y < x) != (y < z))
        return y;
    else
        return z;
}
