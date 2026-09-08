#include<stdio.h>
#include<stdlib.h>
#include"apc.h"

int insert_at_last(int data, Dlist **head, Dlist **tail)
{   
    Dlist *newNode = malloc(sizeof(Dlist));

    if(newNode == NULL)
        return FAILURE;
    
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if(*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
        return SUCCESS;
    }

    if((*head)->next == NULL)
    {
        (*head)->next = newNode;
        newNode->prev = *head;
        *tail = newNode;
        return SUCCESS;
    }

    (*tail)->next = newNode;
    newNode->prev = *tail;
    *tail = newNode;

    return SUCCESS;
    
}

int slicing_input_dll(char *argv[], Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
    int i = 0;
    while(argv[1][i] != '\0')
    {
        if(insert_at_last((argv[1][i] - '0'),head1,tail1) == 0)
        {
            return FAILURE;
        }
        i++;
    }

    i = 0;
    while(argv[3][i] != '\0')
    {
        if(insert_at_last((argv[3][i] - '0'),head2,tail2) == 0)
        {
            return FAILURE;
        }
        i++;
    }

    return SUCCESS;
}
