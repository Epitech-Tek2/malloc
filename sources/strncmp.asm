%include "minilibc.inc"

section .text

strncmp:
    enter       0x00, 0x00
    jmp         .error

.error:
    xor         rcx, rcx
    cmp         rdx, 0x00
    je          ret_zero
    cmp         rdi, 0x00
    je          end
    cmp         rsi, 0x00
    je          end

loop:
    mov         al, [rdi + rcx]
    mov         r8b, [rsi + rcx]
    cmp         al, 0x00
    je          ret_r8b
    cmp         r8b, 0x00
    je          ret_r8b
    cmp         al, r8b
    jne         ret_r8b
    inc         rcx
    cmp         rcx, rdx
    je          ret_r8b
    jmp         loop

ret_r8b:
    sub         al, r8b
    movsx       rax, al
    jmp         end

ret_true:
    mov         rax, 1
    jmp         end

ret_false:
    mov         rax, -1
    jmp         end