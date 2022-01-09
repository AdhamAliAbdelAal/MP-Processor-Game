include utility.inc
;;;;;;;;;;;;;;;IN - GAME;;;;;;;;;;;;
trytosend macro
    LOCAL CONSEND
    LOCAL KML
    LOCAL ENDD
    
    
    push_all
    enter
    mov si,offset valg+2 
    mov cl,'$'
      
consend:              
    mov dx,3fdh
kml:
    in al,dx                                        
    test al,00100000b
    jz kml
         
    cmp [si],cl
    je endd    
    mov dx,3f8h
    mov al,[si]
    out dx,al 
    
    mov bl,[si]
    mov [di],bl
    
    inc di
    inc si
    jmp consend
    
endd:   


   
    
    mov dx,3f8h
    mov al,'$'
    out dx,al
     
  
    
    
    ;clear_buffer 
     
    resetval
    
    
    
    pop_all
endm trytosend 

PRINTREC MACRO
    PUSH_ALL
    
    ;MOV_CURSOR 1600h
    
    ;mov ah,9
    ;mov dx,offset black  
    ;int 21h
    
    blacked 320,183,0,175 
   
    mov_cursor 1600h
     
    mov ah,9
    mov dx,offset other  
    int 21h  
    
    mov ah,9
    mov dx,offset valg+2  
    int 21h 
    
    
    resetval  
    ;mov_cursor 3090h
    
    POP_ALL
ENDM PRINTREC    


resetval MACRO 
    LOCAL LF
    Local a
    PUSH_ALL
        
    mov si,offset valg+1
    mov cl,[si]
    mov ch,0
    mov [si],ch
    mov al,'$'
    cmp cl,0
    je a
LF:    
    inc si
    
    mov [si],al
    dec cx
    jnz LF
a:   
    mov si,offset valg+2 
    mov [si],al
      
    POP_ALL
ENDM resetval    



enter macro
    push_all
    mov_cursor 1800H    
   
      
    mov ah,0AH
    mov dx,offset valg
    int 21h
    
    ;mov_cursor 1800h
    
    ;mov ah,9
    ;mov dx,offset black
    ;int 21h
    blacked 320,199,0,191  
    
    
    
    ;mov_cursor 1700h
    
    ;mov ah,9
    ;mov dx,offset black
    ;int 21h
    blacked 320,191,0,183  
   
   
    mov_cursor 1700h
    
    mov ah,9
    mov dx,offset sendern
    int 21h 
    
   
     
    mov ah,9
    mov dx,offset valg+2
    int 21h
     
    ;mov_cursor 3090h 
    
    pop_all     
endm enter
    


game_chat macro
local abd2
local send
local key
local atb3
local contrec
local rec
local k
local exiit

initial
 
rec:        
    mov dx,3fdh
    in al,dx
    test al,1
    jnz contrec
    jmp key
      
contrec:
    mov dx,03f8h
    in al,dx
    cmp al,'$'
    je atb3
   
    
    mov cx,0      
    mov si,offset valg+1 
    mov cx,[si]
    inc cl
    mov ch,0 
    mov [si],cl      
    add si,cx
    mov [si],al
    
    
           

    jmp rec

atb3:

     PRINTREC
  
    
     
    
key:
   
    
    mov ah,01
    int 16h 
    jnz send
    jmp rec  
    
    
    
send:
    
    mov ah,0         
    int 16h
    cmp al,13
    je abd2
    cmp al,27
    je k
   
    jmp rec
k:   
    jmp exiit     
    
abd2:
   
    trytosend
    jmp rec   

exiit:


endm game_chat