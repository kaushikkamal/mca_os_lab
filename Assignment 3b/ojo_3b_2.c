#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int signal_id;
    pid_t process_id;

    printf("Enter Process ID: ");
    scanf("%d", &process_id);

    printf("\n1. SIGHUP\n");
    printf("2. SIGINT\n");
    printf("3. SIGQUIT\n");
    printf("4. SIGILL\n");
    printf("5. SIGTRAP\n");
    printf("6. SIGABRT\n");
    printf("7. SIGBUS\n");

    printf("\nEnter Signal ID : ");
    scanf("%d", &signal_id);

    kill(process_id, signal_id); // kill system call

    return 0;
}
