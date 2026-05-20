#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define COUNT 7

sem_t sem;              
 
void* read_books(void* arg)
{
    char* reader = (char*) arg; 
    int count = 2;
    while (count > 0)
    {
        sem_wait(&sem);  
        printf("%s enters the library \n", reader);
        //printf("%s reads \n", reader);
        sleep(1);
        printf("%s            leaves the library \n", reader);
        sem_post(&sem);  
        count--;
        sleep(1);
    }
    return NULL;
}
 
int main(void) 
{   char thread_name[COUNT][32];
    pthread_t readers[COUNT];
    sem_init(&sem, 0, 3);       
    for (int i=0; i<COUNT; i++)
    {   memset(thread_name[i],0,32);
        sprintf(thread_name[i],"Reader %d",i+1);
        pthread_create(&readers[i], NULL, read_books, thread_name[i]);
    }    
    sem_destroy(&sem);   
    pthread_exit(NULL); 
    return 0;
}
