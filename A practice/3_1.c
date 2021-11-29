#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle(int sig)
{
    printf("Signal ID : %d\n", sig); // print signal ID
    switch (sig)
    {
    case SIGHUP:
    {
        printf("SIGHUP received\n");
        break;
    }
    case SIGINT:
    {
        printf("SIGINT received\n");
        break;
    }
    default:
    {
        break;
    }
    }
    exit(0);
}

int main()
{
    printf("PROCESS ID = %d \n", getpid());

    signal(SIGHUP, handle);
    signal(SIGINT, handle);

    while (1)
    {
    }
    return 0;
}