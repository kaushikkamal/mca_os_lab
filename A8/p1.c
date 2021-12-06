#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

// unique keys for semaphores
#define SEM1_KEY (key_t)888
#define SEM2_KEY (key_t)1234

// a structure that holds the different semaphore id's
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

struct sembuf p = {0, -1, 0}; // wait() system call
struct sembuf v = {0, +1, 0}; // signal() system call

int main()
{
    // Declaring two semaphores one for wait() and other for signal()
    int semProd, semCon;

    semProd = semget(SEM1_KEY, 1, 0666 | IPC_CREAT); // creating/getting semaphore for prod
    if (semProd < 0)
    {
        perror("semget");
        exit(11);
    }

    semCon = semget(SEM2_KEY, 1, 0666 | IPC_CREAT); // creating/getting semaphore for con
    if (semCon < 0)
    {
        perror("semget");
        exit(11);
    }

    union semun u;

    u.val = 0;
    if (semctl(semProd, 0, SETVAL, u) < 0) // semaphore control operation
    {
        perror("semctl");
        exit(12);
    }

    u.val = 1;
    if (semctl(semCon, 0, SETVAL, u) < 0) // semaphore control operation
    {
        perror("semctl");
        exit(12);
    }

    char *file = "test.txt";
    int fd;
    char buff[255];
    int i;

    fd = open(file, O_RDONLY | O_CREAT, 0777); // opening file and creating if does not exist

    // iterating 5 times
    for (i = 0; i < 5; i++)
    {
        semop(semProd, &p, 1);

        read(fd, buff, 255);
        printf("Read data: %s\n", buff);

        semop(semCon, &v, 1);
    }

    close(fd);                    // closing file
    semctl(semProd, 0, IPC_RMID); // removing prod semaphore
    semctl(semCon, 0, IPC_RMID);  // removing con semaphore
    exit(0);
}