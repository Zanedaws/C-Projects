#include "shell_array.h"
#include <stdio.h>


long *Array_Load_From_File(char* filename, int *size)
{
    //init array
    long * arr = NULL;
    
    //open file
    FILE * fh = open(filename, 'r');
    if(fh == NULL)
    {
        fclose(fh);
        return NULL;
    }

    //get size of file in bytes
    fseek(fh,0,SEEK_END);
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
    
}

