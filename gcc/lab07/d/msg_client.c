#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include "msg.h"


int main(void)
{   
    Message message;
    key_t key;
    int msg_id, length;

    message.mtype = 1L;
    if ((key = ftok("./msg_server", 'A')) < 0)
    {
        printf("Error: Can't get key!\n");
        exit(1);
    }  
    if ((msg_id = msgget(key, 0)) < 0)
    {
        printf("Error: Can't get access to queue!\n");
        exit(1);
    }
    //if ((length = sprintf(message.buff,sizeof(message.buff),"Hello world!\n")) < 0)
    message.data.client_pid = getpid();
    if ((length = sprintf(message.data.buff, "Hello world from PID %d!\n", message.data.client_pid)) < 0)
    {
        printf("Error: of copy to buff!\n");
        exit(1);
    }

    //memcpy(message.buff,"Hello world!\n",14);
    if (msgsnd(msg_id, (void*)&message, sizeof(CustomData), 0) != 0)
    {
        printf("Error: Output error!\n");
        exit(1);
    }
    //sleep(10);
    /*if (msgctl(msg_id, IPC_RMID, 0) <0 )
    {
        printf("Error: Can't delete of queue!\n");
        exit(1);
    }*/
    return 0;
}
