#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int stack_ptr()
{__asm__
    (   ".code32\n"
        ".intel_syntax noprefix\n"
        "mov    eax,    esp\n"
    );
}


int main(int argc, char *argv[])
{   
    unsigned long sp=(unsigned long)stack_ptr();
    void* brk0 = sbrk(0);
    unsigned long tmp = sp - (unsigned long)brk0;
    printf("\nHEAP брейк0-адрес\t\t\t%Xh\n", brk0);
    printf("Полный размер HEAP \t%lu байт = %lu Мб\n\n",tmp,tmp/1024/1024);

    
    if (argc>1)
    {
        int h_size = atoi(argv[1]);
        printf("Размер динамически выделенной области = %d единиц\n",h_size);

        double* ptr = malloc(tmp = h_size * sizeof(double));
        printf("Размер динамически выделенной области (массива) = %d или %Xh байт\n", tmp, tmp);
        printf("Адрес  динамически выделенной области\t%Xh\n\n",ptr);

        void* brk1 = sbrk(0);
        printf("HEAP брейк1-адрес\t\t\t%Xh\n", brk1);
        printf("HEAP брейк1-адрес - брейк0-адрес\t%d или %Xh байт\n\n\n", brk1-brk0, brk1-brk0);


        for (int i=0, j=12; i<10; i++, j+=5)
            *(ptr + i) = j + 0.43;

        for (int i=9; i>-1; i--)
            printf("ptr[%d] = %.3f\n", i, *(ptr + i));


        free(ptr);
        void* brk2 = sbrk(0);
        printf("\nHEAP брейк2-адрес\t\t\t%Xh\n", brk2);
        printf("HEAP брейк2-адрес - брейк1-адрес\t%d или %Xh байт\n", brk2-brk1, brk2-brk1);
        printf("HEAP брейк2-адрес - брейк0-адрес\t%d или %Xh байт\n\n\n", brk2-brk0, brk2-brk0);
        return 0;
    }
    return 1;
}



