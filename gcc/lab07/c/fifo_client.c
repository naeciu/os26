#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO "fifo.2"

int main(void)
{
    int fd_write, n;
    if ((fd_write=open(FIFO, O_WRONLY))<0)
    {
        printf("Error: Cann't open FIFI!\n");
        exit(1);
    }    
    if (write(fd_write, "Hello world!\n", 14)!=14)
    {
        printf("Error: output error!\n");
        exit(1);
    }    
    close(fd_write);
    return 0;
}
