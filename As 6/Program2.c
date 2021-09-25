#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int choice;
    key_t key;
    int shmid;
    void *shared_memory;
    char buff[100];
    key = 1234;

    int i;
    shmid = shmget(key, 1024, 0666);
    
    printf("Key of shared memory is %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0); //process attached to shared memory segment
    printf("Process attached at %p\n", shared_memory);
    printf("Data read from shared memory is : %s\n", (char *)shared_memory);
    return 0;
}