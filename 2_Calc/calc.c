#include "stdio.h"

void get_menu() {
    printf("Select\n");
    printf("1: Plus\n");
    printf("2: Minus\n");
    printf("3: Multiplication\n");
    printf("4: Division\n");
    printf("5: Exit\n");
    printf("->");
}

int act_plus(int a,int b)
{
    return a+b;
}

int act_minus(int a,int b)
{
    return a-b;
}

int act_mult(int a,int b)
{
    return a*b;
}

float act_division(int a,int b)
{
    return (float) a/b;
}