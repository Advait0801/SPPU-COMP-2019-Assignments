%macro print 2
    mov rax, 01
    mov rdi, 01
    mov rsi, %1
    mov rdx, %2
    Syscall
%endmacro

%macro input 1
    mov rax, 0
    mov rdi, 0
    mov rdx, %1
    Syscall
%endmacro

section .data
M1 db "Enter a 2 digit number..."
L1 equ $-M1
M2 db "The 2 digit number is..."
L2 equ $-M2
M3 db 2
count1 db 2
count2 db 2

section .bss
num resb 10
ans resb 2

section .text
global _start
_start:
    print M1,L1
    
    mov rsi, num
    mov rcx, 02
    input M3      
    
    accept:
    mov rsi, num
    mov rbx, 0
    mov rax, 0
    
    back:                 ;ascii to hex conversion step 1
    rol rbx, 04
    mov al, [rsi]
    cmp al, 39h
    jbe next
    sub al, 07h
    
    next:                ;ascii to hex conversion step 2
    sub al, 30h
    add bx, ax
    inc rsi
    dec byte[count1]
    jnz back
    
    print M2,L2
    
    display:
    mov rbp, ans
    
    up:                    ;hex to ascii conversion step 1
    rol bl, 04
    mov dl, bl
    and dl, 0Fh
    cmp dl, 09h
    jbe ahead
    add dl, 07h
    
    ahead:                 ;hex to ascii conversion step 2
    add dl, 30h
    mov [rbp], dl
    inc rbp
    dec byte[count2]
    jnz up
    
    print ans, 2
    
    mov rax, 60
    mov rdx, 0
    Syscall
    

    
    
    
    
    


