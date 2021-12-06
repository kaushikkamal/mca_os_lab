#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 255

// structure for message queue
struct mesg_buffer
{
    long mesg_type;
    char mesg_text[255];
} message;

int main()
{
    key_t key;
    int msgId;

    // ftok to generate unique key
    key = 1234;
    // key = ftok("msgfile", 11);

    // msgget creates a message queue
    // and returns identifier
    msgId = msgget(key, 0666 | IPC_CREAT);
    if (msgId < 0)
    {
        perror("msgget failed\n");
        exit(1);
    }
    message.mesg_type = 1;

    printf("Message id is: %d\n", msgId);
    printf("Write Data to be send: ");
    fgets(message.mesg_text, MAX, stdin);

    // msgsnd to send message
    if (msgsnd(msgId, &message, sizeof(message), 0) == -1)
    {
        perror("Message send failed\n");
        exit(1);
    }

    // display the message
    printf("Sent Data is: %s\n", message.mesg_text);

    exit(0);
}