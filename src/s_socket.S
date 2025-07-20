include asmdefs.inc

.text

csock_ent

FUNC ____csock_open
    _ENTER

    mov ebx, ARG1
    mov eax, 1
    call_csock
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    mov ebx, ARG2
    wptr ebx, edi
    xor eax, eax          ; // Clear EAX (set it to 0) on success
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_open
