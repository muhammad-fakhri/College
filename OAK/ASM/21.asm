extern scanf, printf, fflush
 
section .data
    fmti    db "%s %s", 0
    fmto    db "%d", 10, 0
    fmto2   db "tidak ada", 10, 0
 
section .bss
    input   resb 51
    char    resb 2
     
section .text
    global main
 
main:           
        ;scan(input, char)
        PUSH char
        PUSH input
        PUSH fmti
        CALL scanf
        ADD ESP, 12
         
        ;comparison
        MOV ECX, 50     ;set counter for
        MOV EDI, input  ;prepare the long string
        MOV AL, [char]  ;prepare the character
        REPNE SCASB
         
        ;calculate the position where the character first found
        MOV EAX, 50
        SUB EAX, ECX
         
        ;if not found
        CMP ECX, 0
        JE tidakada
         
        ;print EAX
        PUSH EAX
        PUSH fmto
        CALL printf
        ADD ESP, 8
        JMP exit
 
tidakada:       
        ;print "tidak ada"
        PUSH fmto2
        CALL printf
        ADD ESP, 4
 
exit:
        ;fflush
        PUSH 0
        CALL fflush
        MOV EAX, 1
        MOV EBX, 0
        INT 0x80