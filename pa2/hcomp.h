typedef struct HTree{ //huffman tree
    char chr; //character for the node on the tree
    struct HTree * left; //left pointer
    struct HTree * right; //right pointer
} Tree;

typedef struct list{ //linked list to store frequency
    char chr;
    char* code;
    long freq;
    struct list * next;
} list;


//list functions ------------------------------------------------
list* readFromFile(char* filename, list* header);
list* addListNode(list* head, char chr, long freq);
list* destroyList(list* head);
void freqOutput(char* filename, list* head);
//---------------------------------------------------------------

//HTree functions -----------------------------------------------
Tree* buildTree(Tree * root, list * head);
void preTravHead(char* filename, Tree * root);
list* preTravCode(char* filename, Tree* root);
void codeMessage(char* inputFile, char* filename, list* header);
//---------------------------------------------------------------
