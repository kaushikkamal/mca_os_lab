#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle(int sig) // signal handler function
{
    printf("Signal ID : %d\n", sig); // print signal ID

    switch (sig)
    {
    case SIGHUP: // to handle SIGHUP
    {
        printf("Received SIGHUP\n");
        break;
    }
    case SIGINT: // to handle SIGINT
    {
        printf("Received SIGINT\n");
        break;
    }
    case SIGQUIT: // to handle SIGQUIT
    {
        printf("Received SIGQUIT\n");
        break;
    }
    case SIGILL: // to handle SIGILL
    {
        printf("Received SIGILL\n");
        break;
    }
    case SIGTRAP: // to handle SIGTRAP
    {
        printf("Received SIGTRAP\n");
        break;
    }
    case SIGABRT: // to handle SIGABRT
    {
        printf("Received SIGABRT\n");
        break;
    }
    case SIGBUS: // to handle SIGBUS
    {
        printf("Received SIGBUS\n");
        break;
    }
    case SIGFPE: // to handle SIGFPE
    {
        printf("Received SIGFPE\n");
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
    signal(SIGHUP, handle);  //register signal SIGHUP and signal handler
    signal(SIGINT, handle);  //register signal SIGINT and signal handler
    signal(SIGQUIT, handle); //register signal SIGQUIT and signal handler
    signal(SIGILL, handle);  //register signal SIGILL and signal handler
    signal(SIGTRAP, handle); //register signal SIGTRAP and signal handler
    signal(SIGABRT, handle); //register signal SIGABRT and signal handler
    signal(SIGBUS, handle);  //register signal SIGBUS and signal handler
    signal(SIGFPE, handle);  //register signal SIGFPE and signal handler
    while (1)                // infinite loop
    {
    }
    return 0;
}