#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int res;
    int signal_id;
    pid_t pid;

    printf("Enter Process ID: ");
    scanf("%d", &pid); // get process id from the user

    printf("\n1. SIGHUP\n");
    printf("2. SIGINT\n");
    printf("3. SIGQUIT\n");
    printf("4. SIGILL\n");
    printf("5. SIGTRAP\n");
    printf("6. SIGABRT\n");
    printf("7. SIGBUS\n");
    printf("8. SIGFPE\n");
    
    printf("\nEnter Signal ID : ");
    scanf("%d", &signal_id); // get signal id from the user

    res = kill(pid, signal_id); // called kill system call

    if (res == 0) // check for kill system status
    {
        printf("\nKill signal sent successfully\n\n");
    }

    return 0;
}
