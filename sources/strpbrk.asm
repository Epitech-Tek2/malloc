%include "minilibc.inc"

section .text

strpbrk:
    enter       0x00, 0x00
    xor         rcx, rcx
    cmp         rdi, 0x00
    je          ret_zero
    cmp         rsi, 0x00
    je          ret_zero

loop:
    xor         r10, r10
    cmp         BYTE [rdi + rcx], 0x00
    je          ret_zero
    cmp         BYTE [rsi + r10], 0x00
    je          ret_zero
    mov         r8b, BYTE [rdi + rcx]
    mov         r9b, BYTE [rsi + r10]
    cmp         r9b, 0x00
    je          ret_rdi
    cmp         r8b, 0x00
    je          ret_rdi

check_loop:
    cmp         BYTE [rsi + r10], 0x00
    je          .inc_rdi
    cmp         r8b, BYTE [rsi + r10]
    je          ret_rdi
    inc         r10
    jmp         check_loop

.inc_rdi:
    inc         rdi
    jmp         loop