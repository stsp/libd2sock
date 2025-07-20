include asmdefs.inc

__data

PUBLIC _csock_entry
_csock_entry:
ifdef __USE32
csock_entry_ip: DD 0
csock_entry_cs: DD 0
else
csock_entry_ip: DW 0
csock_entry_cs: DW 0
endif

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
ifdef __USE32
    mov [csock_entry_cs], ebx
    mov [csock_entry_ip], edi
else
    mov [csock_entry_cs], bx
    mov [csock_entry_ip], di
endif
    xor eax, eax          ; // Clear EAX (set it to 0) on success
l2:
    _LEAVE
l1:
    mov eax, -1
    jmp l2
ENDFUNC _VxdGetEntry
