%include "minilibc.inc"

section .text

strcspn:
    xor         rbx, rbx
    enter       0x00, 0x00
    jmp         .process

.inc:
    inc         rbx

.process:
    mov         al, BYTE [rdi + rbx]
    cmp         al, 0
    je          .end
    xor         rcx, rcx
    jmp         .loop

.inc_sub:
    inc         rcx

.loop:
    mov         dl, BYTE [rsi + rcx]
    cmp         dl, 0
    je          .inc
    cmp         al, dl
    je          .end
    jmp         .inc_sub

.end:
    mov         rax, rbx
    jmp         end