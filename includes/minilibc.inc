bits        64

global      strcasecmp:function
global      strpbrk:function
global      strcspn:function
global      strncmp:function
global      strlen:function
global      strcmp:function
global      strstr:function
global      strchr:function
global      rindex:function
global      memcpy:function
global      memset:function
global      memmove:function

ret_rdi:
    mov     rax, rdi
    jmp     end

ret_zero:
    xor     rax, rax
    jmp     end

inc_sub:
    inc rcx

incrementation_rbx:
    inc rbx

end:
    leave
    ret