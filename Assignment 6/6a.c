#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t p = fork();

    FILE *fptr;

    fptr = fopen("file.txt", "w");

    if (p == 0)
    {
        time_t begin = time(NULL);

        printf("Child process\n");
        printf("Child Process Id: %d\n", getpid());
        printf("Child Parent Id: %d\n", getppid());
        sleep(3);
        time_t end = time(NULL);

        fprintf(fptr, "Submission time ");
        fprintf(fptr, "%ld", begin);
        fprintf(fptr, "\n");
        fprintf(fptr, "Finish time ");
        fprintf(fptr, "%ld", end);
        fclose(fptr);

        printf("Submission time is %ld seconds: ", begin);
        printf("Finished time is %ld seconds: ", end);
    }
    exit(0);
}