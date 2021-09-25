#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;                           // file descriptor
    char arr1[50], arr2[50];    // character array to read and write data
    char *fifofile = "/tmp/fifo"; //FIFO named pipe where to read and write

    mkfifo(fifofile, 0666); // creating named pipe with permission to read and write

    printf("Program2 running");

    fd = open(fifofile, O_WRONLY); // open FIFO in Write only mode
    printf("\nEnter data: ");
    scanf("%s", arr2);                    // read the data from user
    write(fd, arr2, strlen(arr2) + 1); // writing the arr2 array into FIFO
    close(fd);                               // closing file descriptor

    sleep(4); // sleep to wait the process for 4 seconds

    fd = open(fifofile, O_RDONLY);          // open FIFO in Read only mode
    read(fd, arr1, sizeof(arr1));     // read from FIFO
    printf("\nProgram 1: %s\n\n", arr1); // print the read message
    close(fd);

    return 0;
}