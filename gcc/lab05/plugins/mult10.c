#include <stdio.h>
#include <string.h>

static char plugin_name[] = "Умножение массива на 10";

void get_name(char* out)
{   
    strcpy(out,plugin_name);
}    


void fun_job(int n, int* A)
{
    printf("\n");
    for (int i=0; i<n; i++) printf("%d\t",*(A+i));
    for (int i=0; i<n; i++) *(A+i)*=10;
    printf("\n");
    for (int i=0; i<n; i++) printf("%d\t",*(A+i));    
    printf("\n");
    return;
}
