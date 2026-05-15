#include <stdio.h>
#include <string.h>

static char plugin_name[] = "Поиск минимального элемента";

void get_name(char* out)
{   
    strcpy(out, plugin_name);
}    

void fun_job(int n, int* A)
{
    printf("\nИсходный массив:\n");
    for (int i=0; i<n; i++) printf("%d\t", *(A+i));
    
    int min = *A;
    for (int i=1; i<n; i++) {
        if (*(A+i) < min) {
            min = *(A+i);
        }
    }
    
    printf("\nМинимальный элемент в массиве: %d\n", min);
    return;
}
