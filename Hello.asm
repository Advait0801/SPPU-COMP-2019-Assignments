section.data
M1 db "Hello" ,0xa, "World"
L1 equ $-M1

section.text
global _start
_start:
    mov rax, 01
    mov rdi, 01
    mov rsi, M1
    mov rdx, L1
    Syscall 
    
    mov rax, 60
    mov rdx, 0
    Syscall
    
;nasm -f elf64 Hello.asm
;ld -o Hello Hello.o
;./Hello

;Hello
;World
    
    
 
