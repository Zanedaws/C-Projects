#include "shell_array.h"
#include "shell_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    fprintf(stderr,"arguments missing");
    return 0;
  }

  
  int i = 0;
  for(i = 0; i < argc; i++)
  {
    printf("argv[%d] = %s\n", i, argv[i]);
  }

  if(!strcmp(argv[1],"-a"))
  {
    int size = 0;
    long* array = NULL;
    array = Array_Load_From_File(argv[2], &size);
    

    long n_comp = 0;


  
    Array_Shellsort(array, size, &n_comp);


    int writ = 0;

    writ = Array_Save_To_File(argv[3],array,size);

    if(writ != size)
    {
      fprintf(stderr, "written != size of array");
      return 0;
    }

    printf("%ld\n",n_comp);
  }

  if(!strcmp(argv[1], "-l"))
  {
    Node* head = NULL;
    head = List_Load_From_File(argv[2]);

    long n_comp = 0;

    int size = 0;
    Node* p = NULL;

    p = head;

    while(p -> next != NULL)
    {
      p = p -> next;
      size++;
    }

    head = List_Shellsort(head, &n_comp);

    printf("reached\n");

    int writ;

    writ = List_Save_To_File(argv[3], head);

    if(writ != size)
    {
      printf("reached");
      fprintf(stderr,"writ != size");
      exit(EXIT_FAILURE);
      return 0;
    }

    printf("%ld\n", n_comp);
  }


  return 0;
}