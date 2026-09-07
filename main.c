#include<stdio.h>
#include"apc.h"

int main(int argc, char *argv[])
{
    
    if(validate_cla_inputs(argc,argv))
    {
        printf("Success");
    }
    else
    {
        printf("Invalid Arguments\n");
        printf("Usage: ./a.out <num1> <operator> <num2>\n");
    }
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

