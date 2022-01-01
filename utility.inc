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

;--------------READ CHAR------------------------

readchar macro char
    push_all
    mov ah,0
    int 16h
    mov char, al
    pop_all    
endm readchar

;--------------DISPLAY CHAR---------------------

printchar macro char
    push dx
    mov ah,2
    mov dl,char
    int 21h
    pop dx
endm printchar

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
draw macro position,p
    local jjj
    push_all 
        mov si,position
        mov cx,7
        mov bx,p
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
drawbyte macro position,p
    local jjjk
    local jjjl
    push_all 
        mov si,0200h
        add si,position
        mov cx,8
        mov bx,p
        jjjk:
        mov_cursor si  
        mov ah,memory[BX]
        MOV al,0 
        printhexa05 ax
        add si,2h
        add bx,1
        loop jjjk  
        
        mov si,0500h 
        add si,position
        mov cx,8
        add p,cx
        mov bx,p
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
    mov cx,17 ;5 times
    mov bl,00h ;Green (A) on white(F) background
    int 10h
    pop_all
endm clearins
;----------------------------------------------------
INPUTFIELD MACRO pos
    push_all
    mov si,pos
    mov_cursor si
    clearins
    mov si,pos
    sub si,100h
    mov_cursor si
    clearins
    mov si,pos
    add si,100h
    mov_cursor si
    clearins
    pop_all
ENDM INPUTFIELD
;--------------------------------------
GO MACRO
        mov ah,0
        mov al,13h
        int 10h 
ENDM GO    
;--------------CHECK PLAYER-------------------
checkPlayer_des macro s1,s2
    local p1_dest2
    local next_dest1
    mov bl,player
    cmp bl,0
    je p1_dest2
    mov bx,offset s1
    jmp next_dest1
    p1_dest2:
    mov bx,offset s2
    next_dest1:    
endm checkPlayer_des

;-------------------------------------------------

checkPlayer_src macro s1,s2
    local p1_src2
    local next_src1
    mov dl,player
    cmp dl,0
    je p1_src2
    mov dx,WORD PTR s1
    jmp next_src1
    p1_src2:
    mov dx,WORD PTR s2
    next_src1:    
endm checkPlayer_src

;-------------------------------------------------

checkPlayer_src05 macro s1,s2
    local p1_src05
    local next_src05
    mov dl,player
    cmp dl,0
    je p1_src05
    mov dl, s1
    jmp next_src05
    p1_src05:
    mov dl, s2
    next_src05:    
endm checkPlayer_src05

;-------------------------------------------------

checkPlayer_src10 macro s1,s2
    local p1_src10
    local next_src10
    mov cl,player
    cmp cl,0
    je p1_src10
    mov cx, WORD PTR s1
    jmp next_src10
    p1_src10:
    mov cx, WORD PTR s2
    next_src10:    
endm checkPlayer_src10

;-------------------------------------------------

checkPlayer_srcbr macro s1,s2
    local p1_srcbr
    local next_srcbr
    mov al,player
    cmp al,0
    je p1_srcbr
    mov ax, WORD PTR s1
    jmp next_srcbr
    p1_srcbr:
    mov ax, WORD PTR s2
    next_srcbr:    
endm checkPlayer_srcbr

;-------------------------------------------------

checkPlayer_srcbr2 macro s1,s2
    local p1_srcbr2
    local next_srcbr2
    mov dl,player
    cmp dl,0
    je p1_srcbr2
    add ax, offset s1
    jmp next_srcbr2
    p1_srcbr2:
    add ax, offset s2
    next_srcbr2:    
endm checkPlayer_srcbr2

display_string_off macro mystring   ;; Display offset sting
    push_all 
mov ah,09H
mov dx, mystring
int 21h
pop_all
endm display_string
;;**************************** 
clear macro                     ;; Clear string 
     push_all
    mov ax,0600h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h  
    pop_all
endm clear  
;;****************************   
wait_enter macro
    LOCAL Enter                     ;; Wait enter  
    push_all
  Enter:
    mov ah,0
    int 16h
    cmp ah,1ch
  jnz Enter  
pop_all                       
endm wait_enter  
;;**************************** 
DRAWREG_PLAYERS MACRO
    INPUTFIELD 444ch
    ;player one drawings
    mov bp,0
    draw  3A1bh,bp
    drawbyte 0000h,bp 
    ;player two drawings 
    mov bp,14
    draw  3A39h,bp
    add bp,2
    drawbyte 0018h,bp
    mov_cursor 444ch
ENDM DRAWREG_PLAYERS