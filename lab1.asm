include utility.inc
.model small
.stack 64  
.data
VALUE db ?
player db 0
mainPlayer db 1
.code
;-----------------Initialization-----------------------
init proc far
    mov dx,3fbh ; Line Control Register
    mov al,10000000b ;Set Divisor Latch Access Bit
    out dx,al ;Out it            
    mov dx,3f8h
    mov al,0ch 
    out dx,al
    mov dx,3f9h
    mov al,00h
    out dx,al
    mov dx,3fbh
    mov al,00011011b
    out dx,al
    ret
init endp    
;--------------------------------------------
;-------------Receive------------------------
receive proc far 
mov dx , 3FDH ; Line Status Register
in al , dx
AND al,1
jz CHK

mov dx , 03F8H
in al , dx
mov VALUE , al

mov ah,2
mov dl,VALUE
int 21h
inc di
CHK:
ret
receive endp
;--------------------------------------------------

;---------------------Send------------------------
send proc far
mov dx , 3FDH ; Line Status Register
In al , dx ;Read Line Status
AND al , 00100000b
JZ CheckSend

mov dx , 3F8H ; Transmit data register
mov al,VALUE
out dx , al
inc si

CheckSend:
ret
send endp
;------------------------------------------------------
;------------------------------------------------------
readmacr macro
mov ah,1
int 16h
jz exit
mov ah,0
int 16h

mov VALUE ,al
mov ah,2
mov dl,VALUE
int 21h
endm readmacr
;------------------------------------------------------
main proc far
mov ax,@data
mov ds,ax
call init
clear
mov si,0
mov di,1500h
L:
mov_cursor di
call receive
;send
mov_cursor si
readmacr
call send
exit:
jmp L
hlt
main endp
end main
    