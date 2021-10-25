#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char choice;
    char buffer[50];
    struct flock lock; // defining lock

    fd = open("data.txt", O_RDONLY); // open file in Read only mode

    if (fd < 0) // check if file is opened or not
    {
        exit(1); // exit unsuccessfully
    }

    lock.l_type = F_RDLCK;    // set the lock type to read lock
    lock.l_whence = SEEK_SET; // lock is set from the beginning of time

    do
    {
        fcntl(fd, F_GETLK, &lock);  // system call to check if lock is there or not
        if (lock.l_type != F_UNLCK) // lock is present
        {
            printf("\nFile is locked! Unlock it first.");
            printf("\nPress y to try again to access it: ");
            scanf("%c", &choice); // user input for his choice
        }
        else // no lock is not present
        {
            read(fd, buffer, sizeof(buffer));               // read from file
            printf("\nData from data.txt: %s\n\n", buffer); // print the read message
            exit(0);                                        // exit successfully
        }

    } while (choice != 'y' || choice != 'Y');

    close(fd); // close the file
    return 0;
}