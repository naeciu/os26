#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define COUNT 5

typedef struct thread_args
{
    int iNumber;
    char cName[64];
} Thread_args;

pthread_mutex_t m_id[COUNT]; 

int iControl[]={3, 0, 4, 2, 1};




void* foo(void* args0)
{   
    Thread_args* args=(Thread_args*)args0;
    for (int i=0; i<3; i++)
    {   pthread_mutex_lock(&m_id[args->iNumber]);   
        printf("%s:\tN = %d\tPID = %d\tTID = %d\n",args->cName,args->iNumber,getpid(),gettid());
        pthread_mutex_unlock(&m_id[iControl[args->iNumber]]);   
    }    
    return NULL;
}

int main(void) 
{   
    pthread_t t_id[COUNT];
    Thread_args args[COUNT];
    for (int i=0; i<COUNT; i++)
    {   pthread_mutex_init(&m_id[i], NULL); 
        pthread_mutex_lock(&m_id[i]);   
        args[i].iNumber = i;
        sprintf(args[i].cName,"Thread %d",i+1);
        pthread_create(&t_id[i], NULL, foo, &args[i]);
    }
    sleep(.2);
    // Строка ниже коменируется
    pthread_mutex_unlock(&m_id[2]);   
    for (int i=0; i<COUNT; i++)
    {   pthread_mutex_destroy(&m_id[i]);  
        pthread_join(t_id[i], NULL);
    }    
    return 0;
}
