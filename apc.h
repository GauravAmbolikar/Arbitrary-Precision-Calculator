#ifndef APC_H
#define APC_H

#define SUCCESS 1;
#define FAILURE 0;

typedef struct node
{
    int data;
    struct node *link;
} Dlist;

/* Function declarations */
int validate_cla_inputs(char *str);
int addition(Dlist *head1, Dlist *head2, Dlist **result);
int subtraction(Dlist *head1, Dlist *head2, Dlist **result);
int multiplication(Dlist *head1, Dlist *head2, Dlist **result);
int division(Dlist *head1, Dlist *head2, Dlist **result);

#endif