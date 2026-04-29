     1                                  section .data
     2                                      n	equ	12
     3 00000000 A70100000200000021-         A	dd	423,2,33,214,5,546,74,8,39,10,-87,15
     3 00000009 000000D60000000500-
     3 00000012 0000220200004A0000-
     3 0000001B 000800000027000000-
     3 00000024 0A000000A9FFFFFF0F-
     3 0000002D 000000             
     4 00000030 0A000000<rep Ch>            B   times   12 dd 10
     5                                  section .bss
     6 00000000 <res 30h>                   C resd 12 
     7                                  section .text
     8                                      global  _start
     9                                      extern	E_prnt
    10                                  _start:
    11 00000000 B90C000000                  mov ecx, n
    12 00000005 31DB                        xor ebx, ebx
    13                                  sum_loop:
    14 00000007 8B049D[00000000]            mov eax, [A + ebx*4]
    15 0000000E 03049D[30000000]            add eax, [B + ebx*4]
    16 00000015 89049D[00000000]            mov [C + ebx*4], eax
    17 0000001C 43                          inc ebx
    18 0000001D E2E8                        loop sum_loop
    19                                  
    20 0000001F 680C000000                  push dword n
    21 00000024 68[00000000]                push C
    22 00000029 E8(00000000)                call E_prnt
    23 0000002E 81C408000000                add esp, 8
    24                                  
    25 00000034 B801000000                  mov eax, 1
    26 00000039 31DB                        xor ebx, ebx
    27 0000003B CD80                        int 0x80
