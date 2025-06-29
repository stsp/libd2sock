include asmdefs.inc

.text

extrn _csock_entry:FWORD

FUNC ____csock_getnblkio
    _ENTER

    mov edi, ARG1
    mov ecx, 0
    mov eax, 15
    call FAR PTR [_csock_entry]      ; // Call the entry point for SOCK.VXD
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    mov ebx, ARG2
    mov [ebx], edx
    xor eax, eax          ; // Clear EAX (set it to 0) on success
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_getnblkio
