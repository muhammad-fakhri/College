; Rataan Suhu
; =====================
 
global main
extern scanf
extern printf
 
section .data
    fmt_in      db      "%d", 0
    fmt_scan    db      "%lf", 0
    fmt_out     db      "%.1lf", 10, 0
 
section .bss
    n           resd    1
    suhu        resd    1
    rataan      resd    1
    total       resd    1
 
section .text
    main:
                ; scanf n (limitation)
                push    n
                push    fmt_in
                call    scanf                   ; %f --> float
                add     esp, 8
                 
                mov     esi, dword[n]               ; esi = n
                fld     qword[total]
    input:
                ; scanf Suhu
                push    suhu
                push    fmt_scan
                call    scanf
                add     esp, 8
                 
                fadd    qword[suhu]
                 
                sub     esi, 1
                cmp     esi, 0
                ja      input
                 
                fidiv   dword[n]
                fst     qword[rataan]
                 
             
                ; printf
                push    dword[rataan+4]
                push    dword[rataan]
                push    fmt_out
                call    printf                  ; %f --> double
                add     esp, 12
 
 
                EXIT :
                mov eax, 0                      ;exit (0)
                ret