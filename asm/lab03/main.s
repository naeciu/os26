section .data
    var1 dd 7
section .text
    global _start
    extern mult10
_start:
    push dword [var1]
    call mult10
    add esp, 4           
    mov dword [var1], eax
L_exit:
    mov ebx, eax         ;
    mov eax, 1
    int 80h
