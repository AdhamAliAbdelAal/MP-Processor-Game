;-----------DETECT REGISTER DESTINATION---------
CheckDestination macro des
    local Check_BX
    local Check_CX
    local Check_DX
    local Check_SI
    local Check_DI
    local Check_BP
    local Check_AL
    local Check_AH
    local Check_BL
    local Check_BH
    local Check_CL
    local Check_CH
    local Check_DL
    local Check_DH
    local FoundDestination
    checkEQUALITY des,ax_str
    jnz Check_BX
    checkPlayer_des AXREG,AXREG2
    mov checkDesSize,2 
    jmp FoundDestination

    Check_BX:
    checkEQUALITY des,bx_str
    jnz Check_CX
    checkPlayer_des BXREG,BXREG2
    mov checkDesSize,2 
    jmp FoundDestination

    Check_CX:
    checkEQUALITY des,cx_str
    jnz Check_DX
    checkPlayer_des CXREG,CXREG2
    mov checkDesSize,2 
    jmp FoundDestination

    Check_DX:
    checkEQUALITY des,dx_str
    jnz Check_SI
    checkPlayer_des DXREG,DXREG2
    mov checkDesSize,2 
    jmp FoundDestination

    Check_SI:
    checkEQUALITY des,si_str
    jnz Check_DI
    checkPlayer_des SIREG,SIREG2
    mov checkDesSize,2 
    jmp FoundDestination

    Check_DI:
    checkEQUALITY des,di_str
    jnz Check_BP
    checkPlayer_des DIREG,DIREG2
    mov checkDesSize,2 
    jmp FoundDestination

    Check_BP:
    checkEQUALITY des,bp_str
    jnz Check_AL
    checkPlayer_des BPREG,BPREG2
    mov checkDesSize,2 
    jmp FoundDestination
    
    Check_AL:
    checkEQUALITY des,al_str
    jnz Check_AH
    checkPlayer_des ALREG,ALREG2
    mov checkDesSize,1 
    jmp FoundDestination
    
    Check_AH:
    checkEQUALITY des,ah_str
    jnz Check_BL
    checkPlayer_des AHREG,AHREG2
    mov checkDesSize,1 
    jmp FoundDestination

    Check_BL:
    checkEQUALITY des,bl_str
    jnz Check_BH  
    checkPlayer_des BLREG,BLREG2
    mov checkDesSize,1 
    jmp FoundDestination

    Check_BH:
    checkEQUALITY des,bh_str
    jnz Check_CL
    checkPlayer_des BHREG,BHREG2
    mov checkDesSize,1 
    jmp FoundDestination

    Check_CL:
    checkEQUALITY des,cl_str
    jnz Check_CH
    checkPlayer_des CLREG,CLREG2
    mov checkDesSize,1 
    jmp FoundDestination

    Check_CH:
    checkEQUALITY des,ch_str
    jnz Check_DL
    checkPlayer_des CHREG,CHREG2
    mov checkDesSize,1 
    jmp FoundDestination

    Check_DL:
    checkEQUALITY des,dl_str
    jnz Check_DH
    checkPlayer_des DLREG,DLREG2
    mov checkDesSize,1 
    jmp FoundDestination

    Check_DH:
    checkEQUALITY des,dh_str
    printmsg adham
    jnz FoundDestination
    checkPlayer_des DHREG,DHREG2
    mov checkDesSize,1 
    jmp FoundDestination

    FoundDestination:
endm CheckDestination 

;-----------DETECT DIRECT DESTINATION---------
DirectDestination macro des
    local harf
    local Dexite
    checkPlayer_des memory,memory2
    mov dh,0
    mov dl,des
    sub dl,30h
    cmp dl,9
    ja harf
    add bx,dx
    jmp Dexite
    harf:
    sub dl,7
    add bx,dx
    Dexite: 
    mov checkDesSize,0
endm DirectDestination
;-----------DETECT INDIRECT DESTINATION---------    
RegIndirect macro des
    CheckDestination des
    mov ax,[bx]
    checkPlayer_des memory,memory2
    add bx,ax
    mov checkDesSize,0    
endm RegIndirect

BasedRelativeDES macro des
    CheckDestination des
    mov ax,[bx]
    DirectDestination des+3
    add bx,ax
    mov checkDesSize,0    
endm BasedRelativeDES