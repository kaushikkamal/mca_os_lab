#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct
{
    long mtype;
    char mtext[200];
} MSGBUFFER;

int main()
{
    MSGBUFFER buf;
    int msgqid;
    key_t key;
    key = 1234;

    msgqid = msgget(key, 0666); /* connect to the queue */
    if (msgqid == -1)           // check for error
    {
        perror("msgget");
        exit(1);
    }
    printf("Msg Queue ID: %d\n\n", msgqid);
    while (1)
    {
        if (msgrcv(msgqid, &buf, sizeof(buf.mtext), 0, 0) == -1) // used to receive the data from queue
        {
            perror("msgrcv");
            exit(1);
        }
        printf("Message from Server: %s\n\n", buf.mtext);
    }
    return 0;
}
