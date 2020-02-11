
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
extern scanf, printf, fflush
 
section .data
    fmti    db "%s", 0
    fmto1   db "weekday", 10, 0
    fmto2   db "weekend", 10, 0
    sun     db "Sun", 0
    sat     db "Sat", 0
 
section .bss
    input   resb 10
     
section .text
    global main
 
main:
        ;scanf(input)
        PUSH input
        PUSH fmti
        CALL scanf
        ADD ESP, 8
 
        ;prepare input for comparison
        MOV ESI, input
         
        ;compare string with sun
        MOV EDI, sun
        CMPSB
        JE iya  ;if same
         
        ;compare string with sat
        MOV EDI, sat
        CMPSB
        JE iya  ;if same
         
        ;if not same with sun and sat
        ;print "weekday"
        PUSH fmto1
        CALL printf
        ADD ESP, 4
        JMP exit
 
iya:
        ;if same with sun or sat
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