#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <string.h>

#define SEM1_KEY (key_t)888
#define SEM2_KEY (key_t)1234

struct sembuf p = {0, -1, 0};
struct sembuf v = {0, +1, 0};

int main()
{
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

    char *file = "test.txt";
    int fd;
    int i;

    fd = open(file, O_RDWR | O_CREAT, 0777); // opening file and creating if does not exist

    for (i = 0; i < 5; i++)
    {
        semop(semCon, &p, 1);

        write(fd, "Data\n", strlen("Data\n"));
        printf("Write data: Data\n");
        getchar();

        semop(semProd, &v, 1);
    }

    close(fd); // closing file
    exit(0);
}