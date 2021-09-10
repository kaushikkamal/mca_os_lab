#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle(int sig)
{
    printf("Signal ID : %d\n", sig);

    switch (sig)
    {
    case SIGHUP:
    {
        printf("Received SIGHUP\n");
        break;
    }
    case SIGINT:
    {
        printf("Received SIGINT\n");
        break;
    }
    case SIGILL:
    {
        printf("Received SIGILL\n");
        break;
    }
    case SIGKILL:
    {
        printf("Received SIGKILL\n");
        break;
    }
    case SIGSTOP:
    {
        printf("Received SIGSTOP\n");
        break;
    }

    default:
        break;
    }
    exit(0);
}

int main()
{
    printf("PROCESS ID = %d \n", getpid());
    signal(SIGHUP, handle);
    signal(SIGINT, handle);
    signal(SIGKILL, handle);
    signal(SIGILL, handle);
    signal(SIGSTOP, handle);
    while (1)
    {
    }
    return 0;
}