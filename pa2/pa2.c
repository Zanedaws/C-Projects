#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hcomp.h"

int main(int argc, char* argv)
{
    if(argc != 6)
    {
        fprintf(stderr, "argc too small\n");
        return EXIT_FAILURE;
    }

    list* header = NULL;

    header = readFromFile(argv[1], header);

    if(header == NULL)
    {
        fprintf(stderr, "failed to read from file\n");
        return EXIT_FAILURE;
    }

    freqOutput(argv[2], header);

    Tree* root = NULL;

    root = buildTree(root, header);

    if(root == NULL)
    {
        fprintf(stderr, "failed to build tree\n");
        return EXIT_FAILURE;
    }

    preTravHead(argv[3], root);

    header = preTravCode(argv[4], root);

    if(header -> code == NULL)
    {
        fprintf(stderr, "failed to get code for characters");
        return EXIT_FAILURE;
    }

    codeMessage(argv[4], argv[1], header);

    header = destroyList(header);

    if(header != NULL)
    {
        fprintf(stderr, "failed to free list");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}