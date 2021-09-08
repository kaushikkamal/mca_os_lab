#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handle(int sig)
{
    pid_t x = fork();

    if (x == 0)
    {
        printf("\nIn Child Process\n");
        printf("PROCESS ID = %d \n", getpid());
        printf("PARENT PROCESS ID = %d \n", getppid());
        exit(0);
    }

    else if (x > 0)
    {
        wait(NULL);
        printf("\nIn Parent Process\n");
        printf("PROCESS ID = %d \n", getpid());
        printf("PARENT PROCESS ID = %d \n", getppid());
        exit(0);
    }

    else
    {
        printf("Unsuccessful, error occured in creating the child process.\n");
        exit(1);
    }
}

int main()
{
    signal(SIGINT, handle);
    while (1)
    {
    }
    return 0;
}