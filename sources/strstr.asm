%include "minilibc.inc"

section .text

strstr:
    enter       0x00, 0x00
    cmp         rdi, 0x00
    je          ret_zero
    cmp         rsi, 0x00
    je          ret_zero
    mov         r9b, [rsi]
    xor         rcx, rcx
    jmp         loop

init_value:
    cmp         r9b, 0x00
    je          ret_zero
    inc         rdi
    mov         r9b, [rsi]
    xor         rcx, rcx
    jmp         loop

loop:
    mov         r9b, [rdi + rcx]
    mov         r8b, [rsi + rcx]
    cmp         r8b, 0x00
    je          ret_rdi
    cmp         r9b, r8b
    jne         init_value
    inc         rcx
    jmp         loop