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
.CODE
MAIN PROC FAR
		   mov ax, @data
		   mov DS, ax 
		   GO
		   mov ax,0600h
mov bh,07
mov cx,0
mov dx,184FH
int 10h
		   MOV bl,0AH
		   MOV AX,50H
		   DIV bl
		     
           printhexa dX
           printhexa ax
         
		
	

	MAIN ENDP
END MAIN