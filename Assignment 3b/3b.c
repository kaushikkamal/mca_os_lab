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
    scanf("%d", &pid);

    printf("\nEnter Signal ID : ");
    scanf("%d", &signal_id);

    res = kill(pid, signal_id);

    // printf("\nStatus: %d\n\n", res);
    return 0;
}
