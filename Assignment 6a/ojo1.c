#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    key_t key;
    char buffer[50];
    int shmID;
    void *memory_address;

    key = 3245; // unique key for the shared memory

    shmID = shmget(key, 1024, 0666 | IPC_CREAT); //creates shared memory segment with key 3245, having size 1024 bytes with both read and write permission.
    if (shmID == -1)                             // check if shared memory segment is created or not
    {
        exit(1);
    }

    memory_address = shmat(shmID, NULL, 0); // attach the memory to the process address space

    snprintf(buffer, sizeof(buffer), "%d", getpid()); // stores a series of characters and values in the buffer

    strcpy(memory_address, buffer); //data present in buffer is copied to shared memory

    printf("Data is copied to the shared memory.\n");

    shmdt(memory_address); //  detached the shared memory

    return 0;
}