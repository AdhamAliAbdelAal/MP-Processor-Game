;--------------PRINT MESSAGE--------------------

printmsg macro msg       
    push_all
    mov ah,9
    mov dx,offset msg
    int 21h     
    pop_all
endm printmsg

;--------------READ MESSAGE---------------------

readmsg macro msg   
    push_all
    mov ah,0ah
    mov dx,offset msg
    int 21h         
    pop_all
endm readmsg

;--------------checkEQUALITY--------------------

checkEQUALITY MACRO S1,S2 
    MOV CX, 3 
    MOV SI, offset S1  
    MOV DI, offset S2 
    REPE CMPSB
    cmp cx,0     
endm checkEQUALITY

;--------------checkInstructionEQUALITY---------

checkINSEQUALITY MACRO S1,S2 
    MOV CX, 4 
    MOV SI, offset S1  
    MOV DI, offset S2 
    REPE CMPSB
    cmp cx,0     
endm checkINSEQUALITY
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
;**********************************************
printhexa05 macro num
    local rakam05
    local notZero05
    local kammel05
    push_all
        mov bx,num
        mov cx,2
        notZero05:
        mov dl,bh
        push cx
        mov cl,4
        shr dl,cl
        pop cx
        cmp dl,9
        jle rakam05
        add dl,55
        jmp kammel05
        rakam05: 
        add dl,30h
        kammel05:
        push cx
        mov cl,4 
        shl bx,cl
        pop cx
        mov ah,2
        int 21h
        loop notZero05
        pop_all
endm printhexa05  
;-------------------------------
draw macro
    local jjj
    push_all 
        mov si,3A1bh
        mov cx,7
        mov bx,0
        jjj:
        mov_cursor si  
        mov ax,AXREG[bx] 
        printhexa ax
        add si,200h
        add bx,2
        loop jjj
        pop_all
endm draw
;------------------------------------
drawbyte macro
    local jjjk
    local jjjl
    push_all 
        mov si,0200h
        mov cx,8
        mov bx,0
        jjjk:
        mov_cursor si  
        mov ah,memory[BX]
        MOV al,0 
        printhexa05 ax
        add si,2h
        add bx,1
        loop jjjk
        
        mov si,0500h
        mov cx,8
        mov bx,8
        jjjl:
        mov_cursor si  
        mov ah,memory[BX]
        MOV al,0 
        printhexa05 ax
        add si,2h
        add bx,1
        loop jjjl
     pop_all
endm drawbyte  
;-----------------------------------------

Draw_BK macro 
 push_all      
   MOV AH,0
   MOV AL,13H
   INT 10H
   MOV AH,0Bh   	;set the configuration
   MOV CX, imgW  	;set the width (X) up to image width (based on image resolution)
   MOV DX, imgH 	;set the hieght (Y) up to image height (based on image resolution)
   mov DI, offset img  ; to iterate over the pixels
   jmp Start    	;Avoid drawing before the calculations
Drawit:
   MOV AH,0Ch   	;set the configuration to writing a pixel
   mov al, [DI]     ; color of the current coordinates
   MOV BH,00h   	;set the page number
   INT 10h      	;execute the configuration
Start: 
   inc DI
   DEC Cx       	;  loop iteration in x direction
   JNZ Drawit      	;  check if we can draw c urrent x and y and excape the y iteration
   mov Cx, imgW 	;  if loop iteration in y direction, then x should start over so that we sweep the grid
   DEC DX       	;  loop iteration in y direction
   JZ  ENDING   	;  both x and y reached 00 so end program
   Jmp Drawit  
ENDING:     
pop_all
endm Draw_BK
;------------------------------------
resetins macro ins
    push_all 
    mov cx,16
    mov al,'$'
    mov di,offset ins
    REP STOSB
    pop_all
endm clearins  
;--------------------------------------------
clearins macro 
    push_all
    mov ah,9 ;Display
    mov bh,0 ;Page 0
    mov al,'M' ;Letter D
    mov cx,16 ;5 times
    mov bl,00h ;Green (A) on white(F) background
    int 10h
    pop_all
endm clearins
;----------------------------------------------------
INPUTFIELD MACRO
    push_all
    mov si,444ch
    mov_cursor si
    clearins
    mov si,434ch
    mov_cursor si
    clearins
    mov si,454ch
    mov_cursor si
    clearins
    pop_all
ENDM INPUTFIELD
