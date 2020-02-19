#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hcomp.h"

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        fprintf(stderr,"not correct number of args\n");
        return EXIT_FAILURE;
    }

    Tree** forest = malloc(sizeof(*forest) * STARTSIZE);
    int count = 0;

    forest = readFromFile(argv[1], forest, &count);

    int writCheck;

    writCheck = freqOutput(argv[2], forest, count);
    if(writCheck != EXIT_SUCCESS)
    {
        fprintf(stderr, "err in freqOutput.\n");
        return EXIT_FAILURE;
    }

    Tree** rootForest = buildTree(forest, count);
    
    fprintf(stderr, "count = %d\n", count);

    // destroyTree(rootForest[0]);

    // forest = destroyForest(forest, count);

    return EXIT_SUCCESS;
}