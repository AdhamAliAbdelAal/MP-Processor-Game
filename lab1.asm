.model small
.stack 64
clear macro                     ;; Clear string  
    mov ax,0600h 
    mov bh,07 
    mov cx,0 
    mov dx,184FH 
    int 10h    
endm clear
mov_cursor macro num       ;; Move Cursor        
mov ah,2  
mov bx,0 
mov dx,num 
int 10h     
endm mov_cursor
.data
VALUE db ?
.code
init proc far
    mov dx,3fbh ; Line Control Register
    mov al,10000000b ;Set Divisor Latch Access Bit
    out dx,al ;Out it
    mov dx,3f8h
    mov al,0ch
    mov dx,3f9h
    mov al,00h
    out dx,al
    out dx,al
    mov dx,3fbh
    mov al,00011011b
    out dx,al
    ret
init endp

receive proc far
mov_cursor si
mov dx , 3FDH ; Line Status Register
in al , dx
AND al , 1
JZ CHK
mov dx , 03F8H
in al , dx
mov VALUE , al
mov ah,2
mov dl,VALUE
int 21h
inc si
CHK:
ret
receive endp

send proc far
mov dx , 3FDH ; Line Status Register
AGAIN:
In al , dx ;Read Line Status
AND al , 00100000b
JZ AGAIN
mov dx , 3F8H ; Transmit data register
mov al,VALUE
out dx , al
ret
send endp

main proc far
mov ax,@data
mov ds,ax
call init
clear
mov si,1500h
mov di,0000h
L:
call receive
;send
mov_cursor di 
inc di
mov ah,1
int 16
jz exit
mov ah,0
int 16h
mov VALUE ,al
mov ah,2
mov dl,VALUE
int 21h
call send
exit:
;receive


jmp L
hlt
main endp
end main
    