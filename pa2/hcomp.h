typedef struct HTree{ //huffman tree
    char chr; //character for the node on the tree
    long freq; //frequency or weight of character
    struct HTree * left; //left pointer
    struct HTree * right; //right pointer
} Tree;

int readFromFile(char* filename, list* head);
int addTree(Tree** forest, char tmp, int* count);
int freqOutput(char* filename, Tree** forest, int size);
void sortForest(Tree** forest, int size);
Tree* buildTree(Tree** forest);
void preTravHead(char* filename, Tree * root);
void preTravCode(char* filename, Tree* root);
void codeMessage(char* inputFile, char* filename, list* header);

