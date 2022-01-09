read_num macro mydata  ;;Read num     
    push_all 
    mov cx,0
    mov ah,1
    int 21h
    sub al,30h
    mov dl,10
    mul dl
    add cl,al
    mov ah,1
    int 21h
    sub al,30h
    add cl,al
    mov mydata,cl 
     pop_all
endm read_num  
 ;;************************************************************
 
;---------------------init no Wait------------------------                  
init_no macro 
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
    
endm init_no  
;------------------------------------------------------  

;-------------Receive no wait------------------------
receive_no macro       
    local enter_es
    local CHK_no_eee 
mov dx , 3FDH ; Line Status Register
in al , dx
AND al,1
jz CHK_no_eee

mov dx , 03F8H
in al , dx
cmp aL,0Dh 
jz enter_es
mov VALUE , al
mov bx, pointer_no_2_of
add bx,  pointer_no_2
mov ah,0DH
mov al,VALUE
mov [bx],ax 
inc pointer_no_2
jmp CHK_no_eee
enter_es:  
inc NO_ENTER_2        
mov cx,pointer_no_2
sub cx,2
mov al,15
mov ah,cl
mov bx, pointer_no_2_of  
mov [bx], ax
mov bx,offset STR_Point2
mov pointer_no_2_of,bx
mov pointer_no_2,2
;inc di
CHK_no_eee:

endm receive_no 
;-------------------------------------------------- 
      ;;BYTE PTR
;---------------------Send no wait------------------------
send_no macro 
    local CheckSend_no_e
    local enter_es2 
    local ll
mov dx , 3FDH ; Line Status Register
In al , dx ;Read Line Status
AND al , 00100000b
JnZ ll
jmp CheckSend_no_e
ll:
mov dx , 3F8H ; Transmit data register
mov al,VALUE
out dx , al
 
 cmp al,0Dh 
jz enter_es2 
mov bx, pointer_no_1_of
add bx,  pointer_no_1
mov ah,0DH
mov al,VALUE
mov [bx],ax
inc pointer_no_1
jmp CheckSend_no_e
enter_es2: 
mov NO_MOUSE , 0b33h 
mov_cursor NO_MOUSE 
INC NO_ENTER_1
mov cx,pointer_no_1
sub cx,2
mov al,15
mov ah,cl
mov bx, pointer_no_1_of  
mov [bx], ax
mov bx,offset STR_Point
mov pointer_no_1_of,bx
mov pointer_no_1,2
;inc si

CheckSend_no_e:
;ret
 endm send_no
;------------------------------------------------------
;;*****************************       ;; read_number
read_number macro ins,TEMP  
    LOCAL MainLoop 
    LOCAL PreventShift 
    LOCAL Sizeloop  
    LOCAL LOOP_MM  
    LOCAL ZERO  
    LOCAL EXIT  
    LOCAL MM 
    push_all 
    MOV DX,0 
    MOV CL, 0 
    MOV BX, 0 
     
    ;------Determine string size-------- 
    Sizeloop: 
        MOV CH, BYTE PTR Ins[BX] 
        INC BX 
        INC CL 
        MOV AH,0DH 
        CMP CH, AH 
        JNE Sizeloop 
    DEC CL  
      MOV DX,0  
      MOV AX,0 
    MOV AL,10 
    MOV BL,CL  
    DEC CL 
    CMP CL,0 
    JZ  ZERO 
    DEC CL  
    CMP CL,0 
    JZ MM 
    LOOP_MM: 
        MUL AL 
        DEC CL  
        JNZ LOOP_MM    
        MOV CL,BL 
        MOV DL,0     
        MOV BX,0   
        jmp  MainLoop 
         
        MM: 
            MOV AL,10  
            MOV CL,BL 
            MOV DL,0     
            MOV BX,0 
     
   MainLoop: 
           MOV CH, BYTE PTR Ins[BX] 
           SUB CH,30H 
           push ax 
           MUL CH  
            
           ADD DL,AL  
           pop ax 
            MOV DH, 10 
            DIV DH 
           INC BX 
         DEC CL 
        JNZ MainLoop 
         
        mov TEMP,DL  
        JMP EXIT    
         
        ZERO: 
        MOV BX,0 
        MOV CH,BYTE PTR Ins[BX]  
          SUB CH,30H 
        MOV TEMP,CH   
    EXIT: 
        pop_all 
endm  read_number  
;;*************************
readmacr macro  
    local exit  
     push_all
mov ah,1
int 16h
jz exit
mov ah,0
int 16h

mov VALUE ,al
pop_all
exit:
endm readmacr 
;;-------------------------------------
wait_enter_eslam macro
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
;;********************************
start_screen macro                     ;; Start Screen
    local L_eslam
    local exit
    local exit_e
    local d
    local kk
    local jj  
 push_all 
 mov bx , offset player_name
 mov pointer_no_1_of,bx
 mov bx , offset player_name2
 mov pointer_no_2_of,bx             
    call init
    mov_cursor 0000h  
    printmsg  GAME_Start_STR  
    mov_cursor 082eh  
   mov NO_MOUSE ,082eh 
       L_eslam:
             ;call receive_no_e
             receive_no
                
                mov ah,1
                int 16h
                jnz kk
                jmp exit
                kk:
                
                mov ah,0
                int 16h
                 cmp NO_ENTER_1,2
                 jl jj
                  jmp exit
                  jj: 
                mov VALUE ,al 
                inc NO_MOUSE
                 mov_cursor NO_MOUSE
                mov ah,2
                mov dl,VALUE
                int 21h
            ;call send_no_e
             send_no 
        exit:
        mov cl,0
        add cl,NO_ENTER_2
        add  cl,NO_ENTER_1
        cmp cl,4
        jl d
        jmp exit_e
        d:
        jmp L_eslam 
        
    exit_e:  
    ;wait_enter
     read_number STR_Point+2,POINT 
     read_number STR_Point2+2,POINT2
    MOV AH,POINT
    MOV AL,POINT2
    CMP AH,AL
    JNC POINT_AKBAR
    MOV POINT2,AH
    JMP EX_CHOOSE
    POINT_AKBAR:
    MOV POINT,AL
    EX_CHOOSE:     
 pop_all 
endm start_screen  
;;------------------------------------------
;-------------Receive main------------------------
receive_main macro       
    local ll_es
    local CHK_no_eee
    local ex
    local f2_near
    local f1
    local f1_second_line
    local  f1_more_lines
    local f2
    local f2_second_line
    local f2_more_lines 
    local con  
    local con2 
mov dx , 3FDH ; Line Status Register
in al , dx
AND al,1
jnz ll_es
 jmp CHK_no_eee
ll_es:
mov dx , 03F8H
in al , dx
mov VALUE , al
  
   cmp VALUE,3bh
  jz f1
    cmp VALUE,3ch
    jz  f2_near
    cmp VALUE,01h 
    jz ex 
  
 jmp  CHK_no_eee  
    ex:
        hlt 
    f2_near:
    jmp  f2
    f1: 
    cmp if_f1_1,1
    jne con
    jmp chat_fathi
    con: 
    mov if_f1_2,1
    mov if_f1_1,0
    mov if_f2_2,0
    mov if_f2_1,0
       CMP begin_nof,0
       jnz f1_second_line
       mov_cursor 1600H
       printmsg get1_STR  
       lea di, get1_STR 
       mov pointer,di
       inc begin_nof
       jmp CHK_no_eee  
       
    f1_second_line:  
    
        CMP begin_nof,1
       jnz f1_more_lines
       mov_cursor 1700H
       printmsg get1_STR
       lea di, get1_STR 
       mov pointer,di
       inc begin_nof  
       
       jmp CHK_no_eee
      
    f1_more_lines:
         
        mov_cursor 1600H 
        printmsg   CLEAR_LINE
        mov_cursor 1600H 
        display_string_off pointer
        mov_cursor 1700H 
        printmsg   CLEAR_LINE
        mov_cursor 1700H
        printmsg get1_STR
        lea di, get1_STR 
        mov pointer,di
        jmp CHK_no_eee
     
    f2:
    cmp if_f2_1,1
    jne con2
    jmp game_eslam 
    con2: 
    mov if_f1_2,0
    mov if_f1_1,0
    mov if_f2_2,1
    mov if_f2_1,0
       CMP begin_nof,0
       jnz f2_second_line
       mov_cursor 1600H
       printmsg get2_STR  
       lea di, get2_STR 
       mov pointer,di
       inc begin_nof
       jmp CHK_no_eee  
       
    f2_second_line:
        CMP begin_nof,1
       jnz f2_more_lines
       mov_cursor 1700H
       printmsg get2_STR 
       lea di, get2_STR 
       mov pointer,di
       inc begin_nof
       jmp CHK_no_eee
      
    f2_more_lines: 
        mov_cursor 1600H 
        printmsg   CLEAR_LINE 
        mov_cursor 1600H 
        display_string_off pointer 
        mov_cursor 1700H 
        printmsg   CLEAR_LINE
        mov_cursor 1700H
        printmsg get2_STR   
        lea di, get2_STR 
        mov pointer,di
    


CHK_no_eee:

endm receive_main 
;-------------------------------------------------- 
      ;;BYTE PTR
;---------------------Send main------------------------
send_main macro 
    local CheckSend_no_e 
    local ll_es
    local ex_es
    local f2_near
    local f1
    local f1_second_line
    local  f1_more_lines
    local f2
    local f2_second_line
    local f2_more_lines 
    local con  
    local con2
mov dx , 3FDH ; Line Status Register
In al , dx ;Read Line Status
AND al , 00100000b
JnZ ll_es
jmp CheckSend_no_e
ll_es:
mov dx , 3F8H ; Transmit data register
mov al,VALUE
out dx , al
 
 cmp ah,3bh
    jz f1
    cmp VALUE,3ch
    jz  f2_near
    cmp VALUE,01h 
    jz ex_es 
  
 jmp  CheckSend_no_e  
    ex_es:
        hlt 
    f2_near:
    jmp  f2
    f1: 
    cmp if_f1_2,1
    jne con
   jmp chat_fathi
    con: 
    mov if_f1_2,0
    mov if_f1_1,1
    mov if_f2_2,0
    mov if_f2_1,0
       CMP begin_nof,0
       jnz f1_second_line
       mov_cursor 1600H
       printmsg F1_str  
       lea di, F1_STR 
       mov pointer,di
       inc begin_nof
       jmp CheckSend_no_e  
       
    f1_second_line:  
    
        CMP begin_nof,1
       jnz f1_more_lines
       mov_cursor 1700H
       printmsg F1_str
       lea di, F1_STR 
       mov pointer,di
       inc begin_nof  
       
       jmp CheckSend_no_e
      
    f1_more_lines:
         
        mov_cursor 1600H 
        printmsg   CLEAR_LINE
        mov_cursor 1600H 
        display_string_off pointer
        mov_cursor 1700H 
        printmsg   CLEAR_LINE
        mov_cursor 1700H
        printmsg F1_str 
        lea di, F1_STR 
        mov pointer,di
        jmp CheckSend_no_e
     
    f2:
    cmp if_f2_2,1
    jne con2
    jmp notfirst 
    con2: 
    mov if_f1_2,0
    mov if_f1_1,0
    mov if_f2_2,0
    mov if_f2_1,1
       CMP begin_nof,0
       jnz f2_second_line
       mov_cursor 1600H
       printmsg F2_STR  
       lea di, F2_STR 
       mov pointer,di
       inc begin_nof
       jmp CheckSend_no_e  
       
    f2_second_line:
        CMP begin_nof,1
       jnz f2_more_lines
       mov_cursor 1700H
       printmsg F2_STR 
       lea di, F2_STR 
       mov pointer,di
       inc begin_nof
       jmp CheckSend_no_e
      
    f2_more_lines: 
        mov_cursor 1600H 
        printmsg   CLEAR_LINE 
        mov_cursor 1600H 
        display_string_off pointer 
        mov_cursor 1700H 
        printmsg   CLEAR_LINE
        mov_cursor 1700H
        printmsg F2_STR   
        lea di, F2_STR 
        mov pointer,di
    
CheckSend_no_e:
;ret
 endm send_main
;;**************************** 
main_screen macro                     ;; Main Screen 
     local L_eslam  
     local exit
     local kk 
     local end_eslam
     push_all          
     mov_cursor 0000h 
    printmsg  GAME_Main_STR    
    
    
    
      L_eslam:
             receive_main
                
                mov ah,1
                int 16h
                jnz kk
                jmp exit
                kk:  
                mov ah,0
                int 16h
                mov VALUE ,ah 
       
             send_main 
        exit:
        
        jmp L_eslam  
    notfirst:
    mov mainPlayer,1
    mov FRISTPLAYER, 1
    mov player_choose,0      
    MOV SI,OFFSET  player_name
    MOV DI,OFFSET  player_name_TEMP
    MOV CX,13
    REP MOVSB 
    MOV SI,OFFSET  player_name2
    MOV DI,OFFSET  player_name2_TEMP
    MOV CX,13
    REP MOVSB 
    MOV SI,OFFSET  player_name_TEMP
    MOV DI,OFFSET  player_name2
    MOV CX,13
    REP MOVSB 
    MOV SI,OFFSET  player_name2_TEMP
    MOV DI,OFFSET  player_name
    MOV CX,13
    REP MOVSB
    
    ;MOV CL ,POINT
    ;MOV CH, POINT2
    ;MOV POINT,CH
    ;MOV POINT2,CL
    JMP END_ESLAM     
    game_eslam:  
      end_eslam:
         jmp main_cont 
     
     chat_fathi:
        
        CALL init
        chatt
        clear
        mov if_f1_2,0
        mov if_f1_1,0
        mov if_f2_2,0
        mov if_f2_1,0
        jmp MAINHAMDY
    wait_enter_eslam 
     
;****************************************
;;------------------------------------
    
 pop_all            
endm main_screen
;****************************************
;;------------------------------------
SelectLevel MACRO
    push_all
    clear 
    mov_cursor 0400h 
    printmsg  level_selection 
    mov_cursor 0c32h
    readchar level
    ;printchar mainPlayer
    printchar level
    wait_enter     
 pop_all 
ENDM SelectLevel

CONVERT2REGS MACRO
    LOCAL convert2Numbers
    LOCAL Tele3Afel
    LOCAL tmam_gedan
    LOCAL el7
    local hona
    convert2Numbers:
    mov al,[bx]
    mov [di],al
    cmp al,0dh
    jz Tele3Afel
    cmp al,'$'
    jmp tmam_gedan
    hona:
    inc bx
    inc di
    jmp convert2Numbers
    Tele3Afel:
    push bx
    push di
    CheckSourceVal temp4Regs
    pop di
    pop bx
    mov [si],dx
    add si,2
    printhexa dx
    inc bx
    mov di,offset temp4Regs
    jmp convert2Numbers

    tmam_gedan:
    jz el7 
    jmp hona
    el7:
    ENDM CONVERT2REGS

DrawInitialP1 MACRO
push_all
    clear 
    mov_cursor 0400h 
    printmsg  InitialP1
    MOV DI, 0727h
    mov_cursor DI
    MOV CX,0707h
    mov si,offset regval
    mov bx,offset regval2
    add bx,2
    add si,2
    MOV VALUE,-1
    T:
    cmp cl,0
    jz toSendPOINTS
    CALL receive_optional
    cmp  VALUE,-1
    jz toSendPOINTS 
    mov al,VALUE
    mov VALUE,-1
    mov [bx],al
    mov dl,[bx]
    inc bx
    cmp al,0dh
    jnz toSendPOINTS
    dec cl

    ;send
    toSendPOINTS:
    cmp ch,0
    jz final_test
    mov ah,1
    int 16h
    jz T
    mov ah,0
    int 16h
    printchar al
    mov [si],al
    inc si
    mov VALUE,al
    CALL send_optional
    mov VALUE,-1
    cmp al,0dh
    jnz nelly
    dec ch
    ADD DI,0200h
    mov_cursor DI
    final_test:
    cmp cx,0
    Jz barabety
    nelly:
    jmp T
    barabety:
    mov di,offset temp4Regs
    mov bx,offset regval    
    add bx,2
    cmp mainPlayer,1
    JZ TELE3ONE
    mov si,offset ALREG
    mov BP,offset ALREG2
    JMP first_loop
    TELE3ONE:
    mov BP,offset ALREG
    mov SI,offset ALREG2
    first_loop:
    mov al,[bx]
    mov [di],al
    inc bx
    inc di
    cmp al,'$'
    jmp first_loop_out
    HONA_FISRT:    
     
    cmp al,0dh
    jNz first_loop
    MOV al,'$'
    mov [di],al
    mov di,offset temp4Regs 
    
    CheckSourceVal temp4Regs
    MOV [SI],DX  
    ADD SI,2

    jmp first_loop
    first_loop_out:
    jz out_eshat
    jmp HONA_FISRT
    out_eshat:    


    mov di,offset temp4Regs
    mov bx,offset regval2
    add bx,2
    mov si,BP
    first_loop1:
    mov al,[bx]
    mov [di],al
    inc bx
    inc di
    cmp al,'$'
    jmp first_loop_out1
    HONA_FISRT1:
    cmp al,0dh
    jNz first_loop1
    MOV al,'$'
    mov [di],al
    mov di,offset temp4Regs
    CheckSourceVal temp4Regs
    MOV [SI],DX  
    ADD SI,2
    

    jmp first_loop1
    first_loop_out1:
    jz out_eshat1
    jmp HONA_FISRT1
    out_eshat1:
    wait_enter 
pop_all     
ENDM DrawInitialP1

DrawInitialP2 MACRO
    xor player,1
    push_all
    clear 
    mov_cursor 0400h 
    printmsg  InitialP2
    MOV SI, 0827h
    MOV BX, offset ALREG2
    MOV CX,7
    JMP ReadIP2     
    T2:
    JNZ ReadIP2
    JMP LEAVEHAMDY2
    ReadIP2:
    PUSH AX
    PUSH CX
    mov_cursor SI
    readmsg regval
    CheckSourceVal regval+2
    POP CX
    POP AX
    MOV [BX], DX
    ADD SI,0200h
    ADD BX,2
    DEC CX 
    JMP T2
    LEAVEHAMDY2:
    mov_cursor SI
    wait_enter    
 pop_all  
 xor player,1  
ENDM DrawInitialP2