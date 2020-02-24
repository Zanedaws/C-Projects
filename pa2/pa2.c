#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "hcomp.h"

int main(int argc, char** argv)
{
    if(argc != 6)
    {
        fprintf(stderr,"not correct number of args\n");
        return EXIT_FAILURE;
    }

    Tree** forest = malloc(sizeof(*forest) * STARTSIZE);
    int count = 0;

    forest = readFromFile(argv[1], forest, &count);

    if(count == 0)
    {
        fprintf(stderr, "file is empty\n");
        free(forest);
        return EXIT_FAILURE;
    }

    int preBuildCount = count;

    int writCheck;

    writCheck = freqOutput(argv[2], forest, count);
    if(writCheck != EXIT_SUCCESS)
    {
        fprintf(stderr, "err in freqOutput.\n");
        return EXIT_FAILURE;
    }


    // int i;
    // for(i = 0; i < count; i++)
    // {
    //     fprintf(stderr, "chr = (%c)\tfreq = %ld\n", forest[i] -> chr, forest[i] -> freq);
    // }

    Tree** rootForest = buildTree(forest, &count);

    Code** codeList = malloc(sizeof(*codeList) * preBuildCount);

    printCode(argv[3], rootForest[0], codeList);

    FILE* fh = fopen(argv[4], "w");

    printHeader(rootForest[0], fh);

    fclose(fh);

    FILE* writeFile = fopen(argv[5], "w");
    FILE* readFile = fopen(argv[1], "r");

    readToCompress(readFile, writeFile, codeList, rootForest[0], (long)preBuildCount);

    fclose(writeFile);
    fclose(readFile);

    // print2DUtil(rootForest[0], 0);

    destroyCodeList(codeList, preBuildCount);

    destroyTree(rootForest[0]);

    free(rootForest);

    return EXIT_SUCCESS;
}