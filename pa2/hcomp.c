#include "hcomp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

list* readFromFIle(char* filename, list* head)
{
    FILE * fh = fopen(filename, "rb");

    if(fh == NULL)
    {
        fprintf(stderr, "file failed to open\n");
        return NULL;
    }

    char tmp = NULL;

    while(!feof(fh))
    {
        tmp = fgetc(fh);
        if(!feof(fh))
        {
            head = addListNode(head, tmp);
        }
    }

    fclose(fh);

    return head;
}


list* addListNode(list* head, char letter)
{
    if(head == NULL)
    {
        list* node = malloc(sizeof(*node));
        node -> chr = letter;
        node -> code = NULL;
        node -> freq = 1;
        node -> next = NULL;
        head = node;
        return head;
    }

    list* p = head;

    while(letter != p -> chr && p -> next != NULL)
    {
        p = p -> next;
    }

    if(letter == p -> chr)
    {
        p -> freq += 1;
        return head;
    }

    if(p -> next == NULL)
    {
        list* node = malloc(sizeof(*node));
        node -> chr = letter;
        node -> code = NULL;
        node -> freq = 1;
        node -> next = NULL;
        p -> next = node;
        return head;
    }
}

list* destroyList(list* head)
{

    if(head == NULL)
        return head;

    list* p = head;
    while(p -> next != NULL)
    {
        p = p -> next;
    }

    free(p);

    destroyList(head);
}

void freqOutput(char* filename, list* head)
{
    FILE* fh = fopen(filename, "wb");
    list* p = head;

    while(p != NULL)
    {
        fwrite(&(p -> freq), sizeof(long), 1, fh);
        p = p -> next;
    }

    return;
}

// list* sortList(list* head)
// {
//     list* p = head;
//     long tmp = 0;
//     int h = 0;
//     int size = 0;

//     while(p -> next != NULL)
//     {
//         size++;
//         p = p -> next;
//     }

//     p = head;

//     do
//     {
//         h = 3 * h + 1;
//     }while(h < size);
//     if(size != h)
//         h = (h-1) / 3;

//     //indexing variables
//     int j = 0;
//     int i = 0;
//     int c = 0; //counts where in the list we are

//     long tmp = 0; //tmp variable for swapping purposes

//     list* arrJ = NULL; //array[j]
//     list* arrIH = NULL; //array[i - h]
//     list* arrI = NULL; //array[i]
//     list* parrI = NULL; //array[i - 1]
//     list* psarrIH = NULL; //array[i - h + 1]
//     list* parrIH = NULL; //array[i - h - 1]

//     while(h > 0)
//     {
//         for(j = h; j < size; j++)
//         {
//             //find the location of arr[j]
//             while(c != j)
//             {
//                 p = p -> next;
//             }
//             arrJ = p; //assign arrJ to be a pointer to list index j
//             p = head; //reset the p pointer to head
//             c = 0; //reset the counter variable

//             i = j; //set i index starting point


//             //find the location of arr[i - h]
//             while(c != i - h)
//             {
//                 p = p -> next;
//             }
//             arrIH = p; //assign arrIH to be a pointer to list index i - h
//             p = head; //reset the p pointer to head
//             c = 0; //reset the counter variable

//             while(i >= h && arrIH -> freq > tmp -> freq)
//             {
//                 //find the location of arr[i]
//                 while(c != i)
//                 {
//                     p = p -> next;
//                 }
//                 arrI = p; //assign arrI to be a pointer to list index i
//                 p = head; //reset the p pointer to head
//                 c = 0; //reset the counter variable

//                 if(arrIH == head)
//                 {
//                     if(arrI != head -> next)
//                     {    
//                         //get the position before the index i in the list
//                         while(p -> next != arrI)
//                         {
//                             p = p -> next;
//                         }
//                         parrI = p;
//                         p = head;
//                     }
//                     else
//                         parrI = NULL;

//                     //check if a post index i - h is needed
//                     if(parrI == NULL && parrI != arrIH -> next)
//                         psarrIH = arrIH -> next;
//                     else
//                         psarrIH = NULL;

//                     //swapping addresses
//                     if(arrI != head -> next)
//                         parrI -> next = arrIH;   
//                     arrIH -> next = arrI -> next;
//                     if(psarrIH == NULL)
//                         if(arrI != head -> next)
//                             arrI -> next = parrI;
//                         else
//                             arrI -> next = arrIH;
//                     else
//                         arrI -> next = psarrIH;
//                     head = arrI;
//                 }

//                 if(arrIH != head)
//                 {
//                     //get list node before array[i]
//                     if(arrI != arrIH -> next)
//                     {
//                         while(p -> next != arrI)
//                         {
//                             p = p -> next;
//                         }
//                         parrI = p;
//                         p = head;
//                     }

//                     //get list node before array[i - h]
//                     if(arrIH != head -> next)
//                     {
//                         while(p -> next != arrIH)
//                         {
//                             p = p -> next;
//                         }
//                         parrIH = p;
//                         p = head;
//                     }
//                     else
//                         parrIH = head;

//                     if(arrIH -> next != arrI)
//                         psarrIH = arrIH -> next;

//                     parrIH -> next = arrI;
//                     arrIH -> next = arrI -> next;
//                     if(psarrIH != NULL)

                    

//                 }

//             }
//         }
//     }





//     // while(p -> next != NULL)
//     // {
//     //     if(p -> next -> freq > p -> freq)
//     //     {
//     //         tmp = p -> freq;
//     //         p -> freq = p -> next -> freq;
//     //         p -> next -> freq = tmp;
//     //     }
//     //     p = p -> next;
//     // }
// }

Tree* buildTree(Tree* root, list* head)
{

}