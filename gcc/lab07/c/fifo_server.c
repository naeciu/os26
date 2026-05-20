#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO "fifo.2"
#define MAXBUF 80

int main(void)
{
    int fd_read, n;
    char buff[MAXBUF];
    char* s_exit=".exit";
    if (mknod(FIFO, S_IFIFO | 0666, 0)<0)
    {
        printf("Error: Cann't create FIFI!\n");
        exit(1);
    }    
    if ((fd_read=open(FIFO, O_RDONLY))<0)
    {
        printf("Error: Cann't read FIFI!\n");
        exit(1);
    }    
    while(memcmp(buff,s_exit,5)!=0)
        while((n=read(fd_read, buff, MAXBUF))>0)
            if (write(1, buff, n)!=n)
            {
                printf("Error: input error!\n");
                exit(1);
            }    
    close(fd_read);
    if (unlink(FIFO)<0)
    {
        printf("Error: Cann't delite FiFO!!\n");
        exit(1);
    }    
    return 0;
}
