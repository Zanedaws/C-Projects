#include "shell_list.h"
#include <stdlib.h>
#include <stdio.h>
Node* addNode(Node* head, long val);
Node* destroyList(Node* head);
Node* swapNodes(Node* list, int pos1, int pos2);
Node* getNodeAtIndex(Node* head, long index);
void printList(Node* head);

Node *addNode(Node* head, long val)
{
    //make new node
    Node* newNode = NULL;
    newNode = malloc(sizeof(*newNode));
    newNode -> value = val;
    newNode -> next = NULL;
    // printf("newNode -> value = %ld\n", newNode -> value);

    //checks if head is null
    if(head == NULL)
    {
        //if it is then the end of the list is the head
        head = newNode;
        return head;
    }
    else
    {
        //if it isn't p will then find the end of the list and add there
        Node* p = head;
        while(p -> next != NULL)
            p = p -> next;
        p -> next = newNode;
        return head;
    }

}

Node* destroyList(Node* head)
{
    Node* p = NULL;
    p = head;
    
    Node * next = NULL;

    while(p != NULL)
    {
        next = p -> next;
        free(p);
        p = next;
    }

    head = NULL;
    return head;
}


Node *List_Load_From_File(char *filename)
{
    //opening file
    FILE *fh = fopen(filename, "rb");
    if(fh == NULL)
    {
        fprintf(stderr, "%s", "file didn't load properly\n");
        return NULL;
    }

    Node *head = NULL; //initializing the head of the list

    long tmp; //tmp for reading into
    int read = 0;

    while(!feof(fh))
    {
        read += fread(&tmp, sizeof(long), 1, fh); //read a value into tmp
        if(!feof(fh)) //check if EOF has been reached
            head = addNode(head, tmp); //add value to list
    }

    if(read == 0)
    {
        fprintf(stderr,"%s","read failed");
        exit(EXIT_FAILURE);
        destroyList(head);
        return NULL;
    }

    fclose(fh); //close the file

    return head; //return the new head of the list
}

int List_Save_To_File(char* filename, Node* list)
{
    FILE *fh = NULL;
    fh = fopen(filename, "w");


    if(fh == NULL)
    {
        fprintf(stderr,"%s", "fopen in save failed");
        exit(EXIT_FAILURE);
        return 0;
    }
    

    Node *p = list;
    int written = 0;

    while(p != NULL)
    {
        written += fwrite(&(p -> value), sizeof(long), 1, fh);
        p = p -> next;
    }

    fclose(fh);

    destroyList(list);

    return written;
}

Node *List_Shellsort(Node *list, long *n_comp)
{

    //counting the size of the list
    Node* p = list;
    long size = 0;

    while(p != NULL)
    {
        p = p -> next;
        size++;
    }


    long h = 0; //sequence value

    //getting max sequence value
    do
    {

        h = 3 * h + 1;

    } while (h < size);
    h = (h - 1) / 3;

    fprintf(stderr, "sorting internal...\n");
    //shell sort --------------------------------------------------
    
    //variable declarations ---------------------------------------
    long j;
    long i;
    Node* arrIminH = NULL;
    Node* tmp = NULL;
    //variable declarations ---------------------------------------

    while(h > 0)
    {
        for(j = h; j < size; j++)
        {
            tmp = getNodeAtIndex(list, j);
            i = j;
            arrIminH = getNodeAtIndex(list, (i - h));
            while(i >= h && arrIminH -> value > tmp -> value)
            {
                (*n_comp)++; 

                list = swapNodes(list, i - h, i);

                i = i - h;
                
                arrIminH = getNodeAtIndex(list, (i - h));
            }
            (*n_comp)++;
        }

        h = (h - 1) / 3;
    }
    //shell sort --------------------------------------------------

    fprintf(stderr, "sorted\n");

    return list;
}


Node* getNodeAtIndex(Node* head, long index)
{
    Node* node = head;
    int i;

    for(i = 0; i < index; i++)
    {   
        if(node == NULL)
            fprintf(stderr, "node is null\nindex is = %ld\n", index);
        node = node -> next;
    }
    return node;
}


Node* swapNodes(Node* list, int pos1, int pos2)
{

    if(pos1 == pos2)
        return list;
    

    if ((pos1 < 0) || (pos2 < 0))
    {
        fprintf(stderr, "\tinvalid position args in swapNodes\n");
        return list;
    }

    Node* node1 = NULL;
    Node* node2 = NULL;
    Node* prev1 = NULL;
    Node* prev2 = NULL;

    Node* tmp = list;

    int i = 0;

    while(tmp != NULL)
    {   
        if(i == pos1 - 1)
            prev1 = tmp;
        if(i == pos2 - 1)
            prev2 = tmp;
        if(i == pos1)
            node1 = tmp;
        if(i == pos2)
            node2 = tmp;
        tmp = tmp -> next;
        i++;
    }

    if(node1 != NULL && node2 != NULL)
    {   
        if(prev1 != NULL)
            prev1 -> next = node2;
        
        if(prev2 != NULL)
            prev2 -> next = node1;

        tmp = node1 -> next;
        node1 -> next = node2 -> next;
        node2 -> next = tmp;

        if(prev1 == NULL)
        {
            list = node2;
        }
        else if(prev2 == NULL)
        {
            list = node1;
        }
    }

    return list;

}

void printList(Node* head)
{
    Node* p = head;
    while(p != NULL)
    {
        fprintf(stderr, "%ld\n", p -> value);
        p = p -> next;
    }

    if(p == NULL)
        fprintf(stderr, "null reached\n");

    return;
}