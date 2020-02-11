extern printf, scanf, fflush
 
section .data
    fmti    db  "%lf %lf", 0
    fmto    db  "%f", 10, 0 
 
section .bss
    J   resq    1
    a   resq    1
    b   resq    1
    c   resq    1
 
section .text
global main
main:
    ;scanf(a, b)
    PUSH b
    PUSH a
    PUSH fmti 
    CALL scanf
    ADD  ESP, 12
     
    ;hitung jarak euclid
    FINIT               ;kosongkan FPU
    FLD  qword [a]      ;ST0 = a
    FMUL qword [a]      ;ST0 *= a
    FST  qword [c]      ;c = ST0 -> a^2, ST0 = NULL
    FLD  qword [b]      ;ST0 = b
    FMUL qword [b]      ;ST0 *= b
    FADD qword [c]      ;ST0 += c   
    FSQRT               ;sqrt(ST0)
    FSTP qword [J]      ;store hasil perhitungan ke J
     
    ;printf(J)
    PUSH dword [J+4]
    PUSH dword [J]
    PUSH fmto
    CALL printf
    ADD  ESP, 12
     
    ;fflush
    PUSH 0
    CALL fflush
    MOV  EAX, 1
    MOV  EBX, 0
    INT  0x80