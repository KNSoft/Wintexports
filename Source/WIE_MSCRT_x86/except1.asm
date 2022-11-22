.686P
.XMM
.model flat, stdcall

PUBLIC _except1

.code

; FIXME:
;   _except1 is not implemented and not be used,
;   call __fastfail instead.

_except1:
    xor ecx, ecx
    int 29h ; __fastfail

END
