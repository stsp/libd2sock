FUNC macro nm
PUBLIC nm
nm PROC NEAR
endm

ARG1 macro
[ebp+8]
endm

ARG2 macro
[ebp+12]
endm

ARG3 macro
[ebp+16]
endm

ARG4 macro
[ebp+20]
endm

ARG5 macro
[ebp+24]
endm

ARG6 macro
[ebp+28]
endm

_ENTER macro
push ebp
mov ebp, esp
endm

_LEAVE macro
pop ebp
ifdef __USE32
ret
else
retf
endif
endm

.text macro
ifdef __USE32
_TEXT SEGMENT BYTE PUBLIC USE32 'CODE'
else
_TEXT SEGMENT BYTE PUBLIC USE16 'CODE'
endif
endm

__data macro
ifdef __USE32
_DATA SEGMENT BYTE PUBLIC USE32 'DATA'
else
_DATA SEGMENT BYTE PUBLIC USE16 'FAR_DATA'
endif
endm

ENDFUNC macro nm
nm ENDP
_TEXT ENDS
END
endm

csock_ent macro
ifdef __USE32
extrn _csock_entry:FWORD
else
extrn _csock_entry:DWORD
endif
endm

call_csock macro
ifdef __USE32
call FWORD PTR ds:[_csock_entry]
else
call DWORD PTR ds:[_csock_entry]
endif
endm

wptr4 macro d, s, t, wt
ifdef __USE32
mov [d], s
else
push es
push t
mov t, d
shr t, 16
mov es, wt
and d, 0ffffh
mov es:[d], s
pop t
pop es
endif
endm

wptr macro d, s
wptr4 d, s, eax, ax
endm

rptr4 macro d, s, t, wt
ifdef __USE32
mov d, [s]
else
push es
push t
mov t, s
shr t, 16
mov es, wt
and s, 0ffffh
mov d, es:[s]
pop t
pop es
endif
endm

rptr macro d, s
rptr4 d, s, eax, ax
endm
