#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    pid_t x = fork();
    
    if (x == 0)
    {
        printf("Child Process\n");
        printf("pid of the child = %d \n", getpid());
        printf("pid of the child's parent = %d \n", getppid());
        exit(0);
    }

    else if (x > 0)
    {
        printf("Parent Process\n");
        printf("pid of the parent = %d \n", getpid());
        printf("pid of the parent's parent = %d \n", getppid());
        exit(0);
    }

    else
    {
        printf("Unsuccessful, error occured in creating the child process.\n");
        exit(1);
    }

    return 0;
}