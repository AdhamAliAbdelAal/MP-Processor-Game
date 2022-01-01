FL_screen macro ;; Start Screen
 push_all
    clear 
    mov_cursor 0400h 
    printmsg  FL_str1 
    mov_cursor 0c37h
    readchar FL2
    printchar FL2 
    wait_enter    
 pop_all
endm FL_screen

FL_screen2 macro ;; Start Screen
 push_all
    clear 
    mov_cursor 0400h 
    printmsg  FL_str2
    mov_cursor 0C37h
    readchar FL1
    printchar FL1 
    wait_enter    
 pop_all
endm FL_screen2