#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    int shmid;
    void *shared_memory;
    char buffer[100];

    shmid = shmget(1234, 1024, 0666);
    if (shmid == -1)
    {
        perror("shmid");
    }

    shared_memory = shmat(shmid, NULL, 0);

    strcpy(buffer, shared_memory);
    printf("Data: %s", buffer);

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}