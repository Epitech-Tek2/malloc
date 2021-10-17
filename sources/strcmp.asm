%include "minilibc.inc"

section .text

strcmp:
    enter       0x00, 0x00
    xor         rcx, rcx
    cmp         rdi, 0x00
    je          end
    cmp         rsi, 0x00
    je          end

loop:
    mov         al, [rdi + rcx]
    mov         r8b, [rsi + rcx]
    cmp         al, 0x00
    je          fend
    cmp         r8b, 0x00
    je          fend
    cmp         al, r8b
    jne         fend
    inc         rcx
    jmp         loop

fend:
    sub         al, r8b
    movsx       rax, al
    cmp         rax, 0x00
    jg          ret_true
    cmp         rax, 0x00
    je          end
    jmp         ret_false

ret_true:
    mov         rax, 1
    jmp         end

ret_false:
    mov         rax, -1
    jmp         end