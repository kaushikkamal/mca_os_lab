#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

// void handle(int sig)
// {
//     switch (sig)
//     {
//     case SIGHUP:
//     {
//         printf("\nSIGHUP");
//         break;
//     }
//     case SIGINT:
//     {
//         printf("\nSIGINTP");
//         break;
//     }

//     default:
//         break;
//     }
//     exit(0);
// }

int main()
{
    int res, signal_id;
    printf("\n1. SIGHUP\n");
    printf("2. SIGINT\n");

    printf("\nEnter Signal ID : ");
    scanf("%d", &signal_id); // get signal id from the user

    printf("\n\nbefore raise");
    res = raise(signal_id);
    if (res == 0) // check for kill system status
    {
        printf("\nKill signal sent successfully\n\n");
    }
    return 0;
}