#ifndef APC_H
#define APC_H

#define SUCCESS 1;
#define FAILURE 0;

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Dlist;

/* Function declarations */
int isNumber(char *str);
int validate_cla_inputs(int argc, char *argv[]);
int slicing_input_dll(char *argv[], Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2);
void print_res(Dlist *head);
int insert_at_last(int data, Dlist **head, Dlist **tail);
int insert_at_first(int data, Dlist **head, Dlist **tail);
int addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **res_head, Dlist **res_tail);
int subtraction(Dlist *head1, Dlist *head2, Dlist **result);
int multiplication(Dlist *head1, Dlist *head2, Dlist **result);
int division(Dlist *head1, Dlist *head2, Dlist **result);

#endif