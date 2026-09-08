#include<stdio.h>
#include<stdlib.h>
#include"apc.h"

void print_res(Dlist *head)
{
    if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    printf("Result -> ");
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
	    }
    	printf("\n");
    }
}

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

int insert_at_first(int data, Dlist **head, Dlist **tail)
{
    Dlist *newNode = malloc(sizeof(Dlist));

    if(newNode == NULL)
        return FAILURE;
    
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if(*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
        return SUCCESS;
    }

    (*head)->prev = newNode;
    newNode->next = *head;
    *head = newNode;

    return SUCCESS;
}

int addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    int carry = 0;
    int sum;

    while(tail1 != NULL && tail2 != NULL)
    {
        sum = tail1->data + tail2->data + carry;

        if(sum > 9)
        {
            sum = sum - 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        if(insert_at_first(sum, res_head, res_tail) == 0)
            return FAILURE;

        tail1 = tail1->prev;
        tail2 = tail2->prev;
    }

    while(tail1 != NULL)
    {
        sum = tail1->data + carry;

        if(sum > 9)
        {
            sum = sum - 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        if(insert_at_first(sum, res_head, res_tail) == 0)
            return FAILURE;

        tail1 = tail1->prev;
    }

    while(tail2 != NULL)
    {
        sum = tail2->data + carry;

        if(sum > 9)
        {
            sum = sum - 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        if(insert_at_first(sum, res_head, res_tail) == 0)
            return FAILURE;

        tail2 = tail2->prev;
    }

    if(carry == 1)
    {
        if(insert_at_first(carry, res_head, res_tail) == 0)
            return FAILURE;
    }

    return SUCCESS;
}
