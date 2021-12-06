// C program to show thread functions

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *func(void *arg)
{
    // detach the current thread
    // from the calling thread
    pthread_detach(pthread_self());

    printf("Inside the thread\n");

    // exit the current thread
    pthread_exit(NULL);
}
// Driver code
int main()
{
    pthread_t ptid;

    pthread_create(&ptid, NULL, &func, NULL);
    printf("This line may be printed"
           " before thread terminates\n");

    // Compare the two threads created
    if(pthread_equal(ptid, pthread_self()))
    {
        printf("Threads are equal\n");
    }
	else{
        printf("Threads are not equal\n");
    }

	// Waiting for the created thread to terminate
	pthread_join(ptid, NULL);

	printf("This line will be printed"
		" after thread ends\n");

	pthread_exit(NULL);
    return 0;
}
