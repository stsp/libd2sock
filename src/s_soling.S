include asmdefs.inc

.text

csock_ent

FUNC ____csock_setsolinger
    _ENTER

    mov edi, ARG1
    mov ecx, ARG2
    mov edx, ARG3
    mov eax, 19
    call_csock
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_setsolinger
