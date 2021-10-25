#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char ch, buf[50];
    struct flock lock; 

    fd = open("file.txt", O_RDONLY); // open file in Read only mode

    lock.l_type = F_RDLCK;    // set the lock type to read lock
    lock.l_whence = SEEK_SET; // lock is set from the beginning of time

    do
    {
        fcntl(fd, F_GETLK, &lock);  // system call to check if lock is there or not
        if (lock.l_type != F_UNLCK) // lock is present
        {
            printf("\nFile is locked! press y to try again to access it: ");
            scanf("%c", &ch); 
        }
        else // no lock is not present
        {
            read(fd, buf, sizeof(buf));               // read from file
            printf("\nData from data.txt: %s\n\n", buf);
            exit(0);                                        // exit successfully
        }

    } while (ch != 'Y' || ch != 'y');

    close(fd); // close the file
    return 0;
}