#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *func(void *arg)
{
    printf("HELLO WORLD\n\n");
    pthread_exit(NULL);
}
int main()
{
    pthread_t th;
    pthread_create(&th, NULL, &func, NULL);
    pthread_exit(NULL);
    return 0;
}