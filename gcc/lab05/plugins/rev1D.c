#include <stdio.h>
#include <string.h>

static char plugin_name[] = "Инверсия (реверс) массива";

void get_name(char* out)
{   
    strcpy(out, plugin_name);
}    

void fun_job(int n, int* A)
{
    printf("\nИсходный массив:\n");
    for (int i=0; i<n; i++) printf("%d\t", *(A+i));
    
    // Алгоритм переворота массива
    for (int i=0; i<n/2; i++) {
        int temp = *(A+i);
        *(A+i) = *(A+n-1-i);
        *(A+n-1-i) = temp;
    }
    
    printf("\nРазвернутый массив:\n");
    for (int i=0; i<n; i++) printf("%d\t", *(A+i));    
    printf("\n");
    return;
}
