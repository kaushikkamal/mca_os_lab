#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char *file = "test.txt";
    int fd;
    struct flock lk;

    printf("Opening - %s\n", file);

    /* Opening a file descriptor to the file. */
    fd = open(file, O_WRONLY | O_CREAT, 0777);

    printf("Trying to accquire write lock.\n");

    /* Initializing the l_type of flock structure. */
    memset(&lk, 0, sizeof(lk));
    lk.l_type = F_WRLCK;

    /* Setting a write lock on the file with F_SETLKW that blocks the process 
    in case there is an exisiting lock
    and waits for the lock to be released so to set the new lock. */
    fcntl(fd, F_SETLKW, &lk);

    printf("Lock accquired.\n");
    printf("Press a key to unlock.\n");

    /* Waiting for a char from the keyboard. */
    getchar();

    printf("Unlocking.\n");

    /* Releasing the lock. */
    lk.l_type = F_UNLCK;

    /* Using F_SETLK to release the lock */
    if (fcntl(fd, F_SETLK, &lk) != -1)
    {
        printf("Unlocked.\n");
    }

    close(fd);
    return 0;
}
