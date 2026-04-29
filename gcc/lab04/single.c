#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "../lib/m_time.h"

int main(void)
{  
    printf("Hello World!\n");
    fnGetDateTime(NULL, 0, 1, 1);
    double t0=fnGetProcTime(1,1);
    for (long i=0, j=0; i<100000000; i++) j=i;
    fnGetDateTime(NULL, 0, 1, 1);
    double t1=fnGetProcTime(1,1);
    printf("%f\n",t1-t0);
    for (int i=0; i<10000; i++)
    {
        FILE* fd=fopen("./data.txt","w");
        if (fd)
        {
            for (int j=0; j<1000; j ++)
            {   char c[64];
                fputs(c,fd);            
            }
            fclose(fd);
        }
    }
    fnGetDateTime(NULL, 0, 1, 1);
    t1=fnGetProcTime(1,1);
    printf("%f\n",t1-t0);
    return 0;
}
