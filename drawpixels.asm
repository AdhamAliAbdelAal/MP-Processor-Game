.model small
draw macro
    local no
    local drawx
    local drawy
    local drawx2
    local drawy2
    int 10h
    mov ax,3
    no:
    int 33h
    and bx,bx
    jz no
    mov ax,0c0fh
    
    push cx
    mov bx,50
    drawx:
    int 10h
    inc cx 
    dec bx
    jnz drawx
    pop cx 
    
    push dx
    mov bx,50
    drawy:
    int 10h
    inc dx 
    dec bx
    jnz drawy
    pop dx
    
    add dx,50
    push cx
    mov bx,50
    drawx2:
    int 10h
    inc cx 
    dec bx
    jnz drawx2
    pop cx
    sub dx,50
    
    add cx,50
    push dx
    mov bx,50
    drawy2:
    int 10h
    inc dx 
    dec bx
    jnz drawy2
    endm draw
.data
.code 
main proc far
    mov ax,@data
    mov ds,ax
    mov ax,13h 
    draw
    draw
    hlt
    main endp
end main