#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int num = 70;
    int prime = 1;
    int i;
    int square_root;

    if (num < 0)
    {
        printf("\nEnter positive number");
        exit(0);
    }
    else if (num == 1)
    {
        prime = 0;
    }
    else
    {
        square_root = sqrt(num);
        for (i = 2; i < square_root; i++)
        {
            if (num % i == 0)
            {
                prime = 0;
            }
        }
    }

    if (prime)
    {
        printf("\nPrime");
    }
    else
    {
        printf("\nNot Prime");
    }

    return 0;
}