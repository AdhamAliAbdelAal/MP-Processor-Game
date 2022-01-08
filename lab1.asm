include utility.inc
include srcval.inc
.model small
.stack 64  
.data
VALUE db ?
player db 0
mainPlayer db 1
fortest db "testing$"
ggg db "finish$"
;------------------------------------------------
Target1_VAL_STR db  10,?,10 duP('$') 
Target2_VAL_STR db  10,?,10 duP('$') 
TARGET1 DW 105Eh 
TARGET2 DW 105Eh
;------------Targets screen----------
TARGET1_STR  db   '        ',0ah,0dh 
    DB   '                ====================================================',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh                                         
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||--------------------------------------------------||',0ah,0dh  
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh       
    DB   "               ||      Choose your Opponent's target:              ||",0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh  
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '                ====================================================',0ah,0dh   
    db   '                                                                    ',0ah,0dh      
    db   '                                                                    ',0ah,0dh 
    DB   '$',0ah,0dh  


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
 mov_cursor 0000h    
 printmsg  TARGET1_STR   
    mov_cursor 0936h 
    mov bx,offset Target1_VAL_STR
    mov si,offset Target2_VAL_STR
    add si,2
    add bx,2
    mov cx,0
    mov dx,0
    mov VALUE,-1
    ;take strings
    target_main_loop:
    cmp dl,0Dh
    jz shoofElsend
    CALL receive_optional
    cmp VALUE,-1
    jz shoofElsend
    mov al,VALUE
    mov [bx],al
    inc bx
    inc cl
    mov dl,VALUE
    mov VALUE,-1

    shoofElsend:
    cmp dh,0Dh
    jz shoofHakamel
    mov ah,1
    int 16h
    jz target_main_loop
    mov ah,0
    int 16h
    
    printchar al
    
    mov [si],al
    inc si
    inc ch
    mov VALUE,al
    mov dh,VALUE
    CALL send_optional
    mov VALUE,-1

    shoofHakamel:
    cmp dx,0d0dh
    jmp hagakeda
    hagakeda:
    jz hagabarra
    jmp target_main_loop
    hagabarra:

    mov [bx],dl
    mov bx,offset Target1_VAL_STR
    mov [bx+1],cl
    mov [si],dh
    mov si,offset Target2_VAL_STR
    add si,1
    mov [si],ch

    ;Checks 
    CheckSourceVal  Target1_VAL_STR+2 
    cmp mainPlayer,0
    jmp TestHenaTany

    t2Fe3lan:
    mov target2,dx 
    CheckSourceVal  Target2_VAL_STR+2 
    mov target1,dx
    jmp yallaBara

    TestHenaTany:
    jz t1Fe3lan
    jmp t2Fe3lan

    t1Fe3lan:
    mov target1,dx 
    CheckSourceVal  Target2_VAL_STR+2 
    mov target2,dx
    yallaBara:
hlt
main endp
;---------------optional receive------------------------
receive_optional proc near 
push_all
mov dx , 3FDH ; Line Status Register
in al , dx
AND al,1
jz CHKop

mov dx , 03F8H
in al , dx
mov VALUE , al

CHKop:
pop_all
ret
receive_optional endp
;-------------------------------------------------------

;---------------optional send----------------------------
send_optional proc near
push_all
mov dx , 3FDH ; Line Status Register
In al , dx ;Read Line Status
AND al , 00100000b
JZ CheckSendop

mov dx , 3F8H ; Transmit data register
mov al,VALUE
out dx , al

CheckSendop:
pop_all
ret
send_optional endp
;--------------------------------------------------------
end main