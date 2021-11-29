#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *arg)
{
    printf("Thread");
}

int main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, &thread_func, NULL);
    pthread_join(thread,NULL);
    pthread_exit(NULL);
}