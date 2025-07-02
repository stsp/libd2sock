include asmdefs.inc

.text

extrn _csock_entry:FWORD

FUNC ____csock_bind
    _ENTER

    mov  edi, ARG1
    mov  ebx, ARG2
    mov  edx, ARG3
    mov  eax,3
    call FWORD PTR ds:[_csock_entry]  ; Call the entry point for SOCK.VXD
    jc l1              ; Jump to label 1 if the carry flag is set (error)
    xor  eax,eax              ; Clear EAX (set it to 0) on success
l2:
    leave
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_bind
