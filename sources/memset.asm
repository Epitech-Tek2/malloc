%include "minilibc.inc"

section .text

memset:
    xor     rcx, rcx
    mov     rax, rdi
    enter   0x00, 0x00

.loop:
    cmp     rcx, rdx
    je      end
    mov     BYTE [rax + rcx], sil
    inc     rcx
    jmp     .loop