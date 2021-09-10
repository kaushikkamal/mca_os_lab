#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle(int sig)
{
    printf("\nSignal ID : %d", sig);
    if (sig == SIGHUP) //  handle SIGHUP
    {
        printf("\nSIGHUP is received\n");
    }
    else if (sig == SIGINT) //  handle SIGINT
    {
        printf("\nSIGINT is received\n");
    }
    else if (sig == SIGILL) //  handle SIGILL
    {
        printf("\nSIGILL is received\n");
    }
    else if (sig == SIGQUIT) //  handle SIGQUIT
    {
        printf("\nSIGQUIT is received\n");
    }
    else if (sig == SIGABRT) //  handle SIGABRT
    {
        printf("\nSIGABRT is received\n");
    }
    else if (sig == SIGBUS) //  handle SIGBUS
    {
        printf("\nSIGBUS is received\n");
    }
    else if (sig == SIGTRAP) //  handle SIGTRAP
    {
        printf("\nSIGTRAP is received\n");
    }
    else
    {
        printf("\nUnhandled signal is received");
    }
    exit(0);
}

int main()
{
    printf("PROCESS ID = %d", getpid());
    signal(SIGHUP, handle);  // signal SIGHUP and signal handler
    signal(SIGINT, handle);  // signal SIGINT and signal handler
    signal(SIGILL, handle);  // signal SIGILL and signal handler
    signal(SIGQUIT, handle); // signal SIGQUIT and signal handler
    signal(SIGABRT, handle); // signal SIGABRT and signal handler
    signal(SIGBUS, handle);  // signal SIGBUS and signal handler
    signal(SIGTRAP, handle); // signal SIGTRAP and signal handler
    while (1)
    {
    }
    return 0;
}