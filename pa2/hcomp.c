#include "hcomp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ZERO 0

int readFromFIle(char* filename, Tree** forest)
{
    FILE * fh = fopen(filename, "rb");

    if(fh == NULL)
    {
        fprintf(stderr, "file failed to open\n");
        return 0;
    }

    char tmp;
    int count = 0;
    int size = STARTSIZE;

    while(!feof(fh))
    {
        tmp = fgetc(fh);
        if(!feof(fh))
        {
            size = addTree(forest, tmp, &count, size);
        }
    }

    fclose(fh);

    sortForest(forest, count);

    return count;
}



int addTree(Tree** forest, char tmp, int* count, int size)
{
    int i;
    //check if character is already in forest
    for(i = 0; i < *count; i++)
    {
        if(forest[i] -> chr == tmp)
        {
            forest[i] -> freq += 1;
            return size;
        }
    }


    //if it isn't then check if the array is big enough, if not increase the size
    if(*count != 0 && *count - 1 < size)
    {
        forest[*count - 1] -> chr = tmp;
        forest[*count - 1] -> freq = 1;
    }
    else if(*count == 0)
    {
        forest[*count] -> chr = tmp;
        forest[*count] -> freq = 1;
        *count++;
    }
    else
    {
        forest = realloc(forest, sizeof(*forest) * (*count + size/4));
        size = *count + size/4;
        forest[*count - 1] -> chr = tmp;
        forest[*count - 1] -> freq = 1;
        *count++;
    }

    return size;
}


Tree* buildTree(Tree** forest, int size)
{
    Tree* root = malloc(sizeof(*root));
    root -> left = NULL;
    root -> right = NULL;
    root -> chr = '\0';
    root -> freq = 0;


    if(size > 1)
    {
        root -> left = forest[0];
        root -> right = forest[1];
        root -> freq = forest[0] -> freq + forest[1] -> freq;

        Tree** newForest = malloc(sizeof(Tree*) * size - 1);
        int i;
        int j = 0;
        for(i = 0; i < size - 1; i++)
        {
            if(j < size && forest[j] -> freq < root -> freq)
            {
                newForest[i] = forest[j];
                j++;
            }
            else
            {
                newForest[i] = root;
            }
        }

        root = buildTree(newForest, size - 1);
        return root;
    }
    return root;
}

void sortForest(Tree** forest, int size)
{
    //sequence value
    long h = 0;

    //indexing values
    long i = 0;
    long j = 0;

    //temp variables
    long tmp = 0;


    //getting max sequence value
    do
    {

        h = 3 * h + 1;

    } while (h < size);
    h = (h - 1) / 3;
    

    //shell sort --------------------------------------------------
    while (h > 0)
    {
        for (j = h; j < size; j++)
        {
            tmp = forest[j] -> freq;
            i = j;
            while (i >= h && forest[i-h] -> freq > tmp)
            {
                forest[i] -> freq = forest[i-h] -> freq;
                i = i - h;
                forest[i] -> freq = tmp;
            }
        }
        //decrement sequence
        h = (h - 1) / 3;
    }
    //shell sort --------------------------------------------------

    return;
}

int freqOutput(char* filename, Tree** forest, int size)
{
    FILE* fh = fopen(filename, "w");
    
    if(fh == NULL)
    {
        fclose(fh);
        fprintf(stderr,"failed to open freqOutput file.\n");
        return EXIT_FAILURE;
    }

    int written;
    int i;
    int j;
    long zero = ZERO;
    for(i = 0; i < 256; i++)
    {
        for(j = 0;j < size; j++)
        {
            if(forest[j] -> chr == (char)i)
            {
                written = fwrite(&(forest[j] -> freq), sizeof(long), 1, fh);
                if(written != 1)
                {
                    fprintf(stderr, "failed to write a freq.\n");
                    fclose(fh);
                    return EXIT_FAILURE;
                }
            }
        }
        if(j != size - 1)
        {
            written = fwrite(&(zero), sizeof(long), 1, fh);
            if(written != 1)
            {
                fprintf(stderr, "failed to write a ZERO freq.\n");
                fclose(fh);
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}