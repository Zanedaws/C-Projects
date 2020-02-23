#include "hcomp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
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
    for(i = count - 1; i >= 0; i--)
    {
        destroyTree(forest[i]);
    }
    free(forest);
    return NULL;
}

void destroyTree(Tree* root)
{
    if(root != NULL)
    {
        destroyTree(root -> left);
        destroyTree(root -> right);
        free(root);
    }
    root = NULL;
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
    
    // h = 1;

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


//TREE BUILDING STARTS HERE---------------------------------------------------------------------------------------------------------------------

Tree** buildTree(Tree** forest, int* size)
{
    while(*size > 1)
    {
        //initialize new root for tree
        Tree* newRoot = malloc(sizeof(*newRoot));
        newRoot -> freq = forest[0] -> freq + forest[1] -> freq;
        newRoot -> chr = '\0';
        newRoot -> left = malloc(sizeof(*(newRoot -> left)));
        newRoot -> right = malloc(sizeof(*(newRoot -> right)));
        newRoot -> left -> left = NULL;
        newRoot -> right -> right = NULL;


        //copy all data into a new left and right node
        newRoot -> left -> freq = forest[0] -> freq;
        newRoot -> right -> freq = forest[1] -> freq;
        newRoot -> left -> chr = forest[0] -> chr;
        newRoot -> right -> chr = forest[1] -> chr;
        newRoot -> left -> left = forest[0] -> left;
        newRoot -> right -> right = forest[1] -> right;
        newRoot -> left -> right = forest[0] -> right;
        newRoot -> right -> left = forest[1] -> left;

        forest = shift(forest, size, 2);
        // fprintf(stderr, "size = %d\n", *size);
        forest = insert(newRoot, forest, size);
        free(newRoot);
    }   
    return forest;
}

Tree** insert(Tree* root, Tree** forest, int* size)
{
    //TESTING CODE-------------------------------------------------------------------------
    // int k;
    // for(k = 0; k < *size; k++)
    // {
    //     fprintf(stderr, "chr = (%c)\tfreq = %ld\n", forest[k] -> chr, forest[k] -> freq);
    // }
    // fprintf(stderr, "\n");
    //TESTING CODE-------------------------------------------------------------------------

    int i = 0;
    while(root -> freq >= forest[i] -> freq && i < *size - 1)
    {
        i++;
    }
    int j = *size - 2;
    while(j >= i)
    {
        forest[j + 1] -> freq = forest[j] -> freq;
        forest[j + 1] -> chr = forest[j] -> chr;
        forest[j + 1] -> left = forest[j] -> left;
        forest[j + 1] -> right = forest[j] -> right;
        j--;
    }
    forest[i] -> freq = root -> freq;
    forest[i] -> chr = root -> chr;
    forest[i] -> left = root -> left;
    forest[i] -> right = root -> right;

    //TESTING CODE-------------------------------------------------------------------------
    // for(k = 0; k < *size; k++)
    // {
    //     fprintf(stderr, "chr = (%c)\tfreq = %ld\n", forest[k] -> chr, forest[k] -> freq);
    // }
    // fprintf(stderr, "\n");
    //TESTING CODE-------------------------------------------------------------------------

    return forest;
}

Tree** shift(Tree** forest, int* size, int ammount)
{
    int i;
    for(i = ammount; i < *size; i++)
    {   
        forest[i - ammount] -> freq = forest[i] -> freq;
        forest[i - ammount] -> chr = forest[i] -> chr;
        forest[i - ammount] -> left = forest[i] -> left;
        forest[i - ammount] -> right = forest[i] -> right;
    }

    free(forest[i - 1]);

    *size = *size - 1;

    return forest;
}


//CODE OUTPUT START------------------------------------------------------------------------

void printCode(char* filename, Tree* root, Code** codeList)
{
    FILE* fh = fopen(filename, "w");
    long sequence = 0x00;
    int depth = 0;
    int index = 0;
    getSequence(root, sequence, depth, fh, codeList, &index);
    fclose(fh);
}

void getSequence(Tree* root, long seq, int depth, FILE* fh, Code** codeList, int* index)
{
    if(root -> left == NULL && root -> right == NULL)
    {
        fprintf(fh, "%c:", root -> chr);
        printSequence(seq, depth - 1, fh, codeList, index, root -> chr);
        fprintf(fh, "\n");
        return;
    }

    seq = seq << 1;
    depth += 1;
    getSequence(root -> left, seq, depth, fh, codeList, index);
    seq = seq >> 1;
    depth--;
    depth++;
    seq = (seq << 1) + 1;
    getSequence(root -> right, seq, depth, fh, codeList, index);
    seq = seq >> 1;
    depth--;
}

void printSequence(long seq, int depth, FILE* fh, Code** codeList, int* index, char chr)
{
    int i;
    long tmp;
    fprintf(stderr, "index = %d\n", *index);
    codeList[*index] = malloc(sizeof(*codeList[*index]));
    codeList[*index] -> chr = chr;
    codeList[*index] -> code = seq;
    codeList[*index] -> depth = depth;
    (*index)++;
    fprintf(stderr, "index = %d\n", *index);
    for(i = depth; i >= 0; i--)
    {
        tmp = seq;
        seq = seq >> i;
        fprintf(fh, "%ld", seq & 0x01);
        seq = tmp;
    }
    
}


void destroyCodeList(Code** codeList, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        free(codeList[i]);
    }
    free(codeList);
    codeList = NULL;
}

//COMPRESSION CODE---------------------------------------------------------------------------

void printCompCode(Code** codeList, char key, FILE* fh, int* totalBits, int* bits)
{
    
    
}


void readToCompress(FILE* readFile, FILE* writeFile, Code** codeList)
{
    int totalBits = 0;
    char tmp;
    int bits = 0;
    while(!feof(readFile))
    {
        tmp = fgetc(readFile);
        if(!feof(readFile))
        {
            printCompCode(codeList, tmp, writeFile, &totalBits, &bits);
        }
    }
}

//HEADER CODE--------------------------------------------------------------------------------


void printHeader(Tree* root, FILE* fh)
{
    if(root -> chr == '\0')
    {
        fprintf(fh, "0");
        printHeader(root -> left, fh);
        printHeader(root -> right, fh);
    }
    else
    {
        fprintf(fh,"1%c", root -> chr);
    }
}


//TESTING CODE-----------------------------------------------------------------------------
void printTree(Tree* root)
{
    if(root == NULL)
    {
        fprintf(stderr, "root NULL\n");
        return;
    }
    if(root -> left == NULL && root -> right == NULL)
    {
        fprintf(stderr, "chr = %c, freq = %ld\n", root -> chr, root -> freq);
        return;
    }
    fprintf(stderr, "moved left\n");
    printTree(root -> left);
    fprintf(stderr, "moved right\n");
    printTree(root -> right);
}

void print2DUtil(Tree *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    fprintf(stderr, "\n"); 
    for (int i = COUNT; i < space; i++) 
        fprintf(stderr, " "); 
    fprintf(stderr, "%ld, %c\n", root->freq, root -> chr); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 