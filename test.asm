.model small
.Stack 64
.data  

printhexa macro num
    local rakam
    local notZero
    local kammel
        push ax
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
         pop ax
        
endm printhexa 
GO MACRO
        mov ah,0
        mov al,13h
        int 10h 
ENDM GO       
push_all macro                  ;; push all
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push bp
endm push_all   
;;**********  
pop_all macro                  ;; pop all
    pop bp
    pop di
    pop si
    pop dx
    pop cx
    pop bx 
    pop ax 
endm pop_all
;********************************************
mov_cursor macro num       ;; Move Cursor       
     push_all
mov ah,2 
mov bx,0
mov dx,num
int 10h    
pop_all
endm mov_cursor

printmsg macro msg       
    push_all
    mov ah,9
    mov dx,offset msg
    int 21h     
    pop_all
endm printmsg

;--------------READ MESSAGE---------------------

ins db 16,?, 16 dup('$') 
ad db "adhoma$"
.CODE
MAIN PROC FAR
		   mov ax, @data
		   mov DS, ax 
		   GO
		   mainloop: 
		   call readmsg 
		   jmp mainloop
         
		   adham:
		   printmsg ad
	
	MAIN ENDP  
readmsg proc     
    push_all
    mov ah,0ah
    mov dx,offset ins
    int 21h         
    pop_all
    ret 
readmsg endp
END MAIN