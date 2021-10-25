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

    fcntl(fd, F_SETLK, &lock); // setting the lock
    
    printf("File locked successfully.");
    read(fd, buffer, sizeof(buffer));               // read from file
    printf("\nData from data.txt: %s\n", buffer); // print the read message
    
    do
    {
        printf("\nEnter y to unlock the file:  ");
        scanf("%c", &choice); // user input for his choice
        if (choice == 'Y' || choice == 'y')
        {
            lock.l_type = F_UNLCK; // set the lock type to unlock
            fcntl(fd, F_SETLK, &lock); // unlock the file
            printf("\nFile unlocked successfully.\n");
            exit(0);  // exit successfully
        }
    } while (choice != 'y' || choice != 'Y');

    close(fd); // close the file 
    return 0;
}