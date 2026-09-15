#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"apc.h"

void print_res(Dlist *head)
{
    if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    // printf("Result -> ");
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

int validate(char *argv[])
{
    if(strlen(argv[1]) > strlen(argv[3]))
        return 1;
    
    if(strlen(argv[1]) == strlen(argv[3]))
    {
        int i = 0;
        while(argv[1][i] != '\0')
        {   
            if((argv[1][i] - '0') > (argv[3][i] - '0'))
                return 1;
            if((argv[1][i] - '0') < (argv[3][i] - '0'))
                return -1;
            
            i++;
        }
        return 0;
    }
    return -1;
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

int addition(Dlist *tail1, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
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

int subtraction(Dlist *tail1, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    while(tail1 != NULL && tail2 != NULL)
    {
        if(tail1->data < tail2->data)
        {
            tail1->data += 10;

            Dlist *temp = tail1->prev;

            while(temp->data == 0)
            {
                temp->data = 9;
                temp = temp->prev;
            }

            temp->data--;
        }

        if(insert_at_first(tail1->data - tail2->data, res_head, res_tail) == 0)
        {
            return FAILURE;
        }

        tail1 = tail1->prev;
        tail2 = tail2->prev;
    }

    while(tail1 != NULL)
    {
        if(insert_at_first(tail1->data, res_head, res_tail) == 0)
        {
            return FAILURE;
        }

        tail1 = tail1->prev;
    }

    return SUCCESS;
}

int dl_delete_list(Dlist **head, Dlist **tail)
{
    if(*head == NULL)
        return FAILURE;
    
    Dlist *temp = *head;
    
    while(*head != NULL)
    {
        *head = (*head)->next;
        free(temp);
        temp = *head;
    }
    
    *head = NULL;
    *tail = NULL;
    
    return SUCCESS;
}

int multiplication(Dlist *tail1, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    Dlist *temp1;
    Dlist *temp2 = tail2;

    Dlist *temp1_h = NULL;
    Dlist *temp1_t = NULL;

    Dlist *sum_h = NULL;
    Dlist *sum_t = NULL;

    int carry;
    int prod;
    int shift = 0;

    while (temp2 != NULL)
    {
        carry = 0;
        temp1 = tail1;

        while (temp1 != NULL)
        {
            prod = temp1->data * temp2->data + carry;

            insert_at_first(prod % 10, &temp1_h, &temp1_t);

            carry = prod / 10;

            temp1 = temp1->prev;
        }

        if (carry != 0)
        {
            insert_at_first(carry, &temp1_h, &temp1_t);
        }

        for (int i = 0; i < shift; i++)
        {
            insert_at_last(0, &temp1_h, &temp1_t);
        }

        sum_h = NULL;
        sum_t = NULL;

        addition(temp1_t, *res_tail, &sum_h, &sum_t);

        dl_delete_list(res_head, res_tail);

        *res_head = sum_h;
        *res_tail = sum_t;

        dl_delete_list(&temp1_h, &temp1_t);

        shift++;
        temp2 = temp2->prev;
    }

    return SUCCESS;
}