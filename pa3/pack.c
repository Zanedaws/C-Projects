#include "pack.h"

node** readNodes(char* filename, int* size)
{
    FILE* fh = fopen(filename, "r");
    node** nodes = malloc(sizeof(*nodes) * 40);
    int maxSize = 40;
    char* valueString;
    int valStringIdx = "\0";

    if(fh == NULL)
    {
        fprintf(stderr, "failed ot open input file\n");
        return NULL;
    }

    char current = fgetc(fh);

    while(!feof(fh))
    {
        if(current != '\n' && !feof(fh))
        {
            if(current == 'H' || current == 'V')
            {
                node* newNode = malloc(sizeof(*newNode));
                newNode->type = current == 'H' ? 'H' : 'V';
                newNode->label = -1;
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->height = 0;
                newNode->width = 0;
                nodes = addNode(nodes, newNode, size, &maxSize);
            }
            else
            {
                node* newNode = malloc(sizeof(*newNode));
                valueString = strcat(valueString, &current);
                while(current != '(')
                {
                    current = fgetc(fh);
                    if(current != '(')
                        valueString = strcat(valueString, &current);
                }
                newNode->label = atoi(valueString);
                valueString = "\0";
                current = fgetc(fh);
                valueString = strcat(valueString, &current);
                while(current != ',')
                {
                    current = fgetc(fh);
                    if(current != ',')
                        valueString = strcat(valueString, &current);
                }
                newNode->width = atoi(valueString);
                valueString = "\0";
                current = fgetc(fh);
                valueString = strcat(valueString, &current);
                while(current != ')')
                {
                    current = fgetc(fh);
                    if(current != ')')
                        valueString = strcat(valueString, &current);
                }
                newNode->height = atoi(valueString);
                valueString = "\0";
                while(current != '\n')
                    fgetc(fh) = current;

                newNode->type = 'L';
                newNode->left = NULL;
                newNode->right = NULL;
                nodes = addNode(nodes, newNode, size, &maxSize);
            }
        }

        current = fgetc(fh);
    }
}

node** addNode(node** nodes, node* newNode, int* size, int* maxSize)
{
    if(*size + 1 > *maxSize)
    {
        *maxSize = *maxSize + (*maxSize) + (int)(((*maxSize) * 3.0) / 4.0);
        nodes = realloc(nodes, sizeof(*nodes) * (*maxSize));
        nodes[(*size)] = newNode;
        *size = *size + 1;
    }
    else
    {
        nodes[(*size)] = newNode;
        *size = *size + 1;
    }
    return nodes;
}