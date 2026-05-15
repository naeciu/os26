#include <stdio.h>
#include <string.h>

static char plugin_name[] = "Сортировка массива";

void get_name(char* out)
{   
    strcpy(out,plugin_name);
}    


void fun_job(int n, int* A)
{   int b;
    printf("\n");
    for (int i=0; i<n; i++) printf("%d\t",*(A+i));
    for (int i=0; i<n-1; i++)
        for (int j=i+1; j<n; j++)
            if (*(A+i)>*(A+j))
            {   b = *(A+i);
                *(A+i)=*(A+j);
                *(A+j)=b;
            }    
    printf("\n");
    for (int i=0; i<n; i++) printf("%d\t",*(A+i));    
    printf("\n");
    return;
}
