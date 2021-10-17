%include "minilibc.inc"

section .text

strchr:
    xor     rax, rax
    enter   0x00, 0x00

.loop:
    cmp     BYTE [rdi], sil
    je      ret_rdi
    cmp     BYTE [rdi], 0x00
    je      ret_zero
    inc     rdi
    jmp     .loop