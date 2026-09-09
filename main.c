#include<stdio.h>
#include"apc.h"

int main(int argc, char *argv[])
{
    
    if(validate_cla_inputs(argc,argv))
    {
        Dlist *head1 = NULL;
        Dlist *tail1 = NULL;

        Dlist *head2 = NULL;
        Dlist *tail2 = NULL;

        Dlist *res_head = NULL;
        Dlist *res_tail = NULL;
        
        if(slicing_input_dll(argv,&head1,&tail1,&head2,&tail2))
        {
            printf("\nArbitrary Precision Calculator\n");
            switch (argv[2][0])
            {
            case '+':
                if(addition(tail1, tail2, &res_head, &res_tail) == 0)
                    printf("Failed to perform addition\n");
                print_res(res_head);
                break;
            case '-':
                if(validate(argv) == 1)
                {
                    if(subtraction(tail1, tail2, &res_head, &res_tail) == 0)
                        printf("Failed to perform addition\n");
                }
                else if(validate(argv) == -1)
                {
                    if(subtraction(tail2, tail1, &res_head, &res_tail) == 0)
                        printf("Failed to perform addition\n");
                    printf("-");
                }
                else
                {
                    printf("0\n");
                }
                print_res(res_head);
                break;
            case '*':
                break;
            case '/':
                break;
            default:
                break;
            }

        }
        else
        {
            printf("Failed to insert data into dll\n");
        }
    }
    else
    {
        printf("Invalid Arguments\n");
        printf("Usage: ./a.out <num1> <operator> <num2>\n");
    }
}

int isNumber(char *str)
{
    int i = 0;

    if(str[i] == '\0')
        return FAILURE;
    
    while(str[i] != '\0')
    {
        if(str[i] < '0' && str[i] > '9')
        {
            return FAILURE;
        }
        i++;
    }
    return SUCCESS;
}

int validate_cla_inputs(int argc, char *argv[])
{
    if(argc == 4)
    {
        if(isNumber(argv[1]) && isNumber(argv[3]))
        {
            if(argv[2][0] == '+' || argv[2][0] == '-' || argv[2][0] == '*' || argv[2][0] == '/')
            {
                return SUCCESS;
            }
        }
    }
    return FAILURE;
}


