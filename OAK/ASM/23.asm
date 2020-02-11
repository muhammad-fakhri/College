extern printf, scanf, fflush
 
section .data
    fmti    db  "%f", 0
    fmto    db  "%f", 10, 0 
 
section .bss
    K   resq    1
    d   resd    1
 
section .text
global main
main:
    ;scanf(d)
    PUSH d
    PUSH fmti 
    CALL scanf
    ADD  ESP, 8
     
    ;hitung keliling
    FLDPI           ;load nilai pi
    FMUL dword [d]  ;kalikan pi dengan nilai d
    FSTP qword [K]  ;store hasil perkalian ke K
     
    ;printf(K)
    PUSH dword [K+4]
    PUSH dword [K]
    PUSH fmto
    CALL printf
    ADD  ESP, 12
     
    ;fflush
    PUSH 0
    CALL fflush
    MOV  EAX, 1
    MOV  EBX, 0
    INT  0x80