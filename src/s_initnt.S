include asmdefs.inc

.text

csock_ent

FUNC ____csock_get_version
    _ENTER

    mov edi, ARG2
    mov esi, ARG3
    mov eax, 0            ; // Set EAX to 0 for the version call
    call_csock
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    mov ebx, ARG1
    wptr4 ebx, eax, edx, dx
    xor eax, eax          ; // Clear EAX (set it to 0) on success
l2:
    _LEAVE
l1:
    mov eax, -1
    jmp l2
ENDFUNC ____csock_get_version
