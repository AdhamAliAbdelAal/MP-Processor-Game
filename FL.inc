FL_screen macro
    local FL_main_loop
    local CheckkSend
    local dont_insert
    local Continue_FL
    local dont_insert2
    local Test_FL
    local Out_FL
    local TMAM1
    local EXIT5LAS 
 push_all
 Text_Mode
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

FL_P3 macro
LOCAL mp22
LOCAL read_char22
local y7otfelawal
local y5lasshukrn 
push_all
    Text_Mode
    clear
    clear_buffer
 mov_cursor 0000h    
 printmsg  FL_str1   
    mov_cursor 0832h
    mov al,mainPlayer
    cmp al,p3_choose
    je mp22
    CALL receive
    mov al,VALUE
    mov bl,al
    jmp read_char22
    mp22:
    mov ah,0
    int 16h
    mov VALUE,al
    mov cl,al
    CALL send
    read_char22:
    cmp mainPlayer,0
    je y7otfelawal 
    mov FL2,al
    printchar FL2
    jmp y5lasshukrn
    y7otfelawal:
    mov FL2,al
    printchar FL2
    y5lasshukrn:
    wait_enter 
pop_all
endm FL_P3