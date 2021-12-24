;-----------DETECT REGISTER DESTINATION---------
CheckDestination macro des
    checkEQUALITY des,ax_str
    jnz Check_BX
    mov bx,offset AXREG 
    jmp FoundDestination

    Check_BX:
    checkEQUALITY des,bx_str
    jnz Check_CX
    mov bx,offset BXREG 
    jmp FoundDestination

    Check_CX:
    checkEQUALITY des,cx_str
    jnz Check_DX
    mov bx,offset CXREG 
    jmp FoundDestination

    Check_DX:
    checkEQUALITY des,dx_str
    jnz Check_SI
    mov bx,offset DXREG 
    jmp FoundDestination

    Check_SI:
    checkEQUALITY des,si_str
    jnz Check_DI
    mov bx,offset SIREG 
    jmp FoundDestination

    Check_DI:
    checkEQUALITY des,di_str
    jnz Check_BP
    mov bx,offset DIREG 
    jmp FoundDestination

    Check_BP:
    checkEQUALITY des,bp_str
    jnz Check_AL
    mov bx,offset BPREG 
    jmp FoundDestination
    
    Check_AL:
    checkEQUALITY des,al_str
    jnz Check_AH
    mov bx,offset ALREG 
    jmp FoundDestination
    
     Check_AH:
    checkEQUALITY des,ah_str
    jnz Check_BL
    mov bx,offset AHREG 
    jmp FoundDestination

    Check_BL:
    checkEQUALITY des,bl_str
    jnz Check_BH  
    mov bx,offset BLREG 
    jmp FoundDestination

    Check_BH:
    checkEQUALITY des,bh_str
    jnz Check_CL
    mov bx,offset BHREG 
    jmp FoundDestination

    Check_CL:
    checkEQUALITY des,cl_str
    jnz Check_CH
    mov bx,offset CLREG 
    jmp FoundDestination

    Check_CH:
    checkEQUALITY des,ch_str
    jnz Check_DL
    mov bx,offset CHREG 
    jmp FoundDestination

    Check_DL:
    checkEQUALITY des,dl_str
    jnz Check_DH
    mov bx,offset DLREG 
    jmp FoundDestination

    Check_DH:
    checkEQUALITY des,dh_str
    jnz FoundDestination
    mov bx,offset DHREG 
    jmp FoundDestination

    FoundDestination:
endm CheckDestination