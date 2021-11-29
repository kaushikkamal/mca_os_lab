#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // unique key to be used in shmget for accessing the shared memory segment created by program1
    key_t key = 0x1999;

    // using shmget to get the shared memory segment that returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory to the current process's address space in processId
    int *processId = shmat(shmid, NULL, 0);

    // check to see if the shm attachment is successfull
    if (processId == (void *)-1)
    {
        perror("Shared memory attachment failure");
        return -1;
    }

    printf("Reading process ID from shared memory: %d\n", *processId);

    //detaching the shared memory segment
    shmdt(processId);

    // destroying the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    exit(0);
}