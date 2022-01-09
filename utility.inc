;--------------PRINT MESSAGE--------------------

printmsg macro msg       
    push_all
    mov ah,9
    mov dx,offset msg
    int 21h     
    pop_all
endm printmsg

;--------------READ MESSAGE---------------------


readmsg macro ins2
    local st
    local ex
    local IsToScore
    local KammelHena 
    LOCAL OUTOFREAD 
    LOCAL ana_Dah
    LOCAL PressEnter
    clear_buffer
PUSH_ALL
mov cl,0
mov BX,offset ins2
ADD BX,2
st:
mov al,mainPlayer
cmp player,al
jz ana_Dah
CALL receive
mov al,VALUE
jmp PressEnter
ana_Dah:
mov ah,0
int 16h
mov VALUE,al
CALL send
PressEnter:
cmp aL,0Dh
je ex
cmp ah,3eh
jmp IsToScore
KammelHena:
inc cl

mov [BX],al
inc BX
mov ah,2
mov dl,al
int 21h
jmp st

ex:
MOV [BX],AL
mov BX,offset ins2
mov [BX+1],cl
JMP OUTOFREAD
IsToScore:
jne KammelHena
jmp toScoreScreen 
OUTOFREAD: 
POP_ALL    
endm readmsg

;--------------READ CHAR------------------------

readchar macro char
    LOCAL mp1
    LOCAL read_char
    clear_buffer
    push_all
    mov al,player
    cmp al,mainPlayer
    je mp1
    CALL receive
    mov al,VALUE
    jmp read_char
    mp1:
    mov ah,0
    int 16h
    mov VALUE,al
    CALL send
    read_char:
    mov char,al
    pop_all    
endm readchar

;--------------DISPLAY CHAR---------------------

printchar macro char
    push_all
    mov ah,2
    mov dl,char
    int 21h
    pop_all
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

print_dec macro num               
       Push_all       
       mov al,num
       mov ah,0
       mov cl,100
       div cl
       
      
       
       mov bh,ah 
       
       
       mov ah,2
       add al,30h
       mov dl,al
       int 21h
       
        
       mov al,bh
       mov ah,0
       mov cl,10
       div cl
       
       mov bh,ah
       mov ah,2
       add al,30h
       mov dl,al
       int 21h
       
       
        
       mov al,bh
       mov ah,2
       add al,30h
       mov dl,al
       int 21h
       POP_ALL
       
endm print_dec

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
    LOCAL Enter
    LOCAL Check4Send            ;; Wait enter
    LOCAL A5er_Check  
    push_all
    mov dx,0
    mov VALUE,0
  Enter:
  cmp dl,1ch
  jz Check4Send
  CALL receive_optional
  mov dl,VALUE
  mov VALUE,0
  Check4Send:
  cmp dh,1ch
  jz A5er_Check
  mov ah,1
  int 16h
  jz A5er_Check
  mov ah,0
  int 16h
  mov VALUE,ah
  mov dh,VALUE
  CALL send_optional
  mov VALUE,0
  A5er_Check:
  cmp dx,1c1ch
  jnz Enter  
pop_all                       
endm wait_enter  
;;**************************** 
DRAWREG_PLAYERS MACRO
    LOCAL printFL
    LOCAL ex_fl
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
     ;mov_cursor 4a1bh
    ;mov DH,Point
    ;MOV DL,0
    ;printhexa05 DX
    ;mov_cursor 4a3bh
    ;mov DH,Point2
    ;MOV DL,0
    ;printhexa05 DX
    mov_cursor 1408h
        printmsg player_name+2
        
        mov_cursor 1508h 
        print_dec point   
         
          
        mov_cursor 1416h  
        printmsg player_name2+2 
        
        mov_cursor 1516h 
        print_dec point2
    mov al,level
    sub al,30h
    CMP al,1
    JE printFL
    jmp ex_fl
    printFL:
    mov_cursor 150dh
    printchar FL1
    mov_cursor 151bh
    printchar FL2
    ex_fl:
    mov_cursor 444ch
ENDM DRAWREG_PLAYERS
;;****************************  
;;--------------- cahnge target first player---------------- 
taget_1 macro
 push_all
 clear
 clear_buffer
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
    ;wait_enter  
 pop_all 
endm taget_1 
;;*******************************    
;;--------------- cahnge target second player---------------- 
taget_2 macro
     xor player,1 
 push_all
 clear              
 mov_cursor 0000h 
 printmsg  TARGET1_STR  
     mov_cursor 0936h 
    readmsg  Target2_VAL_STR  
    
     CheckSourceVal  Target2_VAL_STR+2 
    mov target2,dx  
    wait_enter  
 pop_all    
  xor player,1
endm taget_2
;-----------------------------------------
Text_Mode macro  
    push_all
mov ah,0
mov al,3
int 10h 
pop_all   
endm Text_Mode

;-----------------------------------------

CONG macro NUM,MSG1,MSG2,msg3 
                       ;; Clear string 
     
    clear   
    
    Text_Mode
    
    mov_cursor 0000h  
    
    
      
    printmsg MSG3  
     
    mov_cursor 081AH
    printmsg MSG1
           
    mov ah,2
    mov dl,NUM
    add dl,30h
    int 21h 
           
    printmsg MSG2     
    
    wait_enter
    
ENDM cong

;-----------------------------------------

CheckWinner1 MACRO ; Check regs l tany 3la Target1
    local Player1_WON
    local ex_p11
    local cont_check
    local testfathi
    local chfix
    push_all
    cmp point,0
    JNE chfix
    jmp testfathi
    chfix:
    jmp cont_check
    testfathi:
    MOV CL,1
    MOV FE_PLAYER_KESEB,CL
    cong 2,WINNER,WON,cong_screen
    jmp ex_p11
    cont_check:
    MOV AX,TARGET2
    MOV DI, offset AXREG2
    MOV CX,8
    REPNE SCASW
    cmp cx,0
    JNE Player1_WON
    jmp ex_p11
    Player1_WON:
    MOV CL,1
    MOV FE_PLAYER_KESEB,CL
    cong 1,WINNER,WON,cong_screen
    ex_p11:
    pop_all     
ENDM CheckWinner1

;-----------------------------------------

CheckWinner2 MACRO
    local Player2_WON
    local ex_p12
    local cont_check2
    local testfathi2
    local chfix2
    push_all
    cmp point2,0
    JNE chfix2
    jmp testfathi2
    chfix2:
    jmp cont_check2
    testfathi2:
    MOV CL,1
    MOV FE_PLAYER_KESEB,CL
    cong 1,WINNER,WON,cong_screen
    jmp ex_p12
    cont_check2:
    MOV AX,TARGET1
    MOV DI, offset AXREG
    MOV CX,8
    REPNE SCASW
    cmp cx,0
    JNE Player2_WON
    jmp ex_p12
    Player2_WON:
    MOV CL,1
    MOV FE_PLAYER_KESEB,CL
    cong 2,WINNER,WON,cong_screen
    ex_p12:
    pop_all      
ENDM CheckWinner2    
;-----Flag Register---------------
Flag_reg_check_PUSH macro
    local alFl
    local FlP1
    ;push_all 
    cmp player,0
    je FlP1
    PUSH FREG2
    jmp alFl
    FlP1:
    PUSH FREG  
    alFl:    
    ;pop_all
endm Flag_reg_check_PUSH 
;----------------------
Flag_reg_check_POP macro 
    local al_POP
    local Fl_POP 
    ;push_all
    cmp player,0
    je Fl_POP
    POP FREG2
    jmp al_POP
    Fl_POP:
    POP FREG  
    al_POP:
    ;pop_all
endm Flag_reg_check_POP      
;--------------------
decPoints macro num
        mov bx,offset Point
        add bl,player
        mov al,[bx]
        sub al,num
        mov [bx],al 
endm decPoints 
detectPoints macro num 
    local Hayenfa3pow
    mov bx,offset Point
    add bl,player
    mov al,[bx]
    cmp al,num
    jae Hayenfa3pow
    jmp ENDCHECKS
    Hayenfa3pow: 
    decPoints num
endm detectPoints
;--------------------
SelectProcessor MACRO
    LOCAL EX_PROC
    LOCAL P0PROC
    LOCAL SP1
    LOCAL SP11
    LOCAL SP2
    LOCAL SP22
    LOCAL SP3
    LOCAL SP33
    LOCAL SP4
    LOCAL SP44
    push_all
    MOV AL,level
    SUB AL,30h
    CMP AL,1
    JMP SP1
    SP11:
    cmp Processor_Select,0
    JMP SP2
    SP22:
    CMP player,0
    JMP SP3
    SP33:
    readchar Processor2
    printchar Processor2
    MOV AH,Processor2
    SUB AH,30h
    CMP AH,1
    jmp sp4
    SP44:
    xor player,1
    JMP EX_PROC
    
    P0PROC:
    readchar Processor1
    printchar Processor1
    MOV Al,Processor1
    SUB Al,30h
    CMP Al,2
    JE EX_PROC
    xor player,1
    JMP EX_PROC
    SP1:
    JE EX_PROC
    JMP SP11
    SP2:
    JE EX_PROC
    JMP SP22
    SP3:
    JE P0PROC
    JMP SP33
    sp4:
    JE EX_PROC
    JMP SP44
    EX_PROC:
    pop_all
ENDM SelectProcessor

;--------------------
draw_bk macro n1,n2,n3,n4,IMG
LOCAL DRAWIT
LOCAL START
LOCAL ENDING
       
       
       PuSH_ALL
        
    
        
      	;MOV AH,0Bh       
          	;set the configuration
       MOV CX, n1 	;set the width (X) up to image width (based on image resolution)
       MOV DX, n2 	;set the hieght (Y) up to image height (based on image resolution)
       mov DI, offset img  ; to iterate over the pixels
       jmp Start    	;Avoid drawing before the calculations
Drawit:
       MOV AH,0Ch   	;set the configuration to writing a pixel
           mov al, [DI]     ; color of the current coordinates
       MOV BH,00h   	;set the page number
       INT 10h      	;execute the configuration
Start: 
	   inc DI
       dec cx       	;  loop iteration in x direction
       cmp cx,n3
       jne Drawit      	;  check if we can draw c urrent x and y and excape the y iteration
       mov Cx,n1  	;  if loop iteration in y direction, then x should start over so that we sweep the grid
       DEC DX
       cmp dx,n4
            	;  loop iteration in y direction
       Je  ENDING   	;  both x and y reached 00 so end program
	   Jmp Drawit    
	   POP_ALL  
	   
	    
	  	   
	   

	ENDING:
ENDM draw_bk

print_dec2 macro num               
       Push_all
       MOV AX,0       
       mov aL, NUM
       mov cl,10
       div cl
       
       mov bh,ah
       mov ah,2
       add al,30h
       mov dl,al
       int 21h
       
       
        
       mov al,bh
       mov ah,2
       add al,30h
       mov dl,al
       int 21h
       POP_ALL
       
endm print_dec2 

DrawTargetPoints MACRO
        mov_cursor 6f10h
        print_dec2 green_color   
        
        mov_cursor 6f14h
        print_dec2 light_blue_color   
        
        mov_cursor 6f18h
        print_dec2 blue_color  
        
        mov_cursor 7310h
        print_dec2 yellow_color  
        
        mov_cursor 7314h
        print_dec2 red_color 
ENDM DrawTargetPoints

DrawTargetPoints2 MACRO
        mov_cursor 6f1Eh
        print_dec2 green_color2   
        
        mov_cursor 6f22h
        print_dec2 light_blue_color2   
        
        mov_cursor 6f26h
        print_dec2 blue_color2  
        
        mov_cursor 7322h
        print_dec2 yellow_color2  
        
        mov_cursor 7326h
        print_dec2 red_color2  
ENDM DrawTargetPoints2

DrawPointsScreen MACRO
    LOCAL SEC5_LOOP
    push_all
    clear
    Text_Mode 
    mov_cursor 0400h 
    printmsg Points_Screen 
    mov_cursor 0c1Fh
    print_dec point 
    mov_cursor 0c3Eh
    print_dec point2
    MOV BX,5
    SEC5_LOOP:
    MOV CX,0FH
    MOV DX,4240H
    MOV AH,86H
    INT 15H
    DEC BX
    JNZ SEC5_LOOP 
 pop_all        
ENDM DrawPointsScreen 

;mov ah,0
 ;   int 16h
  ;  mov ah,02ch        ; Get current second         
   ;     int 021h
    ;    mov bh,dh
     ;   loop_5s:
      ;  mov ah,02ch
       ; int 021h
       ; sub dh,05h        
       ; cmp bh,dh                    
       ; je loop_5s
       
blacked macro  n1,n2,n3,n4
    LOCAL DRAWIT
    LOCAL START
    LOCAL ENDING
           
           
           PuSH_ALL
            
        
            
          	;MOV AH,0Bh       
	          	;set the configuration
	       MOV CX, n1 	;set the width (X) up to image width (based on image resolution)
	       MOV DX, n2 	;set the hieght (Y) up to image height (based on image resolution)
	                  ; to iterate over the pixels
	       jmp Start    	;Avoid drawing before the calculations
	Drawit:
	       MOV AH,0Ch   	;set the configuration to writing a pixel
           mov al, 0H    ; color of the current coordinates
	       MOV BH,00h   	;set the page number
	       INT 10h      	;execute the configuration
	Start: 
	       dec cx       	;  loop iteration in x direction
	       cmp cx,n3
	       jne Drawit      	;  check if we can draw c urrent x and y and excape the y iteration
	       mov Cx,n1  	;  if loop iteration in y direction, then x should start over so that we sweep the grid
	       DEC DX
	       cmp dx,n4
	            	;  loop iteration in y direction
	       Je  ENDING   	;  both x and y reached 00 so end program
		   Jmp Drawit    
		   POP_ALL  
		   
		  
	ENDING:   
    
endm balacked

PlayerTurn macro
    mov_cursor 1701h
    printmsg Player_Turn
    mov_cursor 1708h
    MOV AL,player
    ADD AL,31h
    printchar AL
endm PlayerTurn

clear_buffer macro
local Kammel_Deletion
local testClear
push_all
jmp testClear
Kammel_Deletion:
mov ah,0
int 16h
testClear:
mov ah,1
int 16h
jnz Kammel_Deletion
pop_all
endm clear_buffer