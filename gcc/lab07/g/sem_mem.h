#define MAXBUF 80
#define PERM 0666

#define SEM_MEMORY 0
#define SEM_SERVER 1
#define SEM_CLIENT 2
#define FLG_NULL 0


typedef struct mem_msg
{
    int segment;
    char buf[MAXBUF];
} Message;

static struct sembuf mem_lock[2] =
{
    SEM_MEMORY,  0, FLG_NULL,
    SEM_MEMORY,  1, FLG_NULL
};
static struct sembuf mem_unlock[1] =
{
    SEM_MEMORY, -1, FLG_NULL
};
static struct sembuf server_wait[1] =
{
    SEM_SERVER, -1, FLG_NULL
};
static struct sembuf server_start[1] =
{
    SEM_SERVER,  1, FLG_NULL
};
static struct sembuf client_wait[1] =
{
    SEM_CLIENT, -1, FLG_NULL
};
static struct sembuf client_start[1] =
{
    SEM_CLIENT,  1, FLG_NULL
};

//-----------------------------------------------------------------------------
int start_server(int sem_id)
{   if ((semop(sem_id, &server_start[0], 1)) < 0)
    {   fprintf(stderr,"Error: Operation (unlok pocess-server) can't be performed!\n");
        exit(1);
    } 
    else fprintf(stderr,"Client unlocks process-server.\n");
    return 0;
}
//-----------------------------------------------------------------------------
int start_client(int sem_id)
{   if ((semop(sem_id, &client_start[0], 1)) < 0)
    {   fprintf(stderr,"Error: Operation (unlok pocess-client) can't be performed!\n");
        exit(1);
    } 
    else fprintf(stderr,"Server unlocks process-client.\n");
    return 0;
}
//-----------------------------------------------------------------------------
int stop_server(int sem_id)
{   fprintf(stderr,"Waiting for client unlocks process-server.\n");
    if ((semop(sem_id, &server_wait[0], 1)) < 0)
    {   fprintf(stderr,"Error: Waiting for client unlocks process-server can't be performed!\n");
        exit(1);
    } 
    else fprintf(stderr,"Finished waiting for client unlocks process-server.\n");
    
}   
//-----------------------------------------------------------------------------
int stop_client(int sem_id)
{   fprintf(stderr,"Waiting for server unlocks process-client.\n");
    if ((semop(sem_id, &client_wait[0], 1)) < 0)
    {   fprintf(stderr,"Error: Waiting for server unlocks process-client can't be performed!\n");
        exit(1);
    } 
    else fprintf(stderr,"Finished waiting for server unlocks process-client.\n");
    
}   
//-----------------------------------------------------------------------------
