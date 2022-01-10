.model huge        
;;*****************************            
push_all macro                  ;; push all
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push bp
    push sp
endm push_all   
;;****************************  
pop_all macro                  ;; pop all
    pop sp
    pop bp
    pop di
    pop si
    pop dx
    pop cx
    pop bx 
    pop ax 
endm pop_all
;;***************************
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
;;****************************  
read_string macro mystring      ;; Read sting 
     push_all
mov ah,0AH
mov dx,offset mystring
int 21h 
pop_all
endm read_string
 
;;****************************
display_string macro mystring   ;; Display sting
    push_all 
mov ah,09H
mov dx,offset mystring
int 21h
pop_all
endm display_string    
;;****************************
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
wait_enter macro                     ;; Wait enter  
    push_all
  Enter:
    mov ah,0
    int 16h
    cmp ah,1ch
  jnz Enter  
pop_all                       
endm wait_enter  
;;****************************  
mov_cursor macro num       ;; Move Cursor       
     push_all
mov ah,2 
mov bx,0
mov dx,num
int 10h    
pop_all
endm mov_cursor   

;;**************************** 
start_screen macro                     ;; Start Screen
 push_all 
    mov_cursor 0000h 
    display_string  GAME_Start_STR 
    mov_cursor 062ch
    read_string  player_name
    mov_cursor 0933h
    read_num Point
    mov_cursor 0C2Dh
    read_string  player_name2
    mov_cursor 0F34h
    read_num Point2  
    wait_enter    
 pop_all
endm start_screen   
;;**************************** 
main_screen macro                     ;; Main Screen 
     push_all          
     mov_cursor 0000h 
    display_string  GAME_Main_STR
    
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
       display_string F1_str 
       display_string player_name2+2 
       lea di, F1_STR 
       mov pointer,di
       inc begin_nof
       jmp loop_mian  
       
    f1_second_line:  
    
        CMP begin_nof,1
       jnz f1_more_lines
       mov_cursor 1700H
       display_string F1_str
       display_string player_name2+2 
       lea di, F1_STR 
       mov pointer,di
       inc begin_nof  
       
       jmp loop_mian
      
    f1_more_lines:
         
        mov_cursor 1600H 
        display_string   CLEAR_LINE
        mov_cursor 1600H 
        display_string_off pointer
        display_string player_name2+2
        mov_cursor 1700H 
        display_string   CLEAR_LINE
        mov_cursor 1700H
        display_string F1_str
        display_string player_name2+2  
        lea di, F1_STR 
        mov pointer,di
        jmp loop_mian
     
    f2:
       
       CMP begin_nof,0
       jnz f2_second_line
       mov_cursor 1600H
       display_string F2_STR 
       display_string player_name2+2 
       lea di, F2_STR 
       mov pointer,di
       inc begin_nof
       jmp loop_mian  
       
    f2_second_line:
        CMP begin_nof,1
       jnz f2_more_lines
       mov_cursor 1700H
       display_string F2_STR 
       display_string player_name2+2 
       lea di, F2_STR 
       mov pointer,di
       inc begin_nof
       jmp loop_mian
      
    f2_more_lines: 
        mov_cursor 1600H 
        display_string   CLEAR_LINE 
        mov_cursor 1600H 
        display_string_off pointer 
        display_string player_name2+2 
        mov_cursor 1700H 
        display_string   CLEAR_LINE
        mov_cursor 1700H
        display_string F2_STR   
        display_string player_name2+2
        lea di, F2_STR 
        mov pointer,di
    
   jmp loop_mian
      
 pop_all            
endm main_screen  
;;**************************** 
.stack 64
.data  
         

pointer dw ?   
GAME_Main_STR  db   '        ',0ah,0dh
    DB   '                ====================================================',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh                                        
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||--------------------------------------------------||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||            To Start chatting press F1            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||            To start the game press F2            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||            To end the program press ESC          ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '                ====================================================',0ah,0dh  
    db   '                                                                    ',0ah,0dh     
    db   '                                                                    ',0ah,0dh
    db   '                                                                    ',0ah,0dh  
    DB   80 DUP('-'),'$',0ah,0dh  
    DB   '$',0ah,0dh 
           
GAME_Start_STR  db   '        ',0ah,0dh
    DB   '                ====================================================',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh                                        
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||--------------------------------------------------||',0ah,0dh 
    DB   '               ||  Enter your First Player:                        ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh      
    DB   '               ||  Intial Points for First Player:                 ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||  Enter your Second Player:                       ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||  Intial Points for Second Player:                ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh  
    DB   '               ||               Press Enter key to continue        ||',0ah,0dh
    DB   '               ||               * MAX Name 15 characters *         ||',0ah,0dh   
    DB   '                ====================================================',0ah,0dh  
    db   '                                                                    ',0ah,0dh     
    db   '                                                                    ',0ah,0dh
    DB   '$',0ah,0dh 
      
msg_name db 9,9,9,"Enter your name:" ,10,13," $"
msg_point db 9,9,9,"intial points:",10,13," $"
msg_keyEnter db 9,9,9,"Press enter key to continue $"


Point db ?
Point2 db ?  
player_name db 15,?,15 dup('$') 
player_name2 db 15,?,15 dup('$') 
newline db 10,13,'$' 
tab db 9,9,9,'$'      
    
    
emptysttr db "$"    
ClEAR_LINE    DB 80 DUP(' '),'$'
F1_STR  DB '-You send a chat invitation to ','$'
F2_STR  DB '-You send a game invitation to ','$'

get1_STR  DB 'Sent a chat invitation tO you ','$'
get2_STR  DB 'Sent a game invitation tO you ','$'


begin_nof db 0      
notication db 80 DUP('$'),'$'


.code
main proc far
mov AX,@DATA
mov DS,AX   
                                                               
                                                               
    ;;;;;;;;;;;;;;;;;;;;;;;;;;; first screen (Defining Usernames) 
    clear      
    start_screen   
                                 
    ;;;;;;;;;;;;;;;;;;;;;;;;;;; second screen (Main Screen) 
      clear     
    main_screen
                   
    exit:
hlt
main endp 
end main

