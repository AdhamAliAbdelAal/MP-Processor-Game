include srcval.inc
;---------Print Hexa---------------------------
printhexa macro num
    local rakam
    local notZero
    local kammel
    push_all
        mov bx,num
        mov cx,4
        notZero:
        mov dl,bh
        push cx
        mov cl,4
        shr dl,cl
        pop cx
        cmp dl,9
        jle rakam
        add dl,55
        jmp kammel
        rakam: 
        add dl,30h
        kammel:
        push cx
        mov cl,4 
        shl bx,cl
        pop cx
        mov ah,2
        int 21h
        loop notZero
        pop_all
endm printhexa
;-------------------------------------------------
push_all macro                  ;; push all
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push bp
endm push_all   
;;**  
pop_all macro                  ;; pop all
    pop bp
    pop di
    pop si
    pop dx
    pop cx
    pop bx 
    pop ax 
endm pop_all
;******  
clear macro                     ;; Clear string 
     push_all
    mov ax,0600h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h  
    pop_all
endm clear     
printmsg macro msg       
    push_all
    mov ah,9
    mov dx,offset msg
    int 21h     
    pop_all
endm printmsg                  
.MODEL SMALL
.STACK 64
.DATA                        

RR DB "12AB",0DH,'$'    

.CODE    
MAIN PROC FAR
    MOV AX,@DATA
    MOV DS,AX  
    ;PRINTMSG RR+2 
    ;CLEAR
    CHECKSOURCEVAL RR 
    PRINTHEXA DX   
MAIN ENDP
END MAIN