#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg)
{
    printf("HELLO WORLD\n");
}
int main()
{
    pthread_t thread; // declareing thread

    pthread_create(&thread, NULL, &thread_function, NULL); // creating thread

    pthread_join(thread, NULL); // Waiting for the termination of the created thread

    pthread_exit(NULL); // terminate the thread

    return 0;
}