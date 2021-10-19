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

    shmid = shmget(key, 1024, 0666); //creates shared memory segment if not created, having size 1024 bytes with both read and write permission.
    // Since IPC_CREATE flag is not used then shmget() will find the segment associated with key and check to see if the user has permission to access the segment.

    shared_memory = shmat(shmid, NULL, 0); // attach the memory to the process address space

    strcpy(buff, shared_memory); // data present in shared memory is copied to buff

    printf("Data read from shared memory is : %s\n", buff);

    shmdt(shared_memory);          //  detached the shared memory segment
    shmctl(shmid, IPC_RMID, NULL); // removed the shared memory segment

    return 0;
}