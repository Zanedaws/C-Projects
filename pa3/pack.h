#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode{
    char type;
    int width;
    int height;
    int label;
    struct TNode* left;
    struct TNode* right;
}node;


node** readNodes(char* filename, int* size);
node** addNode(node** nodes, node* newNode, int* size, int* maxSize);