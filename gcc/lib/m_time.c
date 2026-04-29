#include <memory.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>


void fnGetDateTime(char* buf, int len_buf, int time_print, int date_print)
{
    clock_t s_time;
    time(&s_time);
    struct tm *tm_time=localtime(&s_time);
    if (time_print)
        printf("Time: %02d:%02d:%02d\n",tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);
    if (date_print)
        printf("Date: %4d.%02d.%02d\n",tm_time->tm_year+1900, tm_time->tm_mon+1, tm_time->tm_mday);
    memset(buf,sizeof(char)*len_buf,0);
    if (len_buf>20)
        sprintf(buf,"[%4d.%02d.%02d  %02d:%02d:%02d]",
            tm_time->tm_year+1900,tm_time->tm_mon+1,tm_time->tm_mday,
            tm_time->tm_hour,tm_time->tm_min,tm_time->tm_sec);
}


double fnGetProcTime(int iPrintSec, int iPrint)
{
    struct tms cpu;
    double dCLOCKS_PER_SEC=sysconf(_SC_CLK_TCK);
    clock_t clocks = times(&cpu);
    double sec=(double)clocks/dCLOCKS_PER_SEC;
    if (iPrintSec)
        printf("Sec:    %f\n",sec);
    if (iPrint)
    {    
        printf("UTime:  %f\tSTime: %f\n",((double)cpu.tms_utime)/ dCLOCKS_PER_SEC,(double)cpu.tms_stime/ dCLOCKS_PER_SEC);
        printf("CUTime: %f\tCSime: %f\n",((double)cpu.tms_cutime)/dCLOCKS_PER_SEC,(double)cpu.tms_cstime/dCLOCKS_PER_SEC);
    }
    return sec;
}
