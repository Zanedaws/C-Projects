#define STARTSIZE 4
#define GROWFACTOR 1.5

typedef struct HTree{ //huffman tree
    char chr; //character for the node on the tree
    long freq; //frequency or weight of character
    struct HTree * left; //left pointer
    struct HTree * right; //right pointer
} Tree;

Tree** readFromFile(char* filename, Tree** forest, int* size);
Tree** addTree(Tree** forest, char tmp, int* count, int* size);
Tree** destroyForest(Tree** forest, int count);
// Tree** moreMem(Tree** forest, int* size /*number of mem spaces in array*/, int* count /*number of spaces used*/);
int freqOutput(char* filename, Tree** forest, int size);
void sortForest(Tree** forest, int size);
Tree* buildTree(Tree** forest, int size);
void preTravHead(char* filename, Tree * root);
void preTravCode(char* filename, Tree* root);
// void codeMessage(char* inputFile, char* filename, list* header);

