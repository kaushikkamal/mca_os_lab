#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void handle(int sig) // signal handler function
{
    pid_t x = fork(); // to create a child process

    if (x == 0) // check for child process
    {
        printf("\nIn Child Process\n");
        printf("PROCESS ID = %d \n", getpid());         // process id of child process
        printf("PARENT PROCESS ID = %d \n", getppid()); // process id of child's parent process
        exit(0);                                        // exit successfully
    }

    else if (x > 0) // check for parent process
    {
        wait(NULL); // wait is used so that the parent process waits until the completion of execution of child process
        printf("\nIn Parent Process\n");
        printf("PROCESS ID = %d \n", getpid());         // process id of parent process
        printf("PARENT PROCESS ID = %d \n", getppid()); // process id of parent's parent process
        exit(0);                                        // exit successfully
    }

    else
    {
        printf("Unsuccessful, error occured in creating the child process.\n");
        exit(1); // exit unsuccessfully
    }
}

int main()
{
    signal(SIGINT, handle); // signal handling
    while (1)               // infinite loop
    {
    }
    return 0;
}