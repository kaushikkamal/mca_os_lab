#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd;              // file descriptor
    char s1[10], s2[10]; // array to read and write data

    printf("Program 2 started..");

    char *fifofile = "/tmp/fifofiles"; // FIFO file where to read and write

    mkfifo(fifofile, 0666); // creating the named pipe to read and write

    fd = open(fifofile, O_WRONLY); // Open FIFO for Write only
    strcpy(s2, argv[1]);           // copying the command line argument into array s2
    write(fd, s2, strlen(s2) + 1); // writing the s2 array into FIFO
    close(fd);                     // closing file descriptor
    sleep(4);                      // sleep to wait the process for few seconds

    fd = open(fifofile, O_RDONLY); // Open FIFO for Read only
    read(fd, s1, sizeof(s1));      // Read from FIFO

    printf("\n Program 1: %s\n\n", s1); // Print the read message
    close(fd);
    return 0;
}