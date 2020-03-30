#include "manip.h"
#include "hbt.h"
#include "pa4.h"

//inserts a key into the BST and balances it
Tnode* insertKey(Tnode* root, int toInsert)
{   
    Tnode* current = root;
    Tnode* previous = NULL;
    Tnode* toBalance = root;
    Tnode* preToBalance = NULL;
    while(current != NULL)
    {
        if(current -> balance != 0)
        {
            preToBalance = previous;
            toBalance = current;
        }

        previous = current;
        current = toInsert <= current -> key ? current -> left : current -> right;

        if(current == NULL || current -> balance == 0)
        {
            previous -> balance = previous -> right == current ? (previous -> balance) - 1 : (previous -> balance) + 1;
        }
    }


    if(current == root)
    {
        current = malloc(sizeof(*current));
        current -> key = toInsert;
        current -> left = NULL;
        current -> right = NULL;
        current -> balance = 0;
        return current;
    }

    current = malloc(sizeof(*current));
    if(toInsert < previous -> key)
        previous -> left = current;
    else 
        previous -> right = current;
    current -> key = toInsert;
    current -> left = NULL;
    current -> right = NULL;
    current -> balance = 0;

    if(toBalance == root)
        root = balance(root, preToBalance);
    else
        toBalance = balance(toBalance, preToBalance);

    return root;
}

//deletes key from the BST and balances it
Tnode* deleteKey(Tnode* root, Tnode* previous, int keyDelete)
{
    if(root == NULL)
        return NULL;

    fprintf(stderr, "delete key: %d\n", keyDelete);
    printTree(root);
    fprintf(stderr, "\n");
    if(root -> key < keyDelete)
    {
        root -> right = deleteKey(root -> right, root, keyDelete);
        getBalanceNS(root);
        if(root -> balance < -1 || root -> balance > 1)
        {
            root = balance(root, previous);
        }
        return root;
    }
    else if(root -> key > keyDelete)
    {
        root -> right = deleteKey(root -> left, root, keyDelete);
        getBalanceNS(root);
        if(root -> balance < -1 || root -> balance > 1)
        {
            root = balance(root, previous);
        }
        return root;
    }
    
    if(root -> left != NULL && root -> right != NULL)
    {
        Tnode* newRoot = root -> left;
        Tnode* prePred = root;
        while(newRoot -> right != NULL)
        {
            prePred = newRoot;
            newRoot = newRoot -> right;
        }
        Tnode* temp;
        temp = root -> left;
        root -> left = newRoot -> left;
        newRoot -> left = temp;
        newRoot -> right = root -> right;
        prePred -> right = root -> left;
        free(root);
        prePred -> balance = prePred -> balance + 1;
        return newRoot;
    }
    else if(root -> left != NULL && root -> right == NULL)
    {
        Tnode* temp = root -> left;
        free(root);
        return temp;
    }
    else if(root -> left == NULL && root -> right != NULL)
    {
        Tnode* temp = root -> right;
        free(root);
        return temp;
    }
    else
    {
        free(root);
        return NULL;
    }

    return root;
}

//balances tree at given root node
Tnode* balance(Tnode* root, Tnode* previous)
{
    printTree(root);
    fprintf(stderr, "\n");
    if(root -> balance > 1)
    {
        root = clkRot(root, previous);
    }
    else if(root -> balance < -1)
    {
        root = cntClkRot(root, previous);
    }
    printTree(root);
    fprintf(stderr, "\n");
    return root;
}

//performs a clockwise rotation at given root node
Tnode* clkRot(Tnode* root, Tnode* previous)
{
    Tnode* newRoot;
    if((root -> left) -> balance < 0)
        root = cntClkRot(root -> left, root);

    newRoot = root -> left;

    root -> left = newRoot -> right;
    newRoot -> right = root;
    if(previous != NULL)
    {
        if(previous -> right == root)
            previous -> right = newRoot;
        else
            previous -> left = newRoot;
    }

    root -> balance = root -> balance - 2;
    newRoot -> balance = newRoot -> balance - 1;

    return newRoot;
}

//performs a counter clockwise rotation at given root node
Tnode* cntClkRot(Tnode* root, Tnode* previous)
{
    Tnode* newRoot;
    if((root -> right) -> balance > 0)
        root = clkRot(root -> right, root);
    
    newRoot = root -> right;

    root -> right = newRoot -> left;
    newRoot -> left = root;
    if(previous != NULL)
    {
        if(previous -> right == root)
            previous -> right = newRoot;
        else
            previous -> left = newRoot;
    }

    root -> balance = root -> balance + 2;
    newRoot -> balance = newRoot -> balance + 1;
    
    return newRoot;
}


//prints the output of the passed tree
void printTreeOutput (Tnode* root, FILE* writeFile)
{
    if(root == NULL)
        return;


    fprintf(writeFile, "%d %d\n", root -> key, root -> balance);

    //fprintf(stderr, "root key: %d\n", root -> key);
    // char code = 0x00;
    // fwrite(&(root -> key), sizeof(int), 1, writeFile);
    // if(root -> left == NULL && root -> right == NULL)
    // {
    //     fwrite(&code, sizeof(char), 1, writeFile);
    // }
    // else if(root -> left != NULL && root -> right == NULL)
    // {
    //     code = code | 0x01;
    //     fwrite(&code, sizeof(char), 1, writeFile);
    // }
    // else if(root -> left == NULL && root -> right != NULL)
    // {
    //     code = code | 0x02;
    //     fwrite(&code, sizeof(char), 1, writeFile);
    // }
    // else
    // {
    //     code = code | 0x03;
    //     fwrite(&code, sizeof(char), 1, writeFile);
    // }

    printTreeOutput(root -> left, writeFile);
    printTreeOutput(root -> right, writeFile);
    return;
}


void printTree (Tnode* root)
{
    if(root == NULL)
        return;

    fprintf(stderr, "root key: %d\n", root -> key);
    fprintf(stderr, "balance: %d\n", root -> balance);
    printTree(root -> left);
    printTree(root -> right);
    return;
}
