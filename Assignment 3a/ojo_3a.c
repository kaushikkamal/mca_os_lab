#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void handle_function(int sig)
{
    pid_t x = fork(); // to create a child process

    if (x == 0) // check for child process
    {
        printf("\nChild Process\n");
        printf("PROCESS ID = %d", getpid());              // process id of child process
        printf("\nPARENT PROCESS ID = %d \n", getppid()); // process id of child's parent process
        exit(0);                                          // exit successfully
    }

    else if (x > 0) // check for parent process
    {
        wait(NULL);
        printf("\nParent Process\n");
        printf("PROCESS ID = %d", getpid());              // process id of parent process
        printf("\nPARENT PROCESS ID = %d \n", getppid()); // process id of parent's parent process
        exit(0);                                          // exit successfully
    }

    else
    {
        printf("Error\n");
        exit(1); // exit unsuccessfully
    }
}

int main()
{
    signal(SIGINT, handle_function); // signal handling
    while (1)                        // infinite loop
    {
    }
    return 0;
}