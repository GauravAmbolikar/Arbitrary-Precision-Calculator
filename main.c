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

        char sign1;
        char sign2;
        char sign_res;
        
        if(slicing_input_dll(argv,&head1,&tail1,&head2,&tail2))
        {
            signExtraction(argv, &sign1, &sign2);
            switch (argv[2][0])
            {
            case '+':
            {
                if(sign1 == sign2)
                {
                    if(addition(tail1, tail2, &res_head, &res_tail) == 0)
                        printf("Failed to perform addition\n");
                    sign_res = sign1;
                }
                else
                { 
                    int ret = compare_lists(head1, head2);
                    if (ret == 0)
                    {
                        // Equal numbers → result is 0
                        sign_res = '+';
                        if(subtraction(tail1, tail2, &res_head, &res_tail) == 0)
                        {
                            printf("Failed to perform subtraction\n");
                            return 0;
                        }
                    }
                    else if (ret > 0)
                    {
                        // number1 is larger
                        if(subtraction(tail1, tail2, &res_head, &res_tail) == 0)
                        {
                            printf("Failed to perform subtraction\n");
                            return 0;
                        }
                        sign_res = sign1;
                    }
                    else
                    {
                        // number2 is larger
                        if(subtraction(tail2, tail1, &res_head, &res_tail) == 0)
                        {
                            printf("Failed to perform subtraction\n");
                            return 0;
                        }
                        sign_res = sign2;   
                    }
                }
                print_res(res_head, argv[1], argv[2][0], argv[3], sign_res);
                break;
            }
            case '-':
            {
                // Flip sign of second number
                if (sign2 == '+')
                    sign2 = '-';
                else
                    sign2 = '+';

                // Now use addition sign logic
                if (sign1 == sign2)
                {
                    if(addition(tail1, tail2, &res_head, &res_tail) == 0)
                    {
                        printf("Failed to perform addition\n");
                        return 0;
                    }
                    sign_res = sign1;
                }
                else
                {
                    int ret = compare_lists(head1, head2);

                    if (ret == 0)
                    {
                        sign_res = '+';
                        if(subtraction(tail1, tail2, &res_head, &res_tail) == 0)
                        {
                            printf("Failed to perform subtraction\n");
                            return 0;
                        }
                    }
                    else if (ret > 0)
                    {
                        if(subtraction(tail1, tail2, &res_head, &res_tail) == 0)
                        {
                            printf("Failed to perform subtraction\n");
                            return 0;
                        }

                        sign_res = sign1;
                    }
                    else
                    {
                        if(subtraction(tail2, tail1, &res_head, &res_tail) == 0)
                        {
                            printf("Failed to perform subtraction\n");
                            return 0;
                        }
                        sign_res = sign2;
                    }
                }
                print_res(res_head, argv[1], argv[2][0], argv[3], sign_res);
                break;
            }
            case '*':
            {
                if(multiplication(tail1, tail2, &res_head, &res_tail) == 0)
                {
                    printf("Failed to perform multiplication\n");
                    return 0;
                }

                if (sign1 == sign2)
                    sign_res = '+';
                else
                    sign_res = '-';

                print_res(res_head, argv[1], argv[2][0], argv[3], sign_res);
                break;
            }
            case '/':
                if(division(head1, tail1, head2, tail2, &res_head, &res_tail) == 0)
                {
                    printf("Failed to perform division\n");
                    return 0;
                }

                if (sign1 == sign2)
                    sign_res = '+';
                else
                    sign_res = '-';

                print_res(res_head, argv[1], argv[2][0], argv[3], sign_res);
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

    return 0;
}

int isNumber(char *str)
{
    int i = 0;

    if(str[i] == '+' || str[i] == '-')
        i++;

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


