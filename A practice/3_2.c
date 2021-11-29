#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t x;
    int sig;
    int res;

    printf("Enter Process ID: ");
    scanf("%d", &x);

    printf("\n1. SIGHUP\n");
    printf("2. SIGINT\n");

    printf("\nEnter Signal ID : ");
    scanf("%d", &sig);

    res = kill(x, sig);
    if (res == 0)
    {
        printf("\nKill signal sent successfully\n\n");
    }
    return 0;
}