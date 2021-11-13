#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    key_t key;
    int shmid;
    void *shared_memory;
    char buff[100];

    key = 1234; // unique key for the shared memory

    shmid = shmget(key, 1024, 0666 | IPC_CREAT); //creates shared memory segment with key 1234, having size 1024 bytes with both read and write permission.
    if (shmid == -1)                             // check if shared memory segment is created or not
    {
        exit(1);
    }

    shared_memory = shmat(shmid, NULL, 0); // attach the memory to the process address space

    snprintf(buff, sizeof(buff), "%d", getpid()); // stores a series of characters and values in the array buffer

    strcpy(shared_memory, buff); //data present in buff is copied to shared memory

    printf("Process id is copied to the shared memory.\n");

    shmdt(shared_memory); //  detached the shared memory segment

    return 0;
}