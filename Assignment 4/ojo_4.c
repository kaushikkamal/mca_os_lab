#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 100

void handle_function(int sig)
{
    pid_t x, y;
    int N, a, b, c, i, fd[2];
    int buffer[SIZE];

    pipe(fd);   // to create a pipe
    x = fork(); // to create a child process
    if (x == 0) // check for child process
    {
        close(fd[0]); // closing read end
        printf("\n\nEnter number of terms of Fibonacci series: \n");
        scanf("%d", &N);
        y = getpid();
        write(fd[1], &y, sizeof(y)); // write process ID in write end
        write(fd[1], &N, sizeof(N)); // write N in write end
        a = 0;
        b = 1;
        write(fd[1], &a, sizeof(a)); // write a in write end
        write(fd[1], &b, sizeof(b)); // write b in write end

        for (i = 2; i < N; i++)
        {
            c = a + b;
            write(fd[1], &c, sizeof(c)); // write c in write end
            a = b;
            b = c;
        }
        write(fd[1], &sig, sizeof(sig)); // write signal ID in write end
        close(fd[1]);                    // closing write end
        exit(0);                         // exit successfully
    }

    else if (x > 0) // check for parent process
    {
        wait(NULL);                 // parent process will wait until the completion of execution of child process
        close(fd[1]);               // closing write end
        read(fd[0], &y, sizeof(y)); // read y from read end of the pipe
        printf("\nProcess ID: %d\n", y);
        read(fd[0], &N, sizeof(N)); // read N from read end
        read(fd[0], buffer, SIZE);  // read fibonacci series in buffer from read end
        printf("\nFibonacci Series:\n");
        for (i = 0; i < N; i++)
        {
            printf("%d  ", *(buffer + i));
        }
        printf("\n\n");
        read(fd[0], &sig, sizeof(sig)); // read signal ID from read end
        printf("Signal ID: %d\n", sig);
        close(fd[0]); // closing read end
        exit(0);      // exit successfully
    }

    else
    {
        printf("Error\n");
        exit(1); // exit unsuccessfully
    }
}

int main()
{
    signal(SIGINT, handle_function); // signal handler
    while (1)                        // infinite loop
    {
    }
    return 0;
}
