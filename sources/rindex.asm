%include "minilibc.inc"

section     .text

rindex:
    xor     rax, rax
    enter   0x00, 0x00

.strlen:
    cmp     BYTE [rdi], 0x00
    je      .loop
    inc     rdi
    jmp     .strlen

.loop:
    cmp     sil, 0x00
    je      ret_rdi
    dec     rdi
    cmp     BYTE [rdi], sil
    je      ret_rdi
    cmp     BYTE [rdi], 0x00
    je      ret_zero
    jmp     .loop