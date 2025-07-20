include asmdefs.inc

.text

csock_ent

FUNC ____csock_getsockname
    _ENTER

    mov edi, ARG1
    mov eax, 13
    call_csock
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    mov edi, ARG2
    mov [edi], ecx
    mov edi, ARG3
    mov [edi], ebx
    xor eax, eax          ; // Clear EAX (set it to 0) on success
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_getsockname
