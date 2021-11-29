#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

#define IST 19800

int main()
{
    // timeval struct taken from sys/time.h for using gettimeofday()
    struct timeval start; /* submission time */
    struct timeval end;   /* finished time */

    pid_t r = fork(); // creating child process

    if (r == 0)
    {
        FILE *fptr;
        fptr = fopen("myFile.txt", "w");

        printf("Inside Child Process.\n");
        printf("Enter a character from keyboard and press enter to \nstop the execution, and see the submission and finished time of the child process.\n");

        // Get the current time of day, putting it into *tv.
        gettimeofday(&start, 0);
        getchar();
        gettimeofday(&end, 0);

        printf("Data to be stored in the created file.\n");
        // submission time in UTC adding 19800 seconds difference to convert to IST
        // tv_sec gives the time of day in seconds and tv_usec gives in microseconds
        printf("Submission time: %ld s and %.3f ms in IST\n", (start.tv_sec + IST), (start.tv_usec / (double)1000));
        printf("Finished time: %ld s and %.3f ms in IST\n", (end.tv_sec + IST), (end.tv_usec / (double)1000));

        fprintf(fptr, "Submission time: ");
        fprintf(fptr, "%ld s and %.3f ms in IST", (start.tv_sec + IST), (start.tv_usec / (double)1000));
        fprintf(fptr, "\n");
        fprintf(fptr, "Finished time: ");
        fprintf(fptr, "%ld s and %.3f ms in IST", (end.tv_sec + IST), (end.tv_usec / (double)1000));
        fclose(fptr);
    }
    if (r > 0)
    {
        wait(NULL);
    }

    exit(0);
}