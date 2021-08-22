#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t x = fork();

    if (x == 0)
    {
        printf("Child Process\n");
        printf("getpid() = %d \n", getpid());
        printf("getppid() = %d \n", getppid());
        exit(0);
    }

    else if (x > 0)
    {
        wait(NULL);
        printf("Parent Process\n");
        printf("getpid() = %d \n", getpid());
        printf("getppid() = %d \n", getppid());
        exit(0);
    }

    else
    {
        printf("Unsuccessful!\n");
        exit(1);
    }

    return 0;
}