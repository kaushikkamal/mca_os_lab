#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *func(void *arg) //pointer to a subroutine that is executed by the thread
{
    printf("HELLO WORLD\n\n");
}
int main()
{
    pthread_t th;                           // declareing thread
    pthread_create(&th, NULL, &func, NULL); // creating a new thread
    pthread_join(th, NULL);                 // Waiting for the termination of the created thread
    pthread_exit(NULL);                     // terminate the thread

    return 0;
}