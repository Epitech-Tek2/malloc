%include "minilibc.inc"

section     .text

memcpy:
    mov     rax, rdi
    xor     rcx, rcx
    enter   0x00, 0x00

.copy:
    cmp     rdx, rcx
    jle     .decrement_rdi
    mov     r10b, BYTE [rsi + rcx]
    mov     [rdi], r10b
    inc     rdi
    inc     rcx
    jmp     .copy

.decrement_rdi:
    cmp     rcx, 0x00
    je      ret_rdi
    dec     rdi
    dec     rcx
    jmp     .decrement_rdi