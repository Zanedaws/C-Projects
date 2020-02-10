#include "shell_list.h"
#include <stdlib.h>
#include <stdio.h>
Node* addNode(Node* head, long val);
Node* destroyList(Node* head);
Node* getIminH(Node* head, int i, int h);


Node *addNode(Node* head, long val)
{
    //make new node
    Node* newNode = NULL;
    newNode = malloc(sizeof(Node));
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

Node* getIminH(Node* head, int i, int h)
{
    Node* p = NULL;
    p = head;
    int count = 0;

    while(count != (i - h - 1))
    {
        p = p -> next;
        count++;
    }

    return p;
}


Node *List_Load_From_File(char *filename)
{
    //opening file
    FILE *fh = fopen(filename, "r");
    if(fh == NULL)
    {
        fprintf(stderr, "file didn't load properly");
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
        fprintf(stderr, "read failed");
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
        exit(EXIT_FAILURE);
        return 0;
    }
    

    Node *p = list;
    int written;

    while(p != NULL)
    {
        fwrite(&(p -> value), sizeof(long), 1, fh);
        p = p -> next;
        written++;
    }

    return written;
}

Node *List_Shellsort(Node *list, long *n_comp)
{

    //counting the size of the list
    Node* p = list;
    int size = 0;

    while(p -> next != NULL)
    {
        p = p -> next;
        size++;
    }

    int h = 0; //sequence value

    //getting max sequence value
    do
    {

        h = 3 * h + 1;

    } while (h < size);
    h = (h - 1) / 3;

    //increment variables
    int j;
    int i;
    int k = 0;

    //
    Node* nodeCmp = NULL;
    Node* tmp = list;

    //shell sort --------------------------------------------------
    while (h > 0)
    {
        for (j = h; j < size; j++)
        {
            while(k < j)
            {
                tmp = tmp -> next;
                k++;
            }
            k = 0;
            //tmp -> next is array[j]
            i = j;
            nodeCmp = list;
            while(k < (i - h))
            {
                nodeCmp = nodeCmp -> next;
                k++;
            }
            k = 0;

            
            while (i >= h && nodeCmp -> next -> value > tmp -> next -> value)
            {
                
                (*n_comp)++;
                p = list;
                while(k < i)
                {
                    p = p -> next;
                    k++;
                }
                k = 0;
                //p -> next is array[i]
                i = i - h;

                nodeCmp = list;
                while(k < i)
                {
                    nodeCmp = nodeCmp -> next;
                    k++;
                }
                k = 0;
                //nodeCmp -> next is array[i - h]

                p -> next = nodeCmp -> next;
                nodeCmp -> next = tmp;
                
            }
            (*n_comp)++; //increment number of comparisons
        }
        //decrement sequence
        h = (h - 1) / 3;
    }
    //shell sort --------------------------------------------------

    printf("reached\n");

    return list;

}