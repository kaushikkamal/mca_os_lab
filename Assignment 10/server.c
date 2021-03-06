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

    msgqid = msgget(key, 0666 | IPC_CREAT); // used to create the message queue
    if (msgqid == -1) // check for error
    {
        perror("msgget");
        exit(1);
    }
    printf("Msg Queue ID: %d",msgqid);

    printf("Enter text: ");
    buf.mtype = 1;  // set the msg type to 1

    while (fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) // read from user
    {
        int len = strlen(buf.mtext);

        if (buf.mtext[len - 1] == '\n')
        {
            buf.mtext[len - 1] = '\0';
        }

        if (msgsnd(msgqid, &buf, len + 1, 0) == -1)  // used to sent the data using queue 
        {
            perror("msgsnd");
        }
    }

    if (msgctl(msgqid, IPC_RMID, NULL) == -1) // used to remove the queue
    {
        perror("msgctl");
        exit(1);
    }
    return 0;
}