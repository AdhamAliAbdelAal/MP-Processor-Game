.model small

;----------------PRINT MESSAGE-------------------

printmsg macro msg
    mov ah,9
    mov dx,offset msg
    int 21h
endm printmsg

;--------------READ MESSAGE---------------------

readmsg macro msg
    mov ah,0ah
    mov dx,offset msg
    int 21h
endm readmsg

;-----------------checkEQUALITY-------------------

checkEQUALITY MACRO S1,S2 
    MOV CX, 2 
    MOV SI, offset S1  
    MOV DI, offset S2 
    REPE CMPSB     
endm checkEQUALITY

;-----------------checkInstructionEQUALITY-------------------

checkINSEQUALITY MACRO S1,S2 
    MOV CX, 3 
    MOV SI, offset S1  
    MOV DI, offset S2 
    REPE CMPSB     
endm checkINSEQUALITY

;---------------DETECT REGISTER DESTINATION--------------

CheckDestination macro des
    checkEQUALITY des,ax_str
    cmp cx,0
    jnz Check_BX
    mov bx,offset AXREG 
    jmp FoundDestination

    Check_BX:
    checkEQUALITY des,bx_str
    cmp cx,0
    jnz Check_CX
    mov bx,offset BXREG 
    jmp FoundDestination

    Check_CX:
    checkEQUALITY des,cx_str
    cmp cx,0
    jnz Check_DX
    mov bx,offset CXREG 
    jmp FoundDestination

    Check_DX:
    checkEQUALITY des,dx_str
    cmp cx,0
    jnz Check_SI
    mov bx,offset DXREG 
    jmp FoundDestination

    Check_SI:
    checkEQUALITY des,si_str
    cmp cx,0
    jnz Check_DI
    mov bx,offset SIREG 
    jmp FoundDestination

    Check_DI:
    checkEQUALITY des,di_str
    cmp cx,0
    jnz Check_BP
    mov bx,offset DIREG 
    jmp FoundDestination

    Check_BP:
    checkEQUALITY des,bp_str
    cmp cx,0
    jnz FoundDestination
    mov bx,offset DIREG 
    jmp FoundDestination

    Check_AL:
    checkEQUALITY des,al_str
    cmp cx,0
    jnz Check_AH
    mov bx,offset ALREG 
    jmp FoundDestination

    Check_AH:
    checkEQUALITY des,ah_str
    cmp cx,0
    jnz Check_BL
    mov bx,offset AHREG 
    jmp FoundDestination

    Check_BL:
    checkEQUALITY des,bl_str
    cmp cx,0
    jnz Check_BH
    mov bx,offset BLREG 
    jmp FoundDestination

    Check_BH:
    checkEQUALITY des,bh_str
    cmp cx,0
    jnz Check_CL
    mov bx,offset BHREG 
    jmp FoundDestination

    Check_CL:
    checkEQUALITY des,cl_str
    cmp cx,0
    jnz Check_CH
    mov bx,offset CLREG 
    jmp FoundDestination

    Check_CH:
    checkEQUALITY des,ch_str
    cmp cx,0
    jnz Check_DL
    mov bx,offset CHREG 
    jmp FoundDestination

    Check_DL:
    checkEQUALITY des,dl_str
    cmp cx,0
    jnz Check_DH
    mov bx,offset DLREG 
    jmp FoundDestination

    Check_DH:
    checkEQUALITY des,ch_str
    cmp cx,0
    jnz FoundDestination
    mov bx,offset DHREG 
    jmp FoundDestination

    FoundDestination:
endm CheckDestination

;---------------DETECT INSTRUCTION--------------

checkInsruction macro ins
    checkINSEQUALITY ins,mov_str
    cmp cx,0
    jnz Check_Add
    mov [bx],dx 
    jmp FoundInstruction

    Check_Add:
    checkINSEQUALITY ins,add_str
    cmp cx,0
    jnz Check_ADC
    add [bx],dx 
    jmp FoundInstruction

    Check_ADC:
    checkINSEQUALITY ins,adc_str
    cmp cx,0
    jnz Check_SUB
    ;we will pop carry flag here
    adc [bx],dx 
    jmp FoundInstruction

    Check_SUB:
    checkINSEQUALITY ins,sub_str
    cmp cx,0
    jnz Check_SBB
    sub [bx],dx 
    jmp FoundInstruction

    Check_SBB:
    checkINSEQUALITY ins,sbb_str
    cmp cx,0
    jnz Check_AND
    ;we will pop carry flag here
    sbb [bx],dx 
    jmp FoundInstruction

    Check_AND:
    checkINSEQUALITY ins,and_str
    cmp cx,0
    jnz Check_MUL
    and [bx],dx 
    jmp FoundInstruction

    Check_MUL:
    checkINSEQUALITY ins,mul_str
    cmp cx,0
    jnz Check_DIV
    mov ax,word ptr ALREG
    mul dx
    mov AXREG,ax
    mov DXREG,dx 
    jmp FoundInstruction
    
    Check_DIV:
    checkINSEQUALITY ins,div_str
    cmp cx,0
    jnz Check_XOR
    mov ax,word ptr ALREG
    div dx
    mov AXREG,ax
    mov DXREG,dx 
    jmp FoundInstruction

    Check_XOR:
    checkINSEQUALITY ins,xor_str
    cmp cx,0
    jnz Check_SHR
    xor [bx],dx 
    jmp FoundInstruction

    Check_SHR:
    checkINSEQUALITY ins,shr_str
    cmp cx,0
    jnz Check_SHL
    mov cl,dl
    shr [bx],cl 
    jmp FoundInstruction

    Check_SHL:
    checkINSEQUALITY ins,shl_str
    cmp cx,0
    jnz Check_SAR
    mov cl,dl
    shl [bx],cl 
    jmp FoundInstruction

    Check_SAR:
    checkINSEQUALITY ins,sar_str
    cmp cx,0
    jnz Check_CLC
    mov cl,dl
    sar [bx],cl 
    jmp FoundInstruction

    Check_CLC:
    checkINSEQUALITY ins,clc_str
    cmp cx,0
    jnz Check_ROR
    ;clear carry flag
    jmp FoundInstruction

    Check_ROR:
    checkINSEQUALITY ins,ror_str
    cmp cx,0
    jnz Check_RCL
    mov cl ,dl
    ror [bx],cl 
    jmp FoundInstruction

    Check_RCL:
    checkINSEQUALITY ins,rcl_str
    cmp cx,0
    jnz Check_RCR
    ;pop carry flag
    mov cl,dl
    rcl [bx],cl 
    jmp FoundInstruction

    Check_RCR:
    checkINSEQUALITY ins,rcr_str
    cmp cx,0
    jnz Check_ROL
    ;pop carry flag
    mov cl,dl
    rcr [bx],cl 
    jmp FoundInstruction

    Check_ROL:
    checkINSEQUALITY ins,rol_str
    cmp cx,0
    jnz Check_INC
    mov cl,dl
    rol [bx],cl 
    jmp FoundInstruction

    Check_INC:
    checkINSEQUALITY ins,inc_str
    cmp cx,0
    jnz Check_DEC
    mov dx,1
    add [bx],dx    
    jmp FoundInstruction

    Check_DEC:
    checkINSEQUALITY ins,dec_str
    cmp cx,0
    jnz FoundInstruction
    mov dx,1
    sub [bx],dx    
    jmp FoundInstruction
    FoundInstruction:
endm checkInsruction

;----------DETECT Instruction Half Register--------

checkInsruction05 macro ins
    checkINSEQUALITY ins,mov_str
    cmp cx,0
    jnz Check_Add05
    mov [bx],dl 
    jmp FoundInstruction05

    Check_Add05:
    checkINSEQUALITY ins,add_str
    cmp cx,0
    jnz Check_Add05
    add [bx],dl 
    jmp FoundInstruction05

    Check_ADC05:
    checkINSEQUALITY ins,adc_str
    cmp cx,0
    jnz Check_SUB05
    ;we will pop carry flag here
    adc [bx],dl 
    jmp FoundInstruction05

    Check_SUB05:
    checkINSEQUALITY ins,sub_str
    cmp cx,0
    jnz Check_SBB05
    sub [bx],dl 
    jmp FoundInstruction05

    Check_SBB05:
    checkINSEQUALITY ins,sbb_str
    cmp cx,0
    jnz Check_AND05
    ;we will pop carry flag here
    sbb [bx],dl 
    jmp FoundInstruction05

    Check_AND05:
    checkINSEQUALITY ins,and_str
    cmp cx,0
    jnz Check_MUL05
    and [bx],dl 
    jmp FoundInstruction05

    Check_MUL05:
    checkINSEQUALITY ins,mul_str
    cmp cx,0
    jnz Check_DIV05
    mov al,ALREG
    mul dl
    mov AXREG,ax 
    jmp FoundInstruction05
    
    Check_DIV05:
    checkINSEQUALITY ins,div_str
    cmp cx,0
    jnz Check_XOR05
    mov ax,word ptr ALREG
    div dl
    mov AXREG,ax 
    jmp FoundInstruction05

    Check_XOR05:
    checkINSEQUALITY ins,xor_str
    cmp cx,0
    jnz Check_SHR05
    xor [bx],dl
    jmp FoundInstruction05

    Check_SHR05:
    checkINSEQUALITY ins,shr_str
    cmp cx,0
    jnz Check_SHL05
    shr [bx],dl 
    jmp FoundInstruction05

    Check_SHL05:
    checkINSEQUALITY ins,shl_str
    cmp cx,0
    jnz Check_SAR05
    mov cl,dl
    shl [bx],cl 
    jmp FoundInstruction05

    Check_SAR05:
    checkINSEQUALITY ins,sar_str
    cmp cx,0
    jnz Check_CLC05
    mov cl,dl
    sar [bx],cl 
    jmp FoundInstruction05

    Check_CLC05:
    checkINSEQUALITY ins,clc_str
    cmp cx,0
    jnz Check_ROR05
    ;clear carry flag
    jmp FoundInstruction05

    Check_ROR05:
    checkINSEQUALITY ins,ror_str
    cmp cx,0
    jnz Check_RCL05
    mov cl,dl
    ror [bx],cl 
    jmp FoundInstruction05

    Check_RCL05:
    checkINSEQUALITY ins,rcl_str
    cmp cx,0
    jnz Check_RCR05
    ;pop carry flag
    mov cl,dl
    rcl [bx],cl 
    jmp FoundInstruction05

    Check_RCR05:
    checkINSEQUALITY ins,rcr_str
    cmp cx,0
    jnz Check_ROL05
    ;pop carry flag
    mov cl,dl
    rcr [bx],cl 
    jmp FoundInstruction05

    Check_ROL05:
    checkINSEQUALITY ins,rol_str
    cmp cx,0
    jnz Check_INC05
    mov cl,dl
    rol [bx],cl 
    jmp FoundInstruction05

    Check_INC05:
    checkINSEQUALITY ins,inc_str
    cmp cx,0
    jnz Check_DEC05
    inc [bx]    
    jmp FoundInstruction05

    Check_DEC05:
    checkINSEQUALITY ins,dec_str
    cmp cx,0
    jnz FoundInstruction05
    dec [bx]   
    jmp FoundInstruction05
    FoundInstruction05:
endm checkInsruction05

;---------------DETECT SOURCE--------------
 
CheckSource MACRO Ins  
    checkEQUALITY ax_str,Ins   
    CMP CX, 0  
    JNZ JumpAX  
    MOV DX, WORD PTR ALREG  
    JMP Found  
    JumpAX:  
      
    checkEQUALITY bx_str,Ins   
    CMP CX, 0  
    JNZ JumpBX  
    MOV DX, WORD PTR BLREG  
    JMP Found  
    JumpBX:  
      
    checkEQUALITY cx_str,Ins   
    CMP CX, 0  
    JNZ JumpCX  
    MOV DX, WORD PTR CLREG  
    JMP Found  
    JumpCX:  
      
    checkEQUALITY dx_str,Ins   
    CMP CX, 0  
    JNZ JumpDX  
    MOV DX, WORD PTR DLREG  
    JMP Found  
    JumpDX: 
     
    checkEQUALITY al_str,Ins   
    CMP CX, 0  
    JNZ JumpAL  
    MOV DL, ALREG  
    JMP Found  
    JumpAL: 
            
    checkEQUALITY ah_str,Ins   
    CMP CX, 0  
    JNZ JumpAH  
    MOV DL, AHREG  
    JMP Found  
    JumpAH: 
     
    checkEQUALITY bl_str,Ins   
    CMP CX, 0  
    JNZ JumpBL  
    MOV DL, BLREG  
    JMP Found  
    JumpBL: 
     
    checkEQUALITY bh_str,Ins   
    CMP CX, 0  
    JNZ JumpBH  
    MOV DL, BHREG  
    JMP Found  
    JumpBH: 
     
    checkEQUALITY cl_str,Ins   
    CMP CX, 0  
    JNZ JumpCL  
    MOV DL, CLREG  
    JMP Found  
    JumpCL: 
     
    checkEQUALITY ch_str,Ins   
    CMP CX, 0  
    JNZ JumpCH  
    MOV DL, CHREG  
    JMP Found  
    JumpCH: 
     
    checkEQUALITY dl_str,Ins   
    CMP CX, 0  
    JNZ JumpDL  
    MOV DL, DLREG  
    JMP Found  
    JumpDL: 
     
    checkEQUALITY dh_str,Ins   
    CMP CX, 0  
    JNZ JumpDH  
    MOV DL, DHREG  
    JMP Found  
    JumpDH: 
     
    checkEQUALITY si_str,Ins   
    CMP CX, 0  
    JNZ JumpSI  
    MOV DX, SIREG  
    JMP Found  
    JumpSI: 
     
    checkEQUALITY di_str,Ins   
    CMP CX, 0  
    JNZ JumpDI  
    MOV DX, DIREG  
    JMP Found  
    JumpDI: 
     
    checkEQUALITY bp_str,Ins   
    CMP CX, 0  
    JNZ JumpBP  
    MOV DX, BPREG  
    JMP Found  
    JumpBP: 
     
    Found: ;EXIT  
endm CheckSource

;---------------DETECT SOURCE (Val)--------------

CheckSourceVal MACRO Ins
    PUSH BX
    MOV DX, 0
    MOV CL, 4
    MOV BX, 0  
    MainLoop:
        MOV CH, BYTE PTR Ins[BX]
        CMP CH, 57
        JNC Str
        SUB CH, 30h
        JMP EXIT
        Str:
            SUB CH, 31h
            CMP CH, 10h
            JNE L1
            MOV CH, 0Ah
            JMP Exit
            L1:
            CMP CH, 11h
            JNE L2
            MOV CH, 0Bh
            JMP Exit
            L2:
            CMP CH, 12h
            JNE L3
            MOV CH, 0Ch
            JMP Exit
            L3:
            CMP CH, 13h
            JNE L4
            MOV CH, 0Dh
            JMP Exit
            L4:
            CMP CH, 14h
            JNE L5
            MOV CH, 0Eh
            JMP Exit
            L5:
            CMP CH, 15h
            JNE L6
            MOV CH, 0Fh
            JMP Exit
            L6:
        Exit:
            ADD DL, CH
        CMP CL, 1
        JZ PreventShift
        SHL DX, 4
        PreventShift:
        INC BX
        DEC CL
    JNZ MainLoop
    POP BX
ENDM CheckSourceVal    

;----------------EXECUTE INSTRUCTION---------------- 

executeInstruction macro input 
CheckDestination input+6
CheckSourceVal input+9
;CheckSource input+9
checkInsruction  input+2
endm executeInstruction

 ;--------------INPUTS-------------------
.data
instruction db 16,?, 16 dup('$') 
newline db 10,13,'$'

;---------------------REGISTERS---------------------

AXREG LABEL WORD 
ALREG db 5h 
AHREG db 10h 
 
BXREG LABEL WORD 
BLREG db 14h 
BHREG db 2h 
 
CXREG LABEL WORD 
CLREG db 8h 
CHREG db 6h 
 
DXREG LABEL WORD 
DLREG db 1h 
DHREG db 34h

SIREG dw ? 
DIREG dw ? 
BPREG dw ?

;------------------INSTRUCTION STRINGS---------------

mov_str db "MOV$"
add_str db "ADD$"
adc_str db "ADC$"
sub_str db "SUB$"
sbb_str db "SBB$"
and_str db "AND$"
mul_str db "MUL$"
div_str db "DIV$"
xor_str db "XOR$"
nop_str db "NOP$" 
shr_str db "SHR$" 
shl_str db "SHL$" 
sar_str db "SAR$" 
clc_str db "CLC$" 
ror_str db "ROR$" 
rcl_str db "RCL$" 
rcr_str db "RCR$" 
rol_str db "ROL$" 
inc_str db "INC$" 
dec_str db "DEC$"

;-------------------REGISTER STRINGS-----------------

ax_str db "AX$" 
al_str db "AL$" 
ah_str db "AH$" 
 
bx_str db "BX$" 
bl_str db "BL$" 
bh_str db "BH$" 
 
cx_str db "CX$" 
cl_str db "CL$" 
ch_str db "CH$" 
 
dx_str db "DX$" 
dl_str db "DL$" 
dh_str db "DH$"

si_str db "SI$"
di_str db "DI$"
bp_str db "BP$"

;----------------------------------------------------
.code
    main proc far
        mov AX,@DATA
        mov DS,AX
        mov ES,AX
        readmsg instruction
        executeInstruction instruction
main endp 
end main