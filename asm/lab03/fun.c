#include <stdio.h>

void E_prnt(int n, int* A)
{
    for (int i=0; i<n; i++)
        printf("%d\t",*(A+i));
    printf("\n");
    return;
}
