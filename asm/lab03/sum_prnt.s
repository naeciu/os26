section .data
    n	dd	12
    A	dd	423,2,33,214,5,546,74,8,39,10,-87,15
    B   times   12 dd 10
section .bss
    C resd 12 
section .text
    global  _start
    extern	E_prnt
_start:
    mov ecx, [n]
    xor ebx, ebx
sum_loop:
    mov eax, [A + ebx*4]
    add eax, [B + ebx*4]
    mov [C + ebx*4], eax
    inc ebx
    loop sum_loop

    push dword [n]
    push C
    call E_prnt
    add esp, 8

    mov eax, 1
    xor ebx, ebx
    int 0x80
