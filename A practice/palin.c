#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *str = "wowow";

    int start = 0;
    int end = strlen(str) - 1;
    int palin = 1;
    while (end > 1)
    {
        if (str[start++] != str[end--])
        {
            palin = 0;
        }
    }
    if (palin)
    {
        printf("Palin");
    }
    else
    {
        printf("Not Palin");
    }

    return 0;
}