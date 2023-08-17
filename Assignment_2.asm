%macro print 2
    mov rax, 01
    mov rdi, 01
    mov rsi, %1
    mov rdx, %2
    Syscall
%endmacro

%macro input 2
    mov rax, 0
    mov rdi, 0
    mov rsi, %1
    mov rdx, %2
    Syscall
%endmacro

section .data
M1 db "Enter a string..."
L1 equ $-M1
M2 db "The length of entered string is..."
L2 equ $-M2
count db 2

section .bss
string resb 80
len resb 2

section .text
global _start
_start:
    print M1,L1
    
    input string,80
    
    ;by default the length of string is stored in accumulator in hex form
    
    dec al
    mov bl, al
    mov rbp, len
    
    label1:                 ;hex to ascii conversion step 1
    rol bl, 04
    mov dl, bl
    and dl, 0Fh
    cmp dl, 09h
    jbe label2
    add dl, 07h
    
    label2:                 ;hex to ascii conversion step 2
    add dl, 30h
    mov [rbp], dl
    inc rbp
    dec byte[count]
    jnz label1
    
    print M2,L2
    print len,2
    
    mov rax, 60
    mov rdx, 0
    Syscall
    
;[mplab12@localhost 21354_Advait Naik]$ nasm -f elf64 Assignment_2.asm
;[mplab12@localhost 21354_Advait Naik]$ ld -o s Assignment_2.o
;[mplab12@localhost 21354_Advait Naik]$ ./s
;Enter a string...Hello World
;The length of entered string is...0B[mplab12@localhost 21354_Advait Naik]$ 

    
    
    
    
