#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE "MYFIFO"

int main()
{
    int choice;
    key_t key;
    int shmid;
    void *shared_memory;
    char buff[100];
    key = 1234;

    shmid = shmget(key, 1024, 0666 | IPC_CREAT); //creates shared memory segment with key 2345, having size 1024 bytes.

    if (shmid == -1)
    {
        exit(1);
    }
    shared_memory = shmat(shmid, NULL, 0);

    printf("Enter some data to write to shared memory\n");
    read(0, buff, 100);          //get some input from user
    strcpy(shared_memory, buff); //data written to shared memory

    // do
    // {
    //     printf("\n1: Read Data");
    //     printf("\n2: Write Data");
    //     printf("\n3: Exit");
    //     printf("\n\nEnter choice: ");
    //     scanf("%d", &choice);
    //     switch (choice)
    //     {
    //     case 1:
    //     {
    //         break;
    //     }
    //     case 2:
    //     {
    //         break;
    //     }
    //     case 3:
    //     {
    //         exit(0);
    //         break;
    //     }

    //     default:
    //     {
    //         printf("\nInvalid choice!\n\n");
    //         break;
    //     }
    //     }
    // } while (choice != 3);

    return 0;
}