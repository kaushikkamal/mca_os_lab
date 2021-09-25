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

    printf("Program1 running");

    sleep(5); // sleep is used to keep the program waiting for 5 secs

    fd = open(fifofile, O_RDONLY);          // open FIFO in Read only mode
    read(fd, arr1, sizeof(arr1));     // read from FIFO
    printf("\nProgram 2: %s\n\n", arr1); // print the read message
    close(fd);                              // closing file descriptor

    fd = open(fifofile, O_WRONLY);           // open FIFO in Write only mode
    strcpy(arr2, "ACKNOWLEDGEMENT");      // copying ACKNOWLEDGEMENT String to array arr2
    write(fd, arr2, strlen(arr2) + 1); // writing ACKNOWLEDGEMENT msg into the FIFO file
    close(fd);                               // closing file descriptor

    return 0;
}