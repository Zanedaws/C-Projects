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