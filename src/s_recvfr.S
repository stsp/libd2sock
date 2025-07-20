include asmdefs.inc

.text

csock_ent

FUNC ____csock_recvfrom
    _ENTER

    mov edi, ARG1
    mov esi, ARG2
    mov ecx, ARG3
    mov eax, 5
    call_csock
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    mov edi, ARG4
    wptr edi, ecx
    mov edi, ARG5
    wptr edi, ebx
    mov edi, ARG6
    wptr edi, edx
    xor eax, eax          ; // Clear EAX (set it to 0) on success
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_recvfrom
