#include "cs50.h"
#include <stdio.h>

int main(void)
{
    //Prompt user for first number
    int x = get_int("x: ");

    //Prompr user for the second number
    int y = get_int("y: ");

    //Do addition of first and second number
    int z = x + y;

    //Print addition value
    printf("%d \n", z);
}