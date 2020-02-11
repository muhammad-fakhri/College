extern scanf, printf, fflush
 
section .data
    fmti    db "%d %d", 0
    fmto    db "%d", 10, 0
 
section .bss
    a resd  4
    b resd  4
     
section .text
    global main
 
;tambah(a, b) {
;   return a + b
;}
 
tambah:
        push    ebp                     ; save old ebp
        mov     ebp, esp                ; this new ebp (as reference to parameter and local variable)
  
        mov     eax, dword [ebp+8]      ;eax = a
        ADD     eax, dword [ebp+12]     ;eax =+ b
    
        mov     esp, ebp                ; deallocate local variables
        pop     ebp                     ; restore old ebp
        ret
 
main:           
        ;scanf(a, b)
        PUSH b
        PUSH a
        PUSH fmti
        CALL scanf
        ADD ESP, 12
 
        ;ganda(a, b)
        PUSH dword [a]
        PUSH dword [b]
        CALL tambah
        ADD ESP, 8
         
        ;print(EAX)
        PUSH EAX
        PUSH fmto
        CALL printf
        ADD ESP, 8
         
        ;fflush
        PUSH 0
        CALL fflush
        MOV EAX, 1
        MOV EBX, 0
        INT 0x80