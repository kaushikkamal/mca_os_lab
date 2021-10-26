#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char ch,buf[50];
    struct flock lock;

    fd = open("file.txt", O_RDONLY); // open file in read mode

    lock.l_type = F_RDLCK;    // set the lock type to read lock
    lock.l_whence = SEEK_SET; // lock is set from the beginning of time
    fcntl(fd, F_SETLK, &lock); // setting the lock
    
    printf("File locked successfully.");

    read(fd, buf, sizeof(buf));               // read from file

    printf("\nData present in file.txt: %s\n", buf); 
    printf("\nEnter y to unlock the file:  ");
    scanf("%c", &ch); 

    if (ch == 'Y' || ch == 'y')
    {
        lock.l_type = F_UNLCK;     // set the lock type to unlock
        fcntl(fd, F_SETLK, &lock); // unlock the file
        printf("\nFile unlocked successfully.\n");
        exit(0); // exit successfully
    }

    close(fd); // close the file 
    return 0;
}