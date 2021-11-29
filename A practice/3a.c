#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void handle(int sig)
{
    printf("\nSignal id: %d", sig);

    pid_t x = fork();

    if (x == 0)
    {
        printf("\n\nChild process id: %d", getpid());
        printf("\nChild's parent process id: %d", getppid());
        exit(0);
    }
    else if (x > 0)
    {
        wait(NULL);
        printf("\n\nParent process id: %d", getpid());
        printf("\nParent's parent process id: %d", getppid());
        exit(0);
    }
    else
    {
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