#ifndef MANIP_H
#define MANIP_H

#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>

Tnode* insertKey(Tnode* root, Tnode* previous, int toInsert);
Tnode* deleteKey(Tnode* root, Tnode* previous, int keyDelete);
Tnode* balance(Tnode* root, Tnode* previous);
Tnode* clkRot(Tnode* root, Tnode* previous);
Tnode* cntClkRot(Tnode* root, Tnode* previous);
void printTreeOutput (Tnode* root, FILE* writeFile);
void printTree (Tnode* root); 
Tnode* getPred(Tnode* root);

#endif