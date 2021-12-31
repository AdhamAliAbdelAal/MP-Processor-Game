;---------------DETECT INSTRUCTION--------------

checkInsruction macro ins 
    checkINSEQUALITY ins,mov_str
    jnz Check_Add
    POPF
    ;printmsg adham
    mov [bx],dx 
    jmp FoundInstruction

    Check_Add:
    checkINSEQUALITY ins,add_str
    jnz Check_ADC
    POPF
    add [bx],dx 
    jmp FoundInstruction

    Check_ADC:
    checkINSEQUALITY ins,adc_str
    jnz Check_SUB
    POPF
    adc [bx],dx 
    jmp FoundInstruction

    Check_SUB:
    checkINSEQUALITY ins,sub_str
    jnz Check_SBB
    POPF
    sub [bx],dx 
    jmp FoundInstruction

    Check_SBB:
    checkINSEQUALITY ins,sbb_str
    jnz Check_AND
    POPF
    sbb [bx],dx 
    jmp FoundInstruction

    Check_AND:
    checkINSEQUALITY ins,and_str
    jnz Check_MUL
    POPF
    and [bx],dx 
    jmp FoundInstruction

    Check_MUL:
    checkINSEQUALITY ins,mul_str
    jnz Check_DIV
    POPF
    mov ax,word ptr ALREG
    mov dx,[bx]
    mul dx 
    cmp player,1
    je pp1               
    mov AXREG2,ax
    mov DXREG2,dx 
    jmp FoundInstruction
    pp1:
    mov AXREG,ax
    mov DXREG,dx
    printhexa AXREG
    jmp FoundInstruction
    
    
    Check_DIV:
    checkINSEQUALITY ins,div_str
    jnz Check_XOR
    POPF
    mov ax,word ptr ALREG  
    mov dx,[bx]
    printhexa DX
    div dx
    cmp player,1
    je pp12               
    mov AXREG2,ax
    mov DXREG2,dx 
    jmp FoundInstruction
    pp12:
    mov AXREG,ax
    mov DXREG,dx
    ;printhexa AXREG
    jmp FoundInstruction 

    Check_XOR:
    checkINSEQUALITY ins,xor_str
    jnz Check_SHR
    POPF
    xor [bx],dx 
    jmp FoundInstruction

    Check_SHR:
    checkINSEQUALITY ins,shr_str
    jnz Check_SHL
    POPF
    mov cl,dl
    mov ax,[bx]
    shr ax,cl
    mov [bx],ax  
    jmp FoundInstruction

    Check_SHL:
    checkINSEQUALITY ins,shl_str
    jnz Check_SAR
    POPF
    mov cl,dl
    mov ax,[bx]
    shl ax,cl
    mov [bx],ax  
    jmp FoundInstruction

    Check_SAR:
    checkINSEQUALITY ins,sar_str
    jnz Check_CLC
    POPF
    mov cl,dl
    mov ax,[bx]
    sar ax,cl
    mov [bx],ax  
    jmp FoundInstruction

    Check_CLC:
    checkINSEQUALITY ins,clc_str
    jnz Check_ROR
    POPF
    CLC
    jmp FoundInstruction

    Check_ROR:
    checkINSEQUALITY ins,ror_str
    jnz Check_RCL
    POPF
    mov cl ,dl
    mov ax,[bx]
    ror ax,cl
    mov [bx],ax  
    jmp FoundInstruction

    Check_RCL:
    checkINSEQUALITY ins,rcl_str
    jnz Check_RCR
    POPF
    mov cl,dl
    mov ax,[bx]
    rcl ax,cl
    mov [bx],ax  
    jmp FoundInstruction

    Check_RCR:
    checkINSEQUALITY ins,rcr_str
    jnz Check_ROL
    POPF
    mov cl,dl
    mov ax,[bx]
    rcr ax,cl
    mov [bx],ax  
    jmp FoundInstruction

    Check_ROL:
    checkINSEQUALITY ins,rol_str
    jnz Check_INC
    POPF
    mov cl,dl
    mov ax,[bx]
    rol ax,cl
    mov [bx],ax  
    jmp FoundInstruction
    
    Check_INC:
    checkINSEQUALITY ins,inc_str
    jnz Check_DEC
    mov dx,1
    add [bx],dx
    POPF    
    jmp FoundInstruction

    Check_DEC:
    checkINSEQUALITY ins,dec_str
    jnz FoundInstruction
    POPF
    mov dx,1
    sub [bx],dx    
    jmp FoundInstruction   
    FoundInstruction:  
    PUSHF
endm checkInsruction

