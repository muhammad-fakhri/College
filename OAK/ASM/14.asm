global main
extern scanf, printf, fflush
 
segment .data
    matriks dd 7, 11, 10, 6
          dd 5, 8, 9, 12
          dd 11, 13, 12, 15
    fmti db '%d',0
    fmto1 db '%d ',0
    fmto2 db '%d',10,0
     
segment .bss
    n resd 4
 
segment .text
 
main:
    PUSH n
    PUSH fmti
    CALL scanf
    ADD ESP,8
 
    MOV EDI,0
 
hitung:
    MOV EAX,[matriks+EDI]
    mul dword[n]
     
    ;kalo udh diujung
    CMP EDI,12
    JE newline
    CMP EDI,28
    JE newline
    CMP EDI,44
    JE newline
    JA exit
 
    PUSH EAX
    PUSH fmto1
    CALL printf
    ADD ESP,8
 
    PUSH 0
    CALL fflush
    ADD ESP,4
 
    ADD EDI,4
    JMP hitung
     
newline:
    PUSH EAX
    PUSH fmto2
    CALL printf
    ADD ESP,8
 
    PUSH 0
    CALL fflush
    ADD ESP,4
     
    ADD EDI,4
    JMP hitung
     
exit:
    MOV EAX,1
    MOV EBX,0
    int 80H