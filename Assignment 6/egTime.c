// // /* times: report times used by the current process */
// // /* Paul Krzyzanowski */

// // #include <stdio.h>     /* defines printf() */
// // #include <stdlib.h>    /* to define exit() */
// // #include <unistd.h>    /* for sysconf() */
// // #include <stdint.h>    /* used for casting clock_t to uintmax_t for printf */
// // #include <sys/times.h> /* needed for the times() system call */
// // #include <sys/types.h>
// // #include <sys/stat.h> /* used for open() */
// // #include <fcntl.h>    /* used for open() */

// // void kill_time(void);

// // int main(int argc, char **argv)
// // {
// //     struct tms t; /* the time values will be placed into this struct */

// //     printf("tick frequency is: %lu\n", sysconf(_SC_CLK_TCK));

// //     kill_time(); /* do something to use up some time */
// //     if (times(&t) < 0)
// //     {
// //         perror("times"); /* error - print a message and exit */
// //         exit(1);
// //     }
// //     /* print the results */
// //     printf("user time: %ju ticks\n", (uintmax_t)t.tms_utime);
// //     printf("system time: %ju ticks\n", (uintmax_t)t.tms_stime);
// //     printf("chidren - user time: %ju ticks\n", (uintmax_t)t.tms_cutime);
// //     printf("chidren - system time: %ju ticks\n", (uintmax_t)t.tms_cstime);

// //     exit(0);
// // }

// // void kill_time(void)
// // {
// //     long long i, j; /* use these in a loop to kill time */
// //     int fd;
// //     char buf[2048];

// //     printf("doing some cpu wasting stuff\n");
// //     for (i = 0; i < 100000000; i++)
// //         j += i;

// //     printf("doing some kernel wasting stuff\n");
// //     /* do some stuff to waste system time */
// //     if ((fd = open("/dev/urandom", O_RDONLY)) < 0)
// //     {
// //         perror("open");
// //         exit(1);
// //     }
// //     for (i = 0; i < 1000; i++)
// //         read(fd, buf, 2048);
// //     close(fd);
// // }

// /* times: use times() to get the elapsed time */
// /* Paul Krzyzanowski */

// #include <stdio.h>     /* declares printf() */
// #include <stdlib.h>    /* declares exit() */
// #include <unistd.h>    /* declares sysconf() */
// #include <stdint.h>    /* used for casting clock_t to uintmax_t for printf */
// #include <sys/times.h> /* needed for the times() system call */
// #include <sys/types.h>
// #include <sys/wait.h>

// int main(int argc, char **argv)
// {
//     struct tms t;       /* parameter to times() - we'll ignore it */
//     unsigned long freq; /* clock frequency */
//     uintmax_t start;    /* starting tick value */
//     uintmax_t end;
//     pid_t r = fork();

//     if (r == 0)
//     {
//         freq = sysconf(_SC_CLK_TCK);
//         long long i, j;

//         if ((start = times(&t)) < 0)
//         {                    /* mark the start time */
//             perror("times"); /* error - print a message and exit */
//             exit(1);
//         }
//         for (i = 0; i < 100000000; i++)
//         {
//             j += i;
//         }
//         if ((end = times(&t)) < 0)
//         {                    /* mark the end time */
//             perror("times"); /* error - print a message and exit */
//             exit(1);
//         }

//         printf("Execution time: %5.2f seconds\n", (double)(end - start) / freq);
//     }
//     if (r > 0)
//     {
//         wait(NULL);
//     }

//     exit(0);
// }

/* times: use gettimeofday() to get the elapsed time */
/* Paul Krzyzanowski */

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
        printf("Inside Child Process.\n");
        printf("Enter a character from keyboard and press enter to \nstop the execution, and see the submission and finished time of the child process.\n");

        // Get the current time of day, putting it into *tv.
        gettimeofday(&start, 0);
        getchar();
        gettimeofday(&end, 0);

        // submission time in UTC adding 19800 seconds difference to convert to IST
        // tv_sec gives the time of day in seconds and tv_usec gives in microseconds
        printf("Submission time: %ld s and %.3f ms in IST\n", (start.tv_sec + IST), (start.tv_usec / (double)1000));
        printf("Finished time: %ld s and %.3f ms in IST\n", (end.tv_sec + IST), (end.tv_usec / (double)1000));
    }
    if (r > 0)
    {
        wait(NULL);
    }

    exit(0);
}