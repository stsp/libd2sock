include asmdefs.inc

.text

csock_ent

FUNC ____csock_getsoerr
    _ENTER

    mov edi, ARG1
    mov eax, 18
    call_csock
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    mov ebx, ARG2
    wptr ebx, edx
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_getsoerr
