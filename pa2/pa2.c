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

    // fprintf(stderr, "count = %d\n", count);

    int preBuildCount = count;

    int writCheck;

    writCheck = freqOutput(argv[2], forest, count);
    if(writCheck != EXIT_SUCCESS)
    {
        fprintf(stderr, "err in freqOutput.\n");
        return EXIT_FAILURE;
    }

    Tree** rootForest = buildTree(forest, &count);

    // print2DUtil(rootForest[0], 0);

    Code** codeList = malloc(sizeof(*codeList) * preBuildCount);

    printCode(argv[3], rootForest[0], codeList);

    

    FILE* fh = fopen(argv[4], "w");

    printHeader(rootForest[0], fh);

    fclose(fh);

    FILE* writeFile = fopen(argv[5], "w");
    FILE* readFile = fopen(argv[1], "r");

    readToCompress(readFile, writeFile, codeList);

    fclose(writeFile);
    fclose(readFile);

    print2DUtil(rootForest[0], 0);

    destroyCodeList(codeList, preBuildCount);

    destroyTree(rootForest[0]);

    free(rootForest);

    return EXIT_SUCCESS;
}