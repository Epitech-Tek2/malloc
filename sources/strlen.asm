%include "minilibc.inc"

section .text

strlen:
    xor     rax, rax
    enter   0x00, 0x00

.loop:
    cmp     BYTE [rdi + rax], 0x00
    je      end
    inc     rax
    jmp     .loop