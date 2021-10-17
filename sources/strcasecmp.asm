%include "minilibc.inc"

section .text

strcasecmp:
    xor         eax, eax
    xor         rcx, rcx
    enter       0x00, 0x00
    jmp         .process

.increment:
    cmp         bl, 0
    je          end
    inc         rcx

.process:
    mov         bl, BYTE [rdi + rcx]
    mov         dl, BYTE [rsi + rcx]
    cmp         bl, 'A'
    jl          .upper
    cmp         bl, 'Z'
    jg          .upper
    add         bl, 32

.upper:
    cmp         dl, 'A'
    jl          .upper2
    cmp         dl, 'Z'
    jg          .upper2
    add         dl, 32

.upper2:
    cmp         bl, dl
    je          .increment

.diff:
    movsx       eax, bl
    movsx       ebx, dl
    sub         eax, ebx