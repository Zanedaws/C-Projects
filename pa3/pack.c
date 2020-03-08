#include "pack.h"

node** readNodes(char* filename, int* size)
{
    FILE* fh = fopen(filename, "r");
    node** nodes = malloc(sizeof(*nodes) * 40);
    int maxSize = 40;
    char valueString[50];
    strcpy(valueString, "");

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
                strncat(valueString, &current, 1);
                while(current != '(')
                {
                    current = fgetc(fh);
                    if(current != '(')
                        strncat(valueString, &current, 1);
                }
                newNode->label = atoi(valueString);
                strcpy(valueString, "");
                current = fgetc(fh);
                strncat(valueString, &current, 1);
                while(current != ',')
                {
                    current = fgetc(fh);
                    if(current != ',')
                        strncat(valueString, &current, 1);
                }
                newNode->width = atoi(valueString);
                strcpy(valueString, "");
                current = fgetc(fh);
                strncat(valueString, &current, 1);
                while(current != ')')
                {
                    current = fgetc(fh);
                    if(current != ')')
                        strncat(valueString, &current, 1);
                }
                newNode->height = atoi(valueString);
                strcpy(valueString, "");
                while(current != '\n')
                    current = fgetc(fh);

                newNode->type = 'L';
                newNode->left = NULL;
                newNode->right = NULL;
                nodes = addNode(nodes, newNode, size, &maxSize);
            }
        }

        current = fgetc(fh);
    }
    fclose(fh);
    return nodes;
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

node* constTree(node** nodes, int* udx)
{
    node* newRoot = nodes[(*udx)];
    if(newRoot->type != 'L')
    {
        if(nodes[(*udx) - 1]->type != 'L')
        {
            (*udx) -= 1;
            newRoot -> right = constTree(nodes, udx);
        }
        else
        {
            (*udx) -= 1;
            newRoot->right = nodes[(*udx)];
        }
        if(nodes[(*udx) - 1]->type != 'L')
        {
            (*udx) -= 1;
            newRoot->left = constTree(nodes, udx);
        }
        else
        {
            (*udx) -= 1;
            newRoot->left = nodes[(*udx)];
        }
    }
    if(newRoot->type == 'H')
    {
        newRoot->height = newRoot->left->height + newRoot->right->height;
        newRoot->width = newRoot->left->width > newRoot->right->width ? newRoot->left->width : newRoot->right->width;
    }
    else if(newRoot->type == 'V')
    {
        newRoot->width = newRoot->left->width + newRoot->right->width;
        newRoot->height = newRoot->left->height > newRoot->right->height ? newRoot->left->height : newRoot->right->height;
    }
    return newRoot;
}


void printPre(node* root, FILE* writeFile)
{
    if(root == NULL)
        return;
    if(root->type == 'L')
    {
        fprintf(writeFile, "%d(%d,%d)\n", root->label, root->width, root->height);
    }
    else
    {
        fprintf(writeFile, "%c\n", root->type);
    }
    printPre(root -> left, writeFile);
    printPre(root -> right, writeFile);
}

void printDim(node* root, FILE* writeFile)
{
    if(root == NULL)
        return;
    printDim(root -> left, writeFile);
    printDim(root -> right, writeFile);
    if(root -> type == 'L')
    {
        fprintf(writeFile, "%d(%d,%d)\n", root->label, root->width, root->height);
    }
    else
    {
        fprintf(writeFile, "%c(%d,%d)\n", root->type, root->width, root->height);
    }
}

void printPack(node* root, FILE* writeFile, int xpos, int ypos)
{
    if(root == NULL)
        return;
    if(root->type == 'L')
    {
        fprintf(writeFile, "%d((%d,%d)(%d,%d))\n", root->label, root->width, root->height, xpos, ypos);
    }
    if(root->type == 'H' && root -> left != NULL && root -> right != NULL)
    {
        printPack(root->left, writeFile, xpos, ypos + (root->height - root->left->height));
        printPack(root->right, writeFile, xpos, ypos);
    }
    else if(root->type == 'V' && root -> left != NULL && root -> right != NULL)
    {
        printPack(root->left, writeFile, xpos, ypos);
        printPack(root->right, writeFile, xpos + (root->width - root->right->width), ypos);
    }
    else
    {
        printPack(root->left, writeFile, xpos, ypos);
        printPack(root->right, writeFile, xpos, ypos);
    }
}

node* destroyTree(node* root)
{
    if(root == NULL)
        return NULL;
    root -> left = destroyTree(root->left);
    root -> right = destroyTree(root->right);
    free(root);
    return NULL;
}