#ifndef APC_H
#define APC_H

typedef struct node
{
    int data;
    struct node *link;
} Dlist;

/* Function declarations */
int validate_number(char *str);
int addition(Dlist *head1, Dlist *head2, Dlist **result);
int subtraction(Dlist *head1, Dlist *head2, Dlist **result);
int multiplication(Dlist *head1, Dlist *head2, Dlist **result);
int division(Dlist *head1, Dlist *head2, Dlist **result);

#endif