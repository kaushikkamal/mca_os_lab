#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 50

void handle(int sig) // signal handler function
{
    int N;
    int a, b, c, i;
    int fd[2];               // pipe
    int buffer[BUFFER_SIZE]; // to store fibonacci series
    pid_t x, y;

    if (pipe(fd) == -1) // check if pipe is initialized or not
    {
        printf("Error in initializing pipe.\n");
        exit(1); // exit unsuccessfully
    }

    x = fork(); // creating a child process

    if (x == 0) // check for child process
    {
        close(fd[0]); // closing the read end

        printf("\nEnter the number of terms of the Fibonacci series: ");
        scanf("%d", &N); // user input for N

        y = getpid(); // child's process id is stored in y

        write(fd[1], &y, sizeof(y)); // write process ID in write end of the pipe
        write(fd[1], &N, sizeof(N)); // write N in write end of the pipe

        a = 0;
        b = 1;

        write(fd[1], &a, sizeof(a)); // write a in write end of the pipe
        write(fd[1], &b, sizeof(b)); // write b in write end of the pipe

        for (i = 2; i < N; i++)
        {
            c = a + b;
            write(fd[1], &c, sizeof(c)); // write c in write end of the pipe
            a = b;
            b = c;
        }

        write(fd[1], &sig, sizeof(sig)); // write signal ID in write end of the pipe

        close(fd[1]); // closing the write end

        exit(0); // exit successfully
    }

    else if (x > 0) // check for parent process
    {
        wait(NULL); // wait is used so that the parent process waits until the completion of execution of child process

        close(fd[1]); // closing the write end

        read(fd[0], &y, sizeof(y));      // read y(process id) from read end of the pipe
        printf("\nProcess ID: %d\n", y); // print process ID

        read(fd[0], &N, sizeof(N));       // read N from read end of the pipe
        read(fd[0], buffer, BUFFER_SIZE); // read fibonacci series in buffer from read end of the pipe

        printf("\nFibonacci Series:\n");
        for (i = 0; i < N; i++)
        {
            printf("%d  ", *(buffer + i)); // print fibonacci series
        }
        printf("\n\n");

        read(fd[0], &sig, sizeof(sig)); // read signal ID from read end of the pipe
        printf("Signal ID: %d  ", sig); // print signal ID
        printf("\n\n");

        close(fd[0]); // closing the read end

        exit(0); // exit successfully
    }

    else
    {
        printf("Unsuccessful, error occured in creating the child process.\n");
        exit(1); // exit unsuccessfully
    }
}

int main()
{
    signal(SIGINT, handle); //register signal SIGINT and signal handler
    while (1)               // infinite loop
    {
    }
    return 0;
}
