#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "sem_mem.h"

#define styleBLUEi "\x1b[6;34;42m" 
#define styleEND   "\x1b[0m"

//=============================================================================
void* get_kernel_objects(int* sem_id, int* mem_id)
{   key_t key;
    Message *pMsg;
    if ((key = ftok("server", 'A')) < 0)
    {   fprintf(stderr,"Error: Can't get key!\n");
        exit(1);
    } 
    else fprintf(stderr,"Get key.\n");
    if ((*mem_id = shmget(key, sizeof(Message), 0)) < 0)
    {   fprintf(stderr,"Error: Can't get region!\n");
        exit(1);
    } 
    if ((pMsg = (Message*)shmat(*mem_id,0,0)) < 0)
    {   fprintf(stderr,"Error: Can't connect region!\n");
        exit(1);
    } 
    else fprintf(stderr,"Connect region.\n");
    if ((*sem_id = semget(key, 2, PERM)) < 0)
    {   fprintf(stderr,"Error: Can't get semaphore!\n");
        exit(1);
    } 
    else fprintf(stderr,"Get semaphore.\n");
    return (void*)pMsg;
}
//=============================================================================
int disconnect_mem(Message *pMsg)
{   if (shmdt(pMsg) <0)
    {   fprintf(stderr,"Error: Can't disconnect from memory!\n");
        exit(1);
    } 
    else fprintf(stderr,"Disconnect region.\n");
    return 0;
}
//=============================================================================
int read_mem(int sem_id, char* buf)
{   if ((semop(sem_id, &mem_lock[0], 2)) < 0)
    {   fprintf(stderr,"Error: Client can't locks memory!\n");
        exit(1);
    } 
    else fprintf(stderr,"Client locks memory.\n");
    ///////////////////////////////////////////
    printf("%s",buf);        
    ///////////////////////////////////////////
    if ((semop(sem_id, &mem_unlock[0], 1)) < 0)
    {   fprintf(stderr,"Error: Client can't unlocks memory!\n");
        exit(1);
    } 
    else fprintf(stderr,"Client unlock memory.\n");
    return 0;
}
//=============================================================================
int write2mem(int sem_id, char* buf, const char* str)
{   if ((semop(sem_id, &mem_lock[0], 2)) < 0)
    {   fprintf(stderr,"Error: Client can't locks memory!\n");
        exit(1);
    } 
    else fprintf(stderr,"Client locks memory.\n");
    ///////////////////////////////////////////
    sprintf(buf, str);
    ///////////////////////////////////////////
    if ((semop(sem_id, &mem_unlock[0], 1)) < 0)
    {   fprintf(stderr,"Error: Client can't unlocks memory!\n");
        exit(1);
    } 
    else fprintf(stderr,"Client unlock memory.\n");
    return 0;
}
//=============================================================================
int main(int argc, char *argv[])
{   int mem_id, sem_id;
    Message *pMsg = (Message*)get_kernel_objects(&sem_id, &mem_id);
    char str[64]; 
    sprintf(str,"\t%sHELLO, SERVER!!!%s\n",styleBLUEi,styleEND);
    write2mem(sem_id, pMsg->buf, str);
    start_server(sem_id);
    stop_client(sem_id);
    read_mem(sem_id, pMsg->buf);
    disconnect_mem(pMsg);
    start_server(sem_id);
    return 0;         
}
//=============================================================================
