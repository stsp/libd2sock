include asmdefs.inc

.text

csock_ent

FUNC ____csock_connect
    _ENTER

    mov edi, ARG1
    mov ebx, ARG2
    mov edx, ARG3
    mov eax, 7
    call_csock
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    xor eax, eax          ; // Clear EAX (set it to 0) on success
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_connect
