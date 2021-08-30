#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Replacement process called\n");
    printf("Parent process is %s\n", argv[1]);
    return 0;
}