#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/times.h>

int main()
{
    struct tms before, after;
    pid_t x;
    times(&before);
    /* ... place code to be timed here ... */
    x = fork();
    if (x == 0)
    {
        exit(0);
    }
    else if (x < 0)
    {
        printf("Unsuccessful, error occured in creating the child process.\n");
        exit(1);
    }
    times(&after);
    printf("User time: %ld seconds\n", after.tms_utime - before.tms_utime);
    printf("System time: %ld seconds\n", after.tms_stime - before.tms_stime);
    exit(0);
}