#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "sem_mem.h"

#define styleGREENi "\x1b[6;32;41m" 
#define styleEND   "\x1b[0m"
// Вместо printf("") используется fprintf(sdterr, "") для гарантии вывода на экран, в случае сбоя в работе.

//=============================================================================
void* create_kernel_objects(char* proc_name, int* sem_id, int* mem_id)
{   key_t key;
    Message *pMsg;
    if ((key = ftok(proc_name, 'A')) < 0)
    {   fprintf(stderr, "Error: Can't create  key!\n");
        exit(1);
    }
    else fprintf(stderr,"Create key.\n");
    if ((*mem_id = shmget(key, sizeof(Message), IPC_CREAT | PERM)) < 0)
    {   fprintf(stderr,"Error: Can't create region!\n");
        exit(1);
    }
    else fprintf(stderr,"Create region.\n");
    if ((pMsg = (Message*)shmat(*mem_id, 0, 0)) < 0)
    {   fprintf(stderr,"Error: Can't connect region!\n");
        exit(1);
    } 
    else fprintf(stderr,"Connect region.\n");
    if ((*sem_id = semget(key, 3, IPC_CREAT | PERM)) < 0)
    {   fprintf(stderr,"Error: Can't create semaphores!\n");
        exit(1);
    } 
    else fprintf(stderr,"Create three semaphores.\n");
    return (void*)pMsg;
}
//=============================================================================
int delete_kernel_objects(int* sem_id, int* mem_id, Message *pMsg)
{   if (shmdt(pMsg) < 0)
    {   fprintf(stderr,"Error: Can't disconnect!\n");
        exit(1);
    } 
    else fprintf(stderr,"Disconnect region.\n");
    if ((shmctl(*mem_id, 0, IPC_RMID)) < 0)
    {   fprintf(stderr,"Error: Operation delete region\n");
        exit(1);
    } 
    else fprintf(stderr,"Delete region.\n");
    if ((semctl(*sem_id, 0, IPC_RMID)) < 0)
    {   fprintf(stderr,"Error: Operation delete semaphores group!\n");
        exit(1);
    } 
    else fprintf(stderr,"Delete semaphores group.\n");
    return 0;
}
//=============================================================================
int read_mem(int sem_id, char* buf)
{   if ((semop(sem_id, &mem_lock[0], 2)) < 0)
    {   fprintf(stderr,"Error: Server can't locks memory!\n");
        exit(1);
    } 
    else fprintf(stderr,"Server locks memory.\n");
    ///////////////////////////////////////////
    printf("%s",buf);        
    ///////////////////////////////////////////
    if ((semop(sem_id, &mem_unlock[0], 1)) < 0)
    {   fprintf(stderr,"Error: Server can't unlocks memory!\n");
        exit(1);
    } 
    else fprintf(stderr,"Server unlock memory.\n");
    return 0;
}
//=============================================================================
int write2mem(int sem_id, char* buf, const char* str)
{   if ((semop(sem_id, &mem_lock[0], 2)) < 0)
    {   fprintf(stderr,"Error: Server can't locks memory!\n");
        exit(1);
    } 
    else fprintf(stderr,"Server locks memory.\n");
    ///////////////////////////////////////////
    sprintf(buf, str);
    ///////////////////////////////////////////
    if ((semop(sem_id, &mem_unlock[0], 1)) < 0)
    {   fprintf(stderr,"Error: Server can't unlocks memory!\n");
        exit(1);
    } 
    else fprintf(stderr,"Server unlock memory.\n");
    return 0;
}
//=============================================================================
int main(int argc, char *argv[])
{   int mem_id, sem_id;
    Message *pMsg = (Message*)create_kernel_objects(argv[0], &sem_id, &mem_id);
    stop_server(sem_id);
    read_mem(sem_id, pMsg->buf);
    char str[64];  
    sprintf(str,"\t%sHELLO, CLIENT!!!%s\n",styleGREENi,styleEND);
    write2mem(sem_id, pMsg->buf, str);
    start_client(sem_id);
    stop_server(sem_id);
    delete_kernel_objects(&sem_id, &mem_id, pMsg);
    return 0;         
}
//=============================================================================
