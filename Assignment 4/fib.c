#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 50

// void handle(int sig) // signal handler function
void handle()
{
    int N;
    int a, b, c, i, res;
    int fd[2], NP[2];
    int buffer[BUFFER_SIZE];
    pid_t x, y;

    res = pipe(fd);
    res = pipe(NP);

    if (res == -1) // error in pipe initialization
    {
        printf("Error in initializing pipe.\n");
        exit(1); // exit unsuccessfully
    }

    x = fork(); // to create a child process

    if (x == 0) // check for child process
    {
        close(fd[0]); // close the read
        close(NP[0]); // close the read

        // y = getpid();

        // write(pi[1], &y, sizeof(y));
        // wait(NULL);

        printf("\n\nEnter the number of terms of the Fibonacci series: ");
        scanf("%d", &N);

        write(NP[1], &N, sizeof(N));

        a = 0;
        b = 1;

        write(fd[1], &a, sizeof(a));
        write(fd[1], &b, sizeof(b));

        for (i = 2; i < N; i++)
        {
            c = a + b;
            write(fd[1], &c, sizeof(c));
            a = b;
            b = c;
        }

        close(fd[1]); // close the write
        close(NP[1]); // close the write
    }

    else if (x > 0) // check for parent process
    {
        wait(NULL); // wait is used so that the parent process waits until the completion of execution of child process

        close(fd[1]); // close the write
        close(NP[1]); // close the write

        read(NP[0], &N, sizeof(N));
        read(fd[0], buffer, BUFFER_SIZE);

        for (i = 0; i < N; i++)
        {
            printf("%d  ", *(buffer + i));
        }
        printf("\n\n");
        
        close(fd[0]); // close the read
        close(NP[0]); // close the read
    }

    else
    {
        printf("Unsuccessful, error occured in creating the child process.\n");
        exit(1); // exit unsuccessfully
    }
    // return 0;
}

int main()
{
    handle();
    // signal(SIGINT, handle); // signal handling
    // while (1)               // infinite loop
    // {
    // }
    return 0;
}
