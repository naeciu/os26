#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include "msg.h"
#include <errno.h>
#include <string.h>

//#include <string.h>

int main(int argc, char *argv[])
{   
    Message message;
    key_t key;
    int msg_id, length, n;

    message.mtype = 1L;
    if ((key = ftok(argv[0], 'A')) < 0)
    {
        printf("Error: Can't get key!\n");
        exit(1);
    }
    if ((msg_id = msgget(key, IPC_CREAT | PERM)) < 0)
    {
        printf("Error: Can't create queue!\n");
        exit(1);
    }
    n = msgrcv(msg_id, &message, sizeof(CustomData), message.mtype, 0);
    int er_num=errno;     
    //size_t er_len=strerrorlen_s(errno)+1;
    char er_buf[256];
    memset(er_buf,256,0);
    strerror_r(er_num,er_buf,256);
    //char* er_str=strerror(errno);
        if (n>0)
    {
        printf("Получено от PID %d: %s", message.data.client_pid, message.data.buff);
    }
    else
    {
        printf("Error: Input error (%s)!\n",er_buf);
        exit(1);
    }
    if (msgctl(msg_id, IPC_RMID, 0) < 0)
    {
        printf("Error: Can't delete of queue!\n");
        exit(1);
    }
    return 0;
}
