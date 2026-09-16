#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"apc.h"

#include <stdio.h>
#include <string.h>

void print_res(Dlist *head, char *num1, char operation, char *num2, char sign_res)
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int result_len = 0;
    int width;
    int i;

    Dlist *temp = head;

    while (temp != NULL)
    {
        result_len++;
        temp = temp->next;
    }

    if (sign_res == '-')
        result_len++;

    width = len1;

    if (len2 + 2 > width)
        width = len2 + 2;

    if (result_len > width)
        width = result_len;

    printf("\n");

    for (i = 0; i < (width - 30) / 2 + 4; i++)
        printf(" ");

    printf("Arbitrary Precision Calculator\n\n");

    printf("%*s%s\n", width - len1 + 4, "", num1);

    printf("%*s%c %s\n", width - (len2 + 2) + 4, "", operation, num2);

    printf("%*s", 4, "");

    for (i = 0; i < width; i++)
        printf("-");

    printf("\n");

    printf("%*s", width - result_len + 4, "");

    if (sign_res == '-')
        printf("-");

    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n\n");
}

int compare_lists(Dlist *head1, Dlist *head2)
{
    int count1 = 0;
    int count2 = 0;

    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    while (temp1 != NULL)
    {
        count1++;
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }

    if (count1 > count2)
        return 1;

    if (count1 < count2)
        return -1;

    temp1 = head1;
    temp2 = head2;

    while (temp1 != NULL)
    {
        if (temp1->data > temp2->data)
            return 1;

        if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
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
        if(argv[1][i] >= '0' && argv[1][i] <= '9')
        {
            if(insert_at_last((argv[1][i] - '0'),head1,tail1) == 0)
            {
                return FAILURE;
            }
        }
        i++;
    }

    i = 0;
    while(argv[3][i] != '\0')
    {
        if(argv[3][i] >= '0' && argv[3][i] <= '9')
        {
            if(insert_at_last((argv[3][i] - '0'),head2,tail2) == 0)
            {
                return FAILURE;
            }
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

void signExtraction(char *argv[], char *sign1, char *sign2)
{
    if (argv[1][0] == '-')
        *sign1 = '-';
    else
        *sign1 = '+';

    if (argv[3][0] == '-')
        *sign2 = '-';
    else
        *sign2 = '+';
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

            while(temp != NULL && temp->data == 0)
            {
                temp->data = 9;
                temp = temp->prev;
            }

            if(temp != NULL)
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

    while (*res_head != NULL && (*res_head)->data == 0 && (*res_head)->next != NULL)
    {
        Dlist *temp = *res_head;

        *res_head = (*res_head)->next;
        (*res_head)->prev = NULL;

        free(temp);
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

int division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    Dlist *rem_h = NULL;
    Dlist *rem_t = NULL;

    Dlist *temp_h = NULL;
    Dlist *temp_t = NULL;

    int count;

    if (head2 != NULL && head2->data == 0 && head2->next == NULL)
    {
        printf("ERROR: Division by zero is not possible\n");
        return FAILURE;
    }

    while (head1 != NULL)
    {
        count = 0;

        if (rem_h != NULL &&
            rem_h->data == 0 &&
            rem_h->next == NULL)
        {
            rem_h->data = head1->data;
        }
        else
        {
            insert_at_last(head1->data, &rem_h, &rem_t);
        }

        while (compare_lists(rem_h, head2) >= 0)
        {
            temp_h = NULL;
            temp_t = NULL;

            if (subtraction(rem_t, tail2, &temp_h, &temp_t) == 0)
            {
                printf("Failed to perform subtraction\n");
                return FAILURE;
            }

            dl_delete_list(&rem_h, &rem_t);

            rem_h = temp_h;
            rem_t = temp_t;

            count++;
        }

        insert_at_last(count, res_head, res_tail);

        head1 = head1->next;
    }

    while (*res_head != NULL &&
           (*res_head)->data == 0 &&
           (*res_head)->next != NULL)
    {
        Dlist *temp = *res_head;

        *res_head = (*res_head)->next;
        (*res_head)->prev = NULL;

        free(temp);
    }

    return SUCCESS;
}