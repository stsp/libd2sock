include asmdefs.inc

.text

csock_ent

FUNC ____csock_setnblkio
    _ENTER

    mov edi, ARG1
    mov ecx, 1
    mov edx, ARG2
    mov eax, 15
    call_csock
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    xor eax, eax          ; // Clear EAX (set it to 0) on success
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_setnblkio
