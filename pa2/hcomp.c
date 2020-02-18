#include "hcomp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ZERO 0

Tree** readFromFile(char* filename, Tree** forest, int* count)
{
    FILE * fh = fopen(filename, "rb");

    if(fh == NULL)
    {
        fprintf(stderr, "file failed to open\n");
        return 0;
    }

    char tmp;
    int size = STARTSIZE;

    while(!feof(fh))
    {
        tmp = fgetc(fh);
        if(!feof(fh))
        {
            forest = addTree(forest, tmp, count, &size);
            
        }
    }

    fclose(fh);

    sortForest(forest, *count);

    return forest;
}



Tree** addTree(Tree** forest, char tmp, int* count, int* size)
{
    Tree* newTree = malloc(sizeof(*newTree));
    newTree ->  chr = tmp;
    newTree -> freq = 1;
    newTree -> left = NULL;
    newTree -> right = NULL;

    int i;
    //check if character is already in forest
    for(i = 0; i < *count; i++)
    {
        if(forest[i] -> chr == tmp)
        {
            forest[i] -> freq += 1;
            free(newTree);
            return forest;
        }
    }


    //if it isn't then check if the array is big enough, if not increase the size
    if(*count != 0 && *count < *size)
    {
        forest[*count] = newTree;
        forest[*count] = newTree;
        *count += 1;
        return forest;
    }
    else if(*count == 0)
    {
        forest[*count] = newTree;
        forest[*count] = newTree;
        *count += 1;
        return forest;
    }
    else
    {
        Tree** newForest = realloc(forest, sizeof(*forest) * (*size + *size/4));
        *size = *size + *size/4;
        newForest[*count] = newTree;
        newForest[*count] = newTree;
        *count += 1;
        return newForest;
    }

    return forest;
}

Tree** destroyForest(Tree** forest, int count)
{
    int i;
    for(i = 0; i < count; i++)
    {
        free(forest[i]);
    }
    free(forest);
    forest = NULL;
    return forest;
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
    char tmp2 = '\0';

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
            tmp2 = forest[j] -> chr;
            i = j;
            while (i >= h && forest[i-h] -> freq > tmp)
            {
                forest[i] -> freq = forest[i-h] -> freq;
                forest[i] -> chr = forest[i-h] -> chr;
                i = i - h;
                forest[i] -> freq = tmp;
                forest[i] -> chr = tmp2;
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

    // //checking frequencies------------------------------------------------------------
    // int k;
    // for(k = 0; k < size; k++)
    // {
    //     fprintf(stderr, "%c -> freq: %ld\n", forest[k] -> chr, forest[k] -> freq);
    // }
    // //--------------------------------------------------------------------------------


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
    char current;
    long zero = ZERO;
    for(i = 0; i < 256; i++)
    {
        current = i;
        for(j = 0; j < size; j++)
        {
            if(forest[j] -> chr == current)
            {
                written = fwrite(&(forest[j] -> freq), sizeof(long), 1, fh);
                if(written != 1)
                {
                    fprintf(stderr, "error occurred when writing a frequency\n");
                    fclose(fh);
                    return EXIT_FAILURE;
                }
            }
        }
        if(written == 0)
        {
            written = fwrite(&(zero), sizeof(long), 1, fh);
            if(written != 1)
            {
                fprintf(stderr, "error occurred when writing a zero\n");
                fclose(fh);
                return EXIT_FAILURE;
            }
        }
        written = 0;
    }

    fclose(fh);
    return EXIT_SUCCESS;
}