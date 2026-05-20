#define MAXBUFF 80
#define PERM 0666

typedef struct custom_data
{
    int client_pid;
    char buff[MAXBUFF];
} CustomData;

typedef struct our_msgbuff
{
    long mtype;
    CustomData data;
} Message;

