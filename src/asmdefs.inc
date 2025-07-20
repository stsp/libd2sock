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
ret
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
_DATA SEGMENT BYTE PUBLIC USE16 'DATA'
endif
endm
ENDFUNC macro nm
nm ENDP
_TEXT ENDS
END
endm
