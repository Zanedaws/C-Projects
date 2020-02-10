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
    while(p -> next -> next != NULL)
    {
        p = p -> next;
    }
    
    free(p -> next);

    if(head -> next != NULL)
        destroyList(head);
    else
    {
        free(head);
        return NULL;
    }
}

Node* getIminH(Node* head, int i, int h)
{
    Node* p = NULL;
    p = head;

    while(count != (i - h))
        p = p -> next;
    
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

    while(!feof(fh))
    {
        fread(&tmp, sizeof(long), 1, fh); //read a value into tmp
        if(!feof(fh)) //check if EOF has been reached
            head = addNode(head, tmp); //add value to list
    }

    fclose(fh); //close the file

    return head; //return the new head of the list
}

int List_save_To_File(char* filename, Node* list)
{
    //open file
    FILE* fh = fopen(filename, "w");
    if(fh == NULL)
    {
        fprintf(stderr,"output file failed to open");
        list = destroyList(list);
        return -1;
    }

    int count = 0; //written counter
    Node* p = NULL; //pointer for printing
    p = list; //initialize pointer at beginning of list

    //loop through list and write each value
    while(p != NULL)
    {
        fwrite(p -> value, sizeof(long), 1, fh);
        count++;
        p = p -> next;
    }

    list = destroyList(list); //destroy the list
    return count; //return the count
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

    int j;
    int i;
    int count;
    Node* nodeCmp = NULL;
    Node* tmp = NULL;

    //shell sort --------------------------------------------------
    while (h > 0)
    {
        for (j = h; j < size; j++)
        {
            // tmp = array[j];
            p = list;
            while(count != j && p != NULL)
            {
                p = p -> next;
                count++;
            }
            i = j;
            while (i >= h && getIminH(list, i, h) -> value > p -> value)
            {
                nodeCmp = getIminH(list, i, h); //get the node at position i - h
                (*n_comp)++; //increment comparison count

                //swap adresses of nodes
                tmp = p -> next;
                p -> next = nodeCmp;
                tmp -> next = nodeCmp -> next;
                nodeCmp -> next = tmp; 


                // array[i] = array[i-h];

                //decrement i by h and then find new array[i]
                i = i - h;
                p = list;
                while(count != i && p != NULL)
                {
                    p = p -> next;
                    count++;
                }
            }
            (*n_comp)++; //increment number of comparisons
        }
        //decrement sequence
        h = (h - 1) / 3;
    }
    //shell sort --------------------------------------------------

}