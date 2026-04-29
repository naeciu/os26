section .data
    n	equ	12 	                    ; кол элементов 
    A	dd	423,2,33,214,5,546,74,8,39,10,-87,15
    i	dd	0  	                    ; переменная внешнего цикла
    j	dd	0  	                    ; переменная внутреннего цикла
section .text
    global  _start
    extern	E_prnt
_start:
    ; Sorting started
    mov		ecx,	n 
    dec		ecx       	            ;  от 1 до n-1
    ;===================== 	        ; внешний цикл от 1 до n-1
L_for_i:
    push	ecx		                ; сохраняем кол. повторений, которые уменьшаются
    mov		ebx,	[i] 	        ; номер внешних повторения, который растет 
    mov		[j],	ebx  	        ; номер внутренних повторений, который растет
    inc		dword [j]   	        ; от i+1 до n
    mov		eax,	dword[A+4*ebx]  ; достанем из RAM элемент для ускорения работы
    ;---------------------  	    ; внутренний цикл от i+1 до n
L_for_j:
    push	ecx		                ; сохраняем кол. повторений
    mov		ebx,	[j]
    cmp		eax,	dword[A+4*ebx]	;сравниваем элем в RAM с тем, который достали
    jle		L_if_true
    xchg   	eax,	dword[A+4*ebx]	; меняем местами за 2 хода!!!
    mov		ebx,	[i]
    mov		[A+4*ebx],	eax
L_if_true:
    inc		dword	[j]
    pop		ecx
    loop	L_for_j
    ;----------------------
    inc		dword	[i]
    pop		ecx
    loop	L_for_i
    ;======================
;======================== 
L_exit:
    mov		eax,	1
    xor		ebx,	ebx
    int		80h
;========================================================================
