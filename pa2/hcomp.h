#define STARTSIZE 4
#define GROWFACTOR 1.5
#define COUNT 10

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
Tree** buildTree(Tree** forest, int size);
Tree** insert(Tree* root, Tree** forest, int* size);
Tree** shift(Tree** forest, int* size, int ammount);
void preTravHead(char* filename, Tree * root);
void preTravCode(char* filename, Tree* root);

//testing code
void printTree(Tree* root);
void print2DUtil(Tree* root, int space);