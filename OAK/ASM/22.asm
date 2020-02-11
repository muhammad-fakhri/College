extern scanf, printf, fflush
 
section .data
    fmti    db "%s", 0
    fmto    db "%d", 10, 0
    char    db "", 0
 
section .bss
    input   resb 21
     
section .text
    global main
 
main:           
        ;scan(input)
        PUSH input
        PUSH fmti
        CALL scanf
        ADD ESP, 8
         
        ;comparison
        MOV ECX, 20     ;set counter for
        MOV EDI, input  ;prepare the long string
        MOV AL, [char]  ;prepare the character
        REPNE SCASB
         
        ;calculate the position where the character first found
        MOV EAX, 20
        SUB EAX, ECX
        SUB EAX, 1
         
        ;print EAX
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