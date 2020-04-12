#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

long *Array_Load_From_File(char *filename, int *size);
int Array_Save_To_File(char *filename, long *array, int size);
void medianQuick(long* array, int start, int end);
int Partition(long* array, int start, int end);
long median(long x, long y, long z);
void swap(long* a, long* b);
void compSwap(long* a, long* b);

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
    if(start >= end)
        return;
    
    int i;
    swap(&array[(start + end) / 2], &array[end-1]);

    compSwap(&array[start], &array[end - 1]);
    compSwap(&array[start], &array[end]);
    compSwap(&array[end - 1], &array[end]);

    i = Partition(array, start, end);
    medianQuick(array, start, i - 1);
    medianQuick(array, i + 1, end);

    // int med;
    // if(start < end)
    // {
    //     med = Partition(array, start, end);
    //     medianQuick(array,start, med - 1);
    //     medianQuick(array,med + 1, end);
    // }
}

void compSwap(long* a, long* b)
{
    if(*a > *b)
        swap(a, b);
    return;
}

//returns the median index after sorting the partitions
int Partition(long* array, int start, int end)
{

    // long pivot = array[end];

    // long tmp;

    // int i = start - 1;

    // int j;
    // for(j = start; j <= end; j++)
    // {
    //     if(array[j] < pivot)
    //     {
    //         i++;
    //         tmp = array[j];
    //         array[j] = array[i];
    //         array[i] = tmp;
    //     }
    // }
    // tmp = array[i + 1];
    // array[i + 1] = array[end];
    // array[end] = tmp;
    // return i + 1;

    int i = start;
    int j = end - 1;
    long v = array[end];

    for(;;)
    {
        while(array[i] < v)
            i++;
        while(array[j] > v)
        {
            j--;
            if(j == 1)
                break;
        }
        if (i >= j) 
            break;
        else
            swap(&array[i], &array[j]);
    }
    swap(&array[i], &array[end]);
    return i;
}

void swap(long* a, long* b)
{
    long tmp = (*a);
    (*a) = (*b);
    (*b) = tmp;
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
