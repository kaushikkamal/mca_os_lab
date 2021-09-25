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

    printf("Program 1 waiting ... ");

    char *fifofile = "/tmp/fifofiles"; //FIFO the named pipe where to read and write

    mkfifo(fifofile, 0666); // creating FIFO i.e named pipe ; with permission to read and write

    sleep(5); // sleep is used to keep the program waiting for few secs

    fd = open(fifofile, O_RDONLY); // Open FIFO for Read only
    read(fd, s1, sizeof(s1));      // Read from FIFO

    printf("\n Program 2: %s\n\n", s1); // Print the read message
    close(fd);                          // closing file descriptor

    fd = open(fifofile, O_WRONLY); // Open FIFO for Write only
    strcpy(s2, "ACK");             // copying Acknowledge String "OK" to array s2
    write(fd, s2, strlen(s2) + 1); // writing ACK msg into the FIFO file
    close(fd);                     // closing file descriptor

    return 0;
}