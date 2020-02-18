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
        return NULL;
    }

    char tmp = NULL;
    int count = 0;

    while(!feof(fh))
    {
        tmp = fgetc(fh);
        if(!feof(fh))
        {
            count = addTree(forest, tmp, count);
        }
    }

    fclose(fh);

    sortForest(forest, count);

    return count;
}



int addTree(Tree** forest, char tmp, int* count)
{
    int sizeE = sizeof(forest)/sizeof(*forest);

    count++;

    int i;
    //check if character is already in forest
    for(i = 0; i < count; i++)
    {
        if(forest[i] -> chr == tmp)
        {
            forest[i] -> freq += 1;
            return count;
        }
    }


    //if it isn't then check if the array is big enough, if not increase the size
    if(count - 1 < sizeE)
    {
        forest[count - 1] -> chr = tmp;
        forest[count - 1] -> freq = 1;
    }
    else
    {
        forest = realloc(forest, sizeof(*forest) * (sizeE + sizeE/4));
        forest[count - 1] -> chr = tmp;
        forest[count - 1] -> freq = 1;
    }

    return count;
}


Tree* buildTree(Tree** forest, int size)
{
    Tree* root = malloc(sizeof(*root));
    root -> left = NULL;
    root -> right = NULL;
    root -> chr = NULL;
    root -> freq = 0;


    if(size > 1)
    {
        Tree* root = malloc(sizeof(*root));
        root -> left = forest[0];
        root -> right = forest[1];
        root -> freq = forest[0] -> freq + forest[1] -> freq;

        Tree** newForest = malloc(sizeof(Tree*) * size - 1);
        int i;
        int j = 0;
        for(i = 0; i < size - 1, i++)
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
                array[i] -> freq = tmp;
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

    int i;
    int j;
    long zero = ZERO;
    for(i = 0; i < 256; i++)
    {
        for(j = 0;j < size; j++)
        {
            if(forest[j] -> chr == (char)i)
            {
                fwrite(&(forest[j] -> freq), sizeof(long), 1, fh);
            }
        }
        if(j != size - 1)
            fwrite(&(zero), sizeof(long), 1, fh);
    }

}