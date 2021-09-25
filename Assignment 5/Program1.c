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

    mkfifo(fifofile, 0666); // creating named pipe with permission to read and write

    printf("Program 1");
    
    sleep(5); // sleep is used to keep the program waiting for 5 secs

    fd = open(fifofile, O_RDONLY);      // open FIFO in Read only mode
    read(fd, buffer1, sizeof(buffer1)); // read from FIFO
    printf("\nProgram 2: %s\n\n", buffer1); // print the read message
    close(fd);                               // closing file descriptor

    fd = open(fifofile, O_WRONLY);           // open FIFO in Write only mode
    strcpy(buffer2, "ACKNOWLEDGEMENT");      // copying ACKNOWLEDGEMENT String to array buffer2
    write(fd, buffer2, strlen(buffer2) + 1); // writing ACKNOWLEDGEMENT msg into the FIFO file
    close(fd);                               // closing file descriptor

    return 0;
}