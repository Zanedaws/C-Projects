#include <stdio.h>
#include <stdint.h>
#define STARTSIZE 4
#define GROWFACTOR 1.5
#define COUNT 10

typedef struct CodeHolder{
    char chr;
    long code;
    int depth;
}Code;

typedef struct HTree{ //huffman tree
    char chr; //character for the node on the tree
    long freq; //frequency or weight of character
    struct HTree * left; //left pointer
    struct HTree * right; //right pointer
} Tree;

Tree** readFromFile(char* filename, Tree** forest, int* size);
Tree** addTree(Tree** forest, char tmp, int* count, int* size);
Tree** destroyForest(Tree** forest, int count);
void destroyTree(Tree* root);
int freqOutput(char* filename, Tree** forest, int size);
void sortForest(Tree** forest, int size);
Tree** buildTree(Tree** forest, int* size);
Tree** insert(Tree* root, Tree** forest, int* size);
Tree** shift(Tree** forest, int* size, int ammount);
void printCode(char* filename, Tree* root, Code** codeList);
void getSequence(Tree* root, long seq, int depth, FILE* fh, Code** codeList, int* index);
void printSequence(long seq, int depth, FILE* fh, Code** codeList, int* index, char chr);
void printHeader(Tree* root, FILE* fh);

void printHeaderInfo(FILE* writeFile, Tree* root, int* bits, int* totalBits, int* totalBytesAdded);
void readToCompress(FILE* readFile, FILE* writeFile, Code** codeList, Tree* root, long size);
void printCompCode(Code** codeList, char key, FILE* writeFile, int* totalBits, int* bits, long size, long* totalNumChar);
void printNumChar(FILE* readFile, FILE* writeFile);
void printHuffNum(FILE* writeFIle, long size);
int reverseByte(int bin);

void destroyCodeList(Code** codeList, int size);

//testing code
void printTree(Tree* root);
void print2DUtil(Tree* root, int space);
void printBinary(int bin, int length);