.model small 
read_num macro mydata  ;;Read num     
    PUSHA 
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
     POPA
endm read_num 
;;****************************
read_string macro mystring      ;; Read sting 
     PUSHA
mov ah,0AH
mov dx,offset mystring
int 21h 
POPA
endm read_string
 
;;****************************
display_string macro mystring   ;; Display sting
    PUSHA 
mov ah,09H
mov dx,offset mystring
int 21h
POPA
endm display_string    
;;****************************
display_string_off macro mystring   ;; Display offset sting
    PUSHA 
mov ah,09H
mov dx, mystring
int 21h
POPA
endm display_string
;;**************************** 
clear macro                     ;; Clear string 
     PUSHA
    mov ax,0600h
    mov bh,07
    mov cx,0
    mov dx,184FH
    int 10h  
    POPA
endm clear  
;;****************************   
wait_enter macro                     ;; Wait enter  
     PUSHA
  Enter:
   mov ah,0
int 16h
cmp ah,1ch
jnz Enter  
POPA                       
endm wait_enter  
;;****************************  
mov_cursor macro num       ;; Move Cursor       
     PUSHA
mov ah,2 
mov bx,0
mov dx,num
int 10h    
POPA
endm mov_cursor     
;;**************************** 
main_screen macro                     ;; Main Screen
     PUSHA
    loop_mian:
       
    mov ah,0
    int 16h
    cmp ah,3dh
    jz f1
    cmp ah,3ch
    jz f2
    cmp ah,01h 
    jz exit
  
 jmp  loop_mian  
    f1:  
   
       CMP begin_nof,0
       jnz f1_second_line
       mov_cursor 1500H
       display_string F1_str 
       display_string player_name2 
       lea di, F1_STR 
       mov pointer,di
       inc begin_nof
       jmp loop_mian  
       
    f1_second_line:  
    
        CMP begin_nof,1
       jnz f1_more_lines
       mov_cursor 1600H
       display_string F1_str
       display_string player_name2  
       lea di, F1_STR 
       mov pointer,di
       inc begin_nof  
       
       jmp loop_mian
      
    f1_more_lines:
         
        mov_cursor 1500H 
        display_string   CLEAR_LINE
        mov_cursor 1500H 
        display_string_off pointer
        display_string player_name2
        mov_cursor 1600H 
        display_string   CLEAR_LINE
        mov_cursor 1600H
        display_string F1_str
        display_string player_name2  
        lea di, F1_STR 
        mov pointer,di
        jmp loop_mian
        
    f2:
       
       CMP begin_nof,0
       jnz f2_second_line
       mov_cursor 1500H
       display_string F2_STR 
       display_string player_name2 
       lea di, F2_STR 
       mov pointer,di
       inc begin_nof
       jmp loop_mian  
       
    f2_second_line:
        CMP begin_nof,1
       jnz f2_more_lines
       mov_cursor 1600H
       display_string F2_STR 
       display_string player_name2 
       lea di, F2_STR 
       mov pointer,di
       inc begin_nof
       jmp loop_mian
      
    f2_more_lines: 
        mov_cursor 1500H 
        display_string   CLEAR_LINE 
        mov_cursor 1500H 
        display_string_off pointer 
        display_string player_name2 
        mov_cursor 1600H 
        display_string   CLEAR_LINE
        mov_cursor 1600H
        display_string F2_STR   
        display_string player_name2
        lea di, F2_STR 
        mov pointer,di
   jmp loop_mian
      
 POPA             
endm main_screen  
;;**************************** 
.stack 64
.data  
         

pointer dw ?        
         
msg_name db "please enter your nanme:" ,10,13," $"
msg_point db "intial points",10,13," $"
msg_keyEnter db "Press enter key to continue $"
msg_f1 db 9,9,9,"To start chatting press F1" ,10,13,10,13," $"
msg_f2  db 9,9,9,"To start the game press F2" ,10,13,10,13," $"
mse_esc  db 9,9,9,"To end the program press ESC" ,10,13,10,13," $" 


Point db ?  
player_name db 15,?,15 dup('$') 
newline db 10,13,'$' 
tab db 9,'$'      
    
    
emptysttr db "$"    
DASH    DB 80 DUP('-'),'$'  
ClEAR_LINE    DB 80 DUP(' '),'$'
F1_STR  DB '-You send a chat invitation to ','$'
F2_STR  DB '-You send a game invitation to ','$'

get1_STR  DB 'Sent a chat invitation tO you ','$'
get2_STR  DB 'Sent a game invitation tO you ','$'

player_name2 db 'Fathi','$' 
begin_nof db 0      
notication db 80 DUP('$'),'$'


.code
main proc far
mov AX,@DATA
mov DS,AX   

 ;;;;;;;;;;;;;;;;;;;;;;;;;;; first screen (Defining Usernames)      
    display_string msg_name       
    read_string  player_name
    display_string  newline
    display_string msg_point
    read_num Point      
    display_string  newline
    display_string msg_keyEnter 
    wait_enter
    clear                                    
    ;;;;;;;;;;;;;;;;;;;;;;;;;;; second screen (Main Screen)   
    mov_cursor 0700h 
    display_string msg_f1 
    display_string  msg_f2
    display_string  mse_esc
    mov_cursor 1300h    
    display_string DASH  
    
    main_screen
   
    exit:
hlt
main endp 
end main

