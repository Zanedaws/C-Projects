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
    int sizeE;

    sizeE = readFromFile(argv[1], forest);

    int writCheck;

    writCheck = freqOutput(argv[2], forest, sizeE);
    if(writCheck != EXIT_SUCCESS)
    {
        fprintf(stderr, "err in freqOutput.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}