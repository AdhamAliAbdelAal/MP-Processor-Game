FL_screen macro
 push_all
    clear
    clear_buffer
 mov_cursor 0000h    
 printmsg  FL_str1   
    mov_cursor 0832h 
    mov bl, -1
    mov cl, -1
    mov dx, 0
    mov VALUE,-1
    ;---------Loop--------
    FL_main_loop:
    cmp dl,0Dh
    jz CheckkSend
    CALL receive_optional
    cmp VALUE,-1
    jz CheckkSend
    mov al,VALUE
    cmp bl,-1
    jne dont_insert
    mov bl,al
    dont_insert:
    mov dl,VALUE
    mov VALUE,-1

    CheckkSend:
    cmp dh,0Dh
    jz Continue_FL
    mov ah,1
    int 16h
    jz FL_main_loop
    mov ah,0
    int 16h
    
    printchar al
    cmp cl,-1
    jne dont_insert2
    mov cl,al
    dont_insert2:
    mov VALUE,al
    mov dh,VALUE
    CALL send_optional
    mov VALUE,-1

    Continue_FL:
    cmp dx,0d0dh
    jmp Test_FL
    Test_FL:
    jz Out_FL
    jmp FL_main_loop
    Out_FL:

    ;Checks  
    cmp mainPlayer,0
    JE TMAM1
    mov FL2,BL 
    mov FL1,CL
    jmp EXIT5LAS

    TMAM1:
    mov FL1,BL 
    mov FL2,CL
    EXIT5LAS:
    ;wait_enter    
 pop_all
endm FL_screen

FL_screen2 macro ;; Start Screen
 push_all
    clear 
    Text_Mode
    mov_cursor 0400h 
    printmsg  FL_str1
    mov_cursor 0C32h
    readchar FL1
    printchar FL1 
    wait_enter    
 pop_all
endm FL_screen2