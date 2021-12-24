;----------DETECT Instruction Half Register--------

checkInsruction05 macro ins
    PUSHF
    checkINSEQUALITY ins,mov_str
    jnz Check_Add05
    POPF
    mov [bx],dl 
    jmp FoundInstruction05

    Check_Add05:
    checkINSEQUALITY ins,add_str
    jnz Check_ADC05
    POPF
    add [bx],dl 
    jmp FoundInstruction05

    Check_ADC05:
    checkINSEQUALITY ins,adc_str
    jnz Check_SUB05
    POPF
    adc [bx],dl 
    jmp FoundInstruction05

    Check_SUB05:
    checkINSEQUALITY ins,sub_str
    jnz Check_SBB05
    POPF
    sub [bx],dl 
    jmp FoundInstruction05

    Check_SBB05:
    checkINSEQUALITY ins,sbb_str
    jnz Check_AND05
    POPF
    sbb [bx],dl 
    jmp FoundInstruction05

    Check_AND05:
    checkINSEQUALITY ins,and_str
    jnz Check_MUL05
    POPF
    and [bx],dl 
    jmp FoundInstruction05

    Check_MUL05:
    checkINSEQUALITY ins,mul_str
    jnz Check_DIV05
    POPF
    mov al,ALREG
    mul dl
    mov AXREG,ax 
    jmp FoundInstruction05
    
    Check_DIV05:
    checkINSEQUALITY ins,div_str
    jnz Check_XOR05
    POPF
    mov ax,word ptr ALREG
    div dl
    mov AXREG,ax 
    jmp FoundInstruction05

    Check_XOR05:
    checkINSEQUALITY ins,xor_str
    jnz Check_SHR05
    POPF
    mov cl,dl
    mov al,[bx]
    xor al,cl
    mov [bx],al
    jmp FoundInstruction05

    Check_SHR05:
    checkINSEQUALITY ins,shr_str
    jnz Check_SHL05
    POPF
    mov cl,dl
    mov al,[bx]
    shr al,cl
    mov [bx],al 
    jmp FoundInstruction05

    Check_SHL05:
    checkINSEQUALITY ins,shl_str
    jnz Check_SAR05
    POPF
    mov cl,dl
    mov al,[bx]
    shl al,cl
    mov [bx],al 
    jmp FoundInstruction05

    Check_SAR05:
    checkINSEQUALITY ins,sar_str
    jnz Check_CLC05
    POPF
    mov cl,dl
    mov al,[bx]
    sar al,cl
    mov [bx],al 
    jmp FoundInstruction05

    Check_CLC05:
    checkINSEQUALITY ins,clc_str
    jnz Check_ROR05
    POPF 
    CLC
    jmp FoundInstruction05

    Check_ROR05:
    checkINSEQUALITY ins,ror_str
    jnz Check_RCL05
    POPF
    mov cl,dl
    mov al,[bx]
    ror al,cl
    mov [bx],al 
    jmp FoundInstruction05

    Check_RCL05:
    checkINSEQUALITY ins,rcl_str
    jnz Check_RCR05
    POPF
    mov cl,dl
    mov al,[bx]
    rcl al,cl
    mov [bx],al
    jmp FoundInstruction05

    Check_RCR05:
    checkINSEQUALITY ins,rcr_str
    jnz Check_ROL05
    POPF
    mov cl,dl
    mov al,[bx]
    rcr al,cl
    mov [bx],al
    jmp FoundInstruction05

    Check_ROL05:
    checkINSEQUALITY ins,rol_str
    jnz Check_INC05
    POPF
    mov cl,dl
    mov al,[bx]
    rol al,cl
    mov [bx],al
    jmp FoundInstruction05

    Check_INC05:
    checkINSEQUALITY ins,inc_str
    jnz Check_DEC05
    POPF
    MOV AL,[BX]
    inc AL
    MOV [BX],AL    
    jmp FoundInstruction05

    Check_DEC05:
    checkINSEQUALITY ins,dec_str
    jnz FoundInstruction05
    POPF
    MOV AL,[BX]
    dec AL
    MOV [BX],AL   
    jmp FoundInstruction05
    FoundInstruction05:
endm checkInsruction05
