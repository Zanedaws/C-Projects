#include "sorting.h"
#include "sorting.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(long* array, int size);


int main(int argc, char** argv)
{

    if(argc != 4)
    {
        fprintf(stderr, "incorrect inputs\n");
        return EXIT_FAILURE;
    }
    
    if(!(strcmp(argv[1], "-q")))
    {
        int size = 0;
        long* array = Array_Load_From_File(argv[2], &size);

        fprintf(stderr, "size = %d\n", size);
        printArray(array, size);
        Quick_Sort(array, size);
        printArray(array, size);

        int written = Array_Save_To_File(argv[3], array, size);
        if(written != size){
            fprintf(stderr, "something went wrong saving\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

void printArray(long* array, int size)
{
    int i;
    for(i = 0; i < size; i++)
        fprintf(stderr, "%ld\n", array[i]);
    fprintf(stderr, "\n");
    return;
}