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

trytosend2 macro
    LOCAL CONSEND
    LOCAL KML
    LOCAL ENDD
    
    
    push_all
    enter2
    mov si,offset val+2 
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
    ;mov [di],bl
    
    ;inc di
    inc si
    jmp consend
    
endd:
    
    mov dx,3f8h
    mov al,'$'
    out dx,al
    
    resetval2
    
    
    
    pop_all
endm trytosend2 

PRINTREC2 MACRO
    PUSH_ALL
    
    mov ch,y
    mov cl,x
    mov_cursor cx 
     
    mov ah,9
    mov dx,offset other  
    int 21h  
    
    mov ah,9
    mov dx,offset val+2  
    int 21h 
    
    
    add x,8
    mov si,offset val+1
    mov cl,x
    add cl,[si]
    mov x,cl  
    mov ch,y
    mov_cursor cx
    
    get_curpos y,x
    
    resetval2  
    mov_cursor 3090h
    
    POP_ALL
ENDM PRINTREC2    
 
get_curpos macro m,n
    local aa
    local f
    local clr
    local ll
    local l 
    
    push_all
    
    
    
    mov ah,3h
    mov bh,0h
    int 10h
    cmp dh,13h
    je clr 
    
    cmp dl,00h
    jne aa    
    mov m,dh
    jmp f 
aa:
    mov n,00h
    add dh,1
    mov m,dh 
    jmp f   

clr:
    
    
    mov cx,640h
  
    mov_cursor 0000h
    
   
ll:
    mov ah,02h
    mov dl,' '
    int 21h
    loop ll
    
    
    mov_cursor 0100h
    mov cl,80
   
l:
    mov ah,02h
    mov dl,'_'
    int 21h
    loop l
    
    
    mov_cursor 0022h
        
    mov ah, 9
    mov dx,offset chatroom
    int 21h
    
    
    
    
    
    mov n,0h
    mov m,2h
    
f:    

    
    pop_all 
endm get_curpos 

resetval2 MACRO 
    LOCAL LF
    Local a
    PUSH_ALL
        
    mov si,offset val+1
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
    mov si,offset val+2 
    mov [si],al
      
    POP_ALL
ENDM resetval2    



enter2 macro
    push_all
    mov_cursor 1600H    
   
      
    mov ah,0AH
    mov dx,offset val
    int 21h
    
    mov_cursor 1600h
    mov ah,9
    mov dx,offset black  
    int 21h
    
   
    mov ch,y
    mov cl,x
    mov_cursor cx
    
    mov ah,9
    mov dx,offset sendern
    int 21h 
    
   
     
    mov ah,9
    mov dx,offset val+2
    int 21h
     
    add x,8
    mov si,offset val+1
    mov cl,x
    add cl,[si]
    mov x,cl  
    mov ch,y
    mov_cursor cx
    
    get_curpos y,x  
    
    mov_cursor 3090h 
    
    pop_all     
endm enter2




initial macro 

      mov dx,3fbh
      mov al,10000000b
      out dx,al
      
      mov dx,3f8h
      mov al,0ch
      out dx,al 
      
      mov dx,3f9h
      mov al,00h
      out dx,al
      
      mov dx,3fbh
      mov al,00010011b
      out dx,al
      
endm initial 
    






arsm macro
    local ll
    local l
    local lll
    
    
        
    clear
   
   mov_cursor 1500h
   mov cl,80
   
ll:
    mov ah,02h
    mov dl,'_'
    int 21h
    loop ll
    
       
       
     mov_cursor 164bh
    mov ah,9
    mov dx,offset press
    int 21h   
       
    
    mov_cursor 174bh
    mov ah,9
    mov dx,offset ent
    int 21h
     
    
    mov_cursor 1800h
    mov cl,80
   
l:
    mov ah,02h
    mov dl,'_'
    int 21h
    loop l  
    
     
    
    mov_cursor 0100h
    mov cl,80
lll:
    mov ah,02h
    mov dl,'_'
    int 21h
    loop lll
    
    mov_cursor 0022h
        
    mov ah, 9
    mov dx,offset chatroom
    int 21h
   
endm arsm 



chatt macro    
local rec
local contrec
local atb3    
local key
local send
local nt
local abd2
local exit

PUSH_ALL   
   
   
    arsm  
   
   
   
  
  
  
  
  
  
   mov_cursor 3090h
   
  
  
  
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
    mov si,offset val+1 
    mov cx,[si]
    inc cl
    mov ch,0 
    mov [si],cl      
    add si,cx
    mov [si],al
    
    
           

    jmp rec

atb3:
             
     PRINTREC2
  
    
     
    
key:
   
    
    mov ah,01
    int 16h
    jnz send
    jmp rec  
    
    
    
send:
    
    mov ah,0         
    int 16h
    ;mov bl,al
    cmp al,13
    je abd2
    cmp al,27
    je nt
   
    jmp rec
    
nt:
    jmp exit    
    
abd2:
   
    trytosend2
    jmp rec    

exit:

    pop_all
     
endm chatt