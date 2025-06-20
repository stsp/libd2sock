FUNC macro nm
PUBLIC nm
nm PROC NEAR C
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
.386p
_TEXT SEGMENT BYTE PUBLIC 'CODE'
endm
ENDFUNC macro nm
nm ENDP
_TEXT ENDS
END
endm
