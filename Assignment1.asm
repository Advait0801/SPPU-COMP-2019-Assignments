section .data
M1 db "Enter 5 64 bit numbers..."
L1 equ $-M1
M2 db "The entered numbers are....."
L2 equ $-M2
count1 db 05
count2 db 05

section .bss
num resb 100


section .text
global _start
_start:
    mov rax, 01
    mov rdi, 01
    mov rsi, M1
    mov rdx, L1
    Syscall
    
    xor rsi, rsi
    mov rsi, num                    ;input array   
    
    loop1:
        mov rax, 0
        mov rdi, 0    
        mov rdx, 17
        Syscall
        
        add rsi, 17
        dec byte[count1]
        jnz loop1
    
    mov rax, 01
    mov rdi, 01
    mov rsi, M2
    mov rdx, L2
    Syscall
    
    mov rsi, num              ;output array
    
    loop2:
        mov rax, 01
        mov rdi, 01        
        mov rdx, 17
        Syscall
        
        add rsi, 17
        dec byte[count2]
        jnz loop2
        
    mov rax, 60
    mov rdx, 0
    Syscall
    

;[mplab12@localhost 21354_Advait Naik]$ nasm -f elf64 Assignment1.asm
;[mplab12@localhost 21354_Advait Naik]$ ld -o s Assignment1.o
;[mplab12@localhost 21354_Advait Naik]$ ./s
;Enter 5 64 bit numbers...0000000000000000
;1010101010101010
;1100110011001100
;0011001100110011
;1111111111111111
;The entered numbers are.....0000000000000000
;1010101010101010
;1100110011001100
;0011001100110011
;1111111111111111
;[mplab12@localhost 21354_Advait Naik]$ 
     
        
        
        
        
    

