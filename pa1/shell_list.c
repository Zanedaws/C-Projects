#include "shell_list.h"
#include <stdlib.h>
#include <stdio.h>
Node* addNode(Node* head, long val);
Node* destroyList(Node* head);
Node* swapNodes(Node* head, Node* n1, Node* n2);

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


Node* swapNodes(Node* head, Node* n1, Node* n2)
{
    Node * p = head;
    Node * q = head;
    
    fprintf(stderr, "head = %ld\n", head -> value);
    fprintf(stderr, "n1 = %ld\n", n1 -> value);
    fprintf(stderr, "n2 = %ld\n", n2 -> value);

    fprintf(stderr, "n1 == head: %d\n", n1 == head);

    if(n1 != head)
    {
        //p finds previous of n1
        while(p -> next != n1)
        {
            p = p -> next;
        }

        if(n2 != head)
        {
            //q finds previous of n2
            while(q -> next != n2)
            {
                q = q -> next;
            }

            Node * tmp = n1 -> next;
            n1 -> next = n2 -> next;
            n2 -> next = tmp;
            p -> next = n2;
            q -> next = n1;
            return head;
        }
        else if (n2 == head)
        {
            Node * tmp = n1 -> next;
            n1 -> next = n2 -> next;
            n2 -> next = tmp;
            p -> next = n2;
            head = n1;
            return head;
        }
        
    }
    
    return head;
}

Node *List_Load_From_File(char *filename)
{
    //opening file
    FILE *fh = fopen(filename, "r");
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
    long size = 0;

    while(p -> next != NULL)
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

    //increment variables
    long j;
    long i;
    long k = 0;

    //
    Node* arrIminH = list;
    Node* tmp = NULL;
    Node* arrI = list;

    //shell sort --------------------------------------------------
    while (h > 0)
    {
        for (j = h; j < size; j++)
        {
            tmp = list;
            while(k != j)
            {
                tmp = tmp -> next;
                k++;
            }
            k = 0;

            i = j;
            
            arrIminH = list;
            while(k != i - h)
            {
                arrIminH = arrIminH -> next;
                k++; 
            }
            k = 0;

            while (i >= h && arrIminH -> value > tmp -> value)
            {
                (*n_comp)++;

                arrIminH = list;
                while(k != i - h)
                {
                    arrIminH = arrIminH -> next;
                    k++; 
                }
                k = 0;

                arrI = list;

                while(k != i)
                {
                    arrI = arrI -> next;
                    k++;
                }
                k = 0;

                fprintf(stderr, "here\n");

                Node * preArrI = list;
                while(preArrI != arrI && preArrI -> next != arrI);
                    preArrI = preArrI -> next;

                fprintf(stderr, "here\n");

                Node * preArrIH = list;
                while(preArrIH != arrIminH && preArrIH -> next != arrIminH)
                    preArrIH = preArrIH -> next;

                Node* pstArrI = arrI -> next;

                arrI -> next = arrIminH -> next;
                preArrI -> next = arrIminH;
                arrIminH -> next = pstArrI;
                preArrIH -> next = arrI;

                i = i - h;

                arrI -> next = arrIminH -> next;
                preArrI -> next = arrIminH;
                arrIminH -> next = pstArrI;
                preArrIH -> next = arrI;

                
            }
            (*n_comp)++; //increment number of comparisons
        }
        //decrement sequence
        h = (h - 1) / 3;
    }
    //shell sort --------------------------------------------------

    return list;

}