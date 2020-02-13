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