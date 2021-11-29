#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct my_msgbuf
{
    long mtype;
    char mtext[200];
};
int main()
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;
    key = 1122;

    msqid = msgget(key, 0666); /* connect to the queue */
    if (msqid == -1)
    {
        perror("msgget");
        exit(1);
    }

    while (1)
    {
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) // used to receive the data 
        {
            perror("msgrcv");
            exit(1);
        }
        printf("Message received from Server: %s\n\n", buf.mtext);
    }
    return 0;
}
