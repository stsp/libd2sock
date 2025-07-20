include asmdefs.inc

.text
csock_ent

FUNC ____csock_select
    _ENTER

    mov esi, ARG1
    rptr ebx, esi
    mov esi, ARG2
    rptr ecx, esi
    mov esi, ARG3
    rptr edx, esi
    mov esi, ARG4
    rptr edi, esi
    mov eax, 6
    call_csock
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    mov esi, ARG1
    wptr esi, ebx
    mov esi, ARG2
    wptr esi, ecx
    mov esi, ARG3
    wptr esi, edx
    mov esi, ARG4
    wptr esi, edi
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_select
