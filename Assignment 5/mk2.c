#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;                           // file descriptor
    char buffer1[50], buffer2[50];    // character array to read and write data
    char *fifofile = "/tmp/fifofile"; //FIFO named pipe where to read and write

    // mkfifo(fifofile, 0666); // creating named pipe with permission to read and write
    mknod("mkfile", S_IFIFO | 0666, 0);

    printf("Program 2");

    fd = open(fifofile, O_WRONLY); // open FIFO in Write only mode
    printf("\nEnter text to share: ");
    scanf("%s", buffer2);                    // read the data from user
    write(fd, buffer2, strlen(buffer2) + 1); // writing the buffer2 array into FIFO
    close(fd);                               // closing file descriptor

    sleep(4); // sleep to wait the process for 4 seconds

    fd = open(fifofile, O_RDONLY);          // open FIFO in Read only mode
    read(fd, buffer1, sizeof(buffer1));     // read from FIFO
    printf("\nProgram 1: %s\n\n", buffer1); // print the read message
    close(fd);

    return 0;
}