global main
extern scanf, printf, fflush
  
segment .data
    fmti db '%d',0
    fmto db '%d',10, 0
      
segment .bss
    a resd 4
    b resd 4
  
segment .text
;pangkat (int a, int b) {
;   eax = a
;   while(b){
;       eax *= a 
;   }
;   return eax
;}
 
pangkat:
        push    ebp                     ; save old ebp
        mov     ebp, esp                ; this new ebp (as reference to parameter and local variable)
      
        mov     eax, dword [ebp+8]      ;eax = a
        mov     ecx, dword [ebp+12]     ;counter = b
        sub ecx, 1                  ;counter -= 1
        mov     ebx, dword [ebp+8]      ;ebx = a
         
        looping:
        mul     ebx                     ;eax *= a
        LOOP looping
         
        mov     esp, ebp                ; deallocate local variables
        pop     ebp                     ; restore old ebp
        ret
 
main:
ulang:
    ;scanf(a)
    push a
    push fmti
    call scanf
    add esp, 8
     
    ;exit condition if input = 0
    CMP dword [a], 0
    JE exit
     
    ;scanf(b)
    push b
    push fmti
    call scanf
    add esp, 8
     
    ;pangkat function call
    push dword [b]
    push dword [a]
    call pangkat
    add esp, 8
     
    ;print
    push eax
    push fmto
    call printf
    add esp, 8
     
    ;fflush
    push 0
    call fflush
    add esp, 4
     
    ;looping as long as input still not equal 0
    JMP ulang
 
exit:
    ;exit
    MOV EAX,1
    MOV EBX,0
    int 80H