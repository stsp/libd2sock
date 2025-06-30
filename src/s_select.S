include asmdefs.inc

.text

extrn _csock_entry:FWORD

FUNC ____csock_select
    _ENTER

    mov esi, ARG1
    mov ebx, [esi]
    mov esi, ARG2
    mov ecx, [esi]
    mov esi, ARG3
    mov edx, [esi]
    mov esi, ARG4
    mov edi, [esi]
    mov eax, 6
    call FAR PTR [_csock_entry]      ; // Call the entry point for SOCK.VXD
    jc l1                    ; // Jump to label 1 if the carry flag is set (error)
    mov esi, ARG1
    mov [esi], ebx
    mov esi, ARG2
    mov [esi], ecx
    mov esi, ARG3
    mov [esi], edx
    mov esi, ARG4
    mov [esi], edi
l2:
    _LEAVE
l1:
    neg eax
    jmp l2
ENDFUNC ____csock_select
