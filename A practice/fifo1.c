#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fd;
    char *fifofile = "/tmp/fifo";
    char buffer1[100], buffer2[100];

    mkfifo(fifofile, 0666);

    sleep(5);

    fd = open(fifofile, O_RDONLY);
    read(fd, buffer1, sizeof(buffer1));
    printf("From p 2: %s", buffer1);
    close(fd);

    fd = open(fifofile, O_WRONLY);
    strcpy(buffer2, "ACK");
    write(fd, buffer2, sizeof(buffer2) + 1);
    close(fd);

    return 0;
}