include asmdefs.inc

__data

PUBLIC _csock_entry
_csock_entry:
csock_entry_ip: DD 0
csock_entry_cs: DD 0

_DATA ENDS

.text

FUNC _VxdGetEntry
    _ENTER

    mov ebx, ARG1
    mov eax, 0x1684
    xor edi, edi
    push es
    mov es, edi
    int 02fh
    mov ebx, es
    pop es
    jc l1
    test ebx, ebx
    jz l1
    mov csock_entry_cs, ebx
    mov csock_entry_ip, edi
    xor eax, eax          ; // Clear EAX (set it to 0) on success
l2:
    _LEAVE
l1:
    mov eax, -1
    jmp l2
ENDFUNC _VxdGetEntry
