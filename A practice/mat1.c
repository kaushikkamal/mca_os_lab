#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    key_t key;
    int shmid;
    int *shared_memory;
    char buff[100];

    int mat1[3][3], mat2[3][3], res[3][3];
    int r, c;

    key = 1234;

    shmid = shmget(key, 2048, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        exit(1);
    }

    shared_memory = shmat(shmid, NULL, 0);

    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 3; c++)
        {
            scanf("%d", &mat1[r][c]);
            *shared_memory = mat1[r][c];
            shared_memory++;
        }
        printf("\n");
    }
    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 3; c++)
        {
            scanf("%d", &mat2[r][c]);
            *shared_memory = mat2[r][c];
            shared_memory++;
        }
        printf("\n");
    }

    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 3; c++)
        {
            res[r][c] = mat1[r][c] + mat2[r][c];
            *shared_memory = res[r][c];
            shared_memory++;
        }
        printf("\n");
    }
    printf("\nMat 1: \n");
    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 3; c++)
        {
            printf("%d ", mat1[r][c]);
        }
        printf("\n");
    }
    printf("\nMat 2: \n");
    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 3; c++)
        {
            printf("%d ", mat2[r][c]);
        }
        printf("\n");
    }
    printf("\nRES: \n");
    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 3; c++)
        {
            printf("%d ", res[r][c]);
        }
        printf("\n");
    }

    shmdt(shared_memory);

    return 0;
}