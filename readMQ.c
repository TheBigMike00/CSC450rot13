#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "rot13.h"
  
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
  
int main()
{
    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok("progfile", 65);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
  
    printf("What is the message type? ");
    long msgType;
    scanf("%ld", &msgType);
    //printf("%ld\n", msgType);
    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), msgType, 0);
  
    // display the message
    printf("Data Received is : %s \n", 
                    encodeRot13String(message.mesg_text));
  
    // to destroy the message queue
    //msgctl(msgid, IPC_RMID, NULL);
  
    return 0;
}