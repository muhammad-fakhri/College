global main
extern scanf, printf, fflush
  
segment .data
    fmti db '%d',0
    fmto db '%d',10, 0
      
segment .bss
    a resd 4
  
segment .text
;pangkat (int a) {
;   eax = 2
;   while(a){
;       eax *= 2 
;   }
;   return eax
;}
 
pangkat:
        push    ebp                     ; save old ebp
        mov     ebp, esp                ; this new ebp (as reference to parameter and local variable)
        sub     esp, 4                  ; allocate 1 local variables
      
        mov     ecx, dword [ebp+8]      ;counter = a
        sub     ecx, 1
        mov     eax, 2                  ;eax = 2
        mov     dword [ebp-4], 2       ; d = 15
         
        looping:
        mul     dword [ebp-4]                       ;eax *= 2
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
     
    ;ganda function call
    push dword [a]
    call pangkat
    add esp, 4
     
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