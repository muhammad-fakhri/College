extern printf, scanf, fflush
   
section .data
    fmti db "%d %d", 0
    fmto db "%d", 10, 0
    matriks dd  7, 11, 10, 6
            dd  5, 8, 9, 2
            dd  1, 3, 12, 4
    n dd 4
section .bss
    row resd 1
    col resd 1
       
section .text
global main
main:
    ; scanf(fmti, row, col)
    PUSH col
    PUSH row
    PUSH fmti
    CALL scanf
    ADD ESP, 12
 
    ;hitung index
    MOV ESI, [row]
    MOV EAX, ESI
    MUL dword [n]
    MOV ESI, EAX
    ADD ESI, [col]
    MOV EAX, [matriks + ESI * 4] 
  
    ;print
    PUSH EAX
    PUSH fmto
    CALL printf
    ADD ESP, 8
    ;fflush
    PUSH 0
    CALL fflush
    ADD ESP, 4
    ;exit
    MOV EAX, 1
    MOV EBX, 0
    int 80h