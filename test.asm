.MODEL SMALL

;--------------PRINT MESSAGE--------------------

printmsg macro msg
    mov ah,9
    mov dx,offset msg
    int 21h
endm printmsg

;--------------READ MESSAGE---------------------

readmsg macro msg
    mov ah,0ah
    mov dx,offset msg
    int 21h
endm readmsg

.STACK 64

.DATA
instruction db 16,?, 16 dup('$')
;input db 16,?, 16 dup('$')
newline db 10,13,'$'
.CODE
MAIN PROC
MOV AX, @DATA
MOV DS, AX
mov ah,0
mov al,13h
int 10h
readmsg 
MAIN ENDP
END MAIN