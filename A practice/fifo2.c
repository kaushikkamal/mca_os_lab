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

    fd = open(fifofile, O_WRONLY);
    printf("Enter text to share: ");
    scanf("%s", buffer1);
    write(fd, buffer1, sizeof(buffer1) + 1);
    close(fd);

    sleep(5);

    fd = open(fifofile, O_RDONLY);
    read(fd, buffer2, sizeof(buffer2));
    printf("From p 1: %s", buffer2);
    close(fd);
    return 0;
}