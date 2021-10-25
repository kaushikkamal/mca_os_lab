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

    shmID = shmget(key, 1024, 0666); //creates shared memory segment if not created, having size 3245 bytes with both read and write permission.

    memory_address = shmat(shmID, NULL, 0); // attach the memory to the process address space

    strcpy(buffer, memory_address); // data present in shared memory is copied to buffer

    printf("Data read from shared memory is : %s\n", buffer);

    shmdt(memory_address);          //  detached the shared memory
    shmctl(shmID, IPC_RMID, NULL); // removed the shared memory 

    return 0;
}