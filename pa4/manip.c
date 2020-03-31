#include "manip.h"
#include "hbt.h"
#include "pa4.h"
#include "build.h"

//inserts a key into the BST and balances it
Tnode* insertKey(Tnode* root, Tnode* previous, int toInsert)
{   
    if(root == NULL)
    {
        Tnode* newRoot = malloc(sizeof(*newRoot));
        newRoot -> balance = 0;
        newRoot -> key = toInsert;
        newRoot -> left = NULL;
        newRoot -> right = NULL;
        return newRoot;
    }
        
    if(toInsert > root -> key)
    {
        fprintf(stderr, "\n");
        root -> right = insertKey(root -> right, root, toInsert);
        getBalanceNS(root);
        if(root -> balance < -1 || root -> balance > 1)
        {
            root = balance(root, previous);
        }
        return root;
    }
    if(toInsert <= root -> key)
    {
        fprintf(stderr, "\n");
        root -> left = insertKey(root -> left, root, toInsert);
        getBalanceNS(root);
        if(root -> balance < -1 || root -> balance > 1)
        {

            root = balance(root, previous);

        }
        return root;
    }

    // fprintf(stderr, "something odd happened\n");

    return NULL;
}

//deletes key from the BST and balances it
Tnode* deleteKey(Tnode* root, Tnode* previous, int keyDelete)
{
    if(root == NULL)
        return NULL;
    
    if(keyDelete < root -> key)
    {
        root -> left = deleteKey(root -> left, root, keyDelete);
        getBalanceNS(root);
        root = balance(root, previous);
    }
    else if(keyDelete > root -> key)
    {
        root -> right = deleteKey(root -> right, root, keyDelete);
        getBalanceNS(root);
        root = balance(root, previous);
    }
    else
    {
        if(root -> left == NULL)
        {
            Tnode* temp = root -> right;
            free(root);
            return temp;
        }
        else if(root -> right == NULL)
        {
            Tnode* temp = root -> left;
            free(root);
            return temp;
        }
    

        Tnode* temp = getPred(root -> left);
        
        root -> key = temp -> key;

        root -> left = deleteKey(root -> left, previous, temp -> key);
        getBalanceNS(root);
        root = balance(root, previous);
    }
    getBalanceNS(root);
    root = balance(root, previous);
    return root;
}

//gets inorder predecessor
Tnode* getPred(Tnode* root)
{
    while(root -> right != NULL)
    {
        root = root -> right;
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
    {
        newRoot = (root -> left) -> right;
        Tnode* temp = root -> left;
        root -> left = newRoot;
        temp -> right = newRoot -> left;
        newRoot -> left = temp;
        getBalanceNS(newRoot);
        getBalanceNS(temp);
    }
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

    getBalanceNS(root);
    getBalanceNS(newRoot);

    return newRoot;
}

//performs a counter clockwise rotation at given root node
Tnode* cntClkRot(Tnode* root, Tnode* previous)
{
    Tnode* newRoot;
    if((root -> right) -> balance > 0)
    {
        newRoot = (root -> right) -> left;
        Tnode* temp = root -> right;
        root -> right = newRoot;
        temp -> left = newRoot -> right;
        newRoot -> right = temp;
        getBalanceNS(newRoot);
        getBalanceNS(temp);
    }

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


    char code = 0;

    fwrite(&(root -> key), sizeof(int), 1, writeFile);
    if(root -> left != NULL || root -> right != NULL)
    {
        code = root -> left != NULL ? code | 2 : code | 0;
        code = root -> right != NULL ? code | 1 : code | 0;
    }
    fwrite(&(code), sizeof(char), 1, writeFile);

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

