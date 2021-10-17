%include "minilibc.inc"

section .text

memmove:
    enter       0x00, 0x00
    xor         rcx, rcx
    xor         r8, r8
    sub         rsp, rdx
    cmp         rdx, 0x00
    je          ret_rdi

.loop:
    mov         r8, qword [rsi + rcx]
    mov         BYTE [rsp + rcx], r8b
    inc         rcx
    cmp         rcx, rdx
    jne         .loop
    mov         rsi, rsp
    call        .memcpy
    jmp         end

.memcpy:
    xor         rcx,  rcx
    mov         rax, rdi

.memloop:
    cmp         rcx, rdx
    je          end
    mov         r8b, BYTE [rsi + rcx]
    mov         BYTE [rax + rcx], r8b
    inc         rcx
    jmp         .memloop