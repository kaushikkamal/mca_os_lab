#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t x = fork();
    char *args[] = {"./1cc", argv[0], NULL};
    int status;

    if (x == 0)
    {
        printf("\nChild Process\n");
        printf("%s is name of the main process\n", argv[0]);
        execv(args[0], args);
        printf("pid of the child %d\n", getpid());
        printf("pid of the child's parent %d\n", getppid());
        exit(0);
    }

    else if (x > 0)
    {
        wait(&status);
        printf("\nParent Process\n");
        printf("Returned value of the child process is %d\n", WIFEXITED(status));
        printf("pid of the parent %d\n", getpid());
        printf("pid of the parent's parent %d\n", getppid());
        exit(0);
    }

    else
    {
        printf("Unsuccessful, error occured in creating the child process.\n");
        exit(1); 
    }

    return 0;
}
