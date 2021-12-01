#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int shmid;
    void *shared_memory;
    char buffer[100];

    shmid = shmget(1234, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmid");
    }

    shared_memory = shmat(shmid, NULL, 0);

    snprintf(buffer, sizeof(buffer), "%d", getpid());

    strcpy(shared_memory, buffer);

    printf("Copied");

    shmdt(shared_memory);
    return 0;
}