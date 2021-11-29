#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#define SIZE 50
void handle(int sig)
{
    pid_t x, y;
    int fd[2], a, b, c, i, N;
    int buffer[SIZE];

    if (pipe(fd) == -1)
    {
        printf("Error i pipe");
    }
    x = fork();

    if (x == 0)
    {
        close(fd[0]);

        y = getpid();
        write(fd[1], &y, sizeof(y));

        printf("Enter N: ");
        scanf("%d", &N);
        write(fd[1], &N, sizeof(N));

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

        write(fd[1], &sig, sizeof(sig));
        
        close(fd[1]);
        
        exit(0);
    }
    else if (x > 0)
    {
        wait(NULL);

        close(fd[1]);
        
        read(fd[0], &y, sizeof(y));
        printf("\nProcess ID: %d\n", y);
        
        read(fd[0], &N, sizeof(N));
        printf("N: %d\n", N);
        
        read(fd[0], buffer, SIZE);
        printf("\nFibonacci Series:\n");
        for (i = 0; i < N; i++)
        {
            printf("%d  ", buffer[i]);
        }
        read(fd[0], &sig, sizeof(sig));
        printf("sig: %d\n", sig);
        printf("\n\n");
        close(fd[0]);
        exit(0);
    }
    else
    {
        exit(1);
    }
}

int main()
{
    signal(SIGINT, handle);
    while (1)
    {
    }
    return 0;
}
