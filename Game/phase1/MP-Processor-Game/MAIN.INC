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
;;**************************** 
start_screen macro                     ;; Start Screen 
 push_all  
    mov_cursor 0000h  
    printmsg  GAME_Start_STR  
    mov_cursor 082ch 
    readmsg  player_name 
    mov_cursor 0b33h 
    readmsg  STR_Point 
    read_number STR_Point+2,POINT 
     
    wait_enter 
     clear     
    mov_cursor 0000h  
    printmsg GAME_Start2_STR 
    mov_cursor 082ch 
    readmsg  player_name2 
    mov_cursor 0b33h 
    readmsg  STR_Point2 
    read_number STR_Point2+2,POINT2   
    wait_enter
    
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
;;**************************** 
main_screen macro                     ;; Main Screen 
     push_all          
     mov_cursor 0000h 
    printmsg  GAME_Main_STR
    
    loop_mian:
       
    mov ah,0
    int 16h
    cmp ah,3bh
    jz f1
    cmp ah,3ch
    jz  f2_near
    cmp ah,01h 
    jz ex 
  
 jmp  loop_mian  
    ex:
        hlt 
    f2_near:
    jmp  f2
    f1:  
   
       CMP begin_nof,0
       jnz f1_second_line
       mov_cursor 1600H
       printmsg F1_str 
       printmsg player_name2+2 
       lea di, F1_STR 
       mov pointer,di
       inc begin_nof
       jmp loop_mian  
       
    f1_second_line:  
    
        CMP begin_nof,1
       jnz f1_more_lines
       mov_cursor 1700H
       printmsg F1_str
       printmsg player_name2+2 
       lea di, F1_STR 
       mov pointer,di
       inc begin_nof  
       
       jmp loop_mian
      
    f1_more_lines:
         
        mov_cursor 1600H 
        printmsg   CLEAR_LINE
        mov_cursor 1600H 
        display_string_off pointer
        printmsg player_name2+2
        mov_cursor 1700H 
        printmsg   CLEAR_LINE
        mov_cursor 1700H
        printmsg F1_str
        printmsg player_name2+2  
        lea di, F1_STR 
        mov pointer,di
        jmp loop_mian
     
    f2:
       SelectLevel
       FL_screen
       FL_screen2
       jmp ex_eslam
       ;CMP begin_nof,0
       ;jnz f2_second_line
       ;mov_cursor 1600H
       ;printmsg F2_STR 
       ;printmsg player_name2+2 
       ;lea di, F2_STR 
       ;mov pointer,di
       ;inc begin_nof
       ;jmp loop_mian  
       
    f2_second_line:
        CMP begin_nof,1
       jnz f2_more_lines
       mov_cursor 1700H
       printmsg F2_STR 
       printmsg player_name2+2 
       lea di, F2_STR 
       mov pointer,di
       inc begin_nof
       jmp loop_mian
      
    f2_more_lines: 
        mov_cursor 1600H 
        printmsg   CLEAR_LINE 
        mov_cursor 1600H 
        display_string_off pointer 
        printmsg player_name2+2 
        mov_cursor 1700H 
        printmsg   CLEAR_LINE
        mov_cursor 1700H
        printmsg F2_STR   
        printmsg player_name2+2
        lea di, F2_STR 
        mov pointer,di
    
   jmp loop_mian
   ex_eslam:  
 pop_all            
endm main_screen

SelectLevel MACRO
    push_all
    clear 
    mov_cursor 0400h 
    printmsg  level_selection 
    mov_cursor 0c35h
    readchar level
    printchar level 
    wait_enter    
 pop_all 
ENDM SelectLevel

DrawInitialP1 MACRO
     push_all
    clear 
    mov_cursor 0400h 
    printmsg  InitialP1
    MOV SI, 0827h
    MOV BX, offset ALREG
    MOV CX,7
    JMP ReadIP1     
    T:
    JNZ ReadIP1
    JMP LEAVEHAMDY
    ReadIP1:
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
    JMP T
    LEAVEHAMDY:
    mov_cursor SI
    wait_enter    
 pop_all     
ENDM DrawInitialP1

DrawInitialP2 MACRO
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
ENDM DrawInitialP2