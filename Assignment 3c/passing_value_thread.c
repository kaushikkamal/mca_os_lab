#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *func(void *arg)
{
    int a = *((int *)arg);
    printf("HELLO WORLD\n");
    printf("arg: %d\n\n", a);
}
int main()
{
    pthread_t th;

    int num = 5;
    int *j = &num;

    pthread_create(&th, NULL, &func, (void *)j);

    pthread_join(th, NULL);

    pthread_exit(NULL);

    return 0;
}
