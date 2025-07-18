include asmdefs.inc

.text

extrn _csock_entry:FWORD

FUNC ____csock_fionread
    _ENTER

    mov edi, ARG1
    mov eax, 17
    call FWORD PTR ds:[_csock_entry]      ; // Call the entry point for SOCK.VXD
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    mov ebx, ARG2
    mov [ebx], ecx
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_fionread
