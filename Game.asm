Include des1.inc
include ins1.inc
include ins2.inc
include utility.inc
include src1.inc
include src2.inc
include srcval.inc
include BasRel.inc
.model huge

DetectSourceMode MACRO input
    local Number
    local StartBracket
    local ExitSrcMode
    local DirectMode
    local RegIndirect
    local BasedRelativeMode
    local testHamdy1
    local testHamdy2
    local testHamdy3
    local okHamdy1
    local okHamdy2
    local okHamdy3
    PUSH CX
    MOV CL, BYTE PTR input
    CMP CL, '['
    jmp testHamdy1
    okHamdy1:
    MOV CL, BYTE PTR input+1
    CMP CL, 'I'
    jmp testHamdy2
    okHamdy2:
    CheckSource input ; 1st
    JMP ExitSrcMode
    testHamdy2:
    JC Number
    jmp okHamdy2
    Number:
    CheckSourceVal input ; 2nd
    mov checkSrcSize,0
    JMP ExitSrcMode
    testHamdy1:
    JZ StartBracket
    jmp okHamdy1
    
    StartBracket:
    MOV CL, BYTE PTR input+2
    CMP CL, ']'
    JZ DirectMode 
    MOV CL, BYTE PTR input+3
    CMP CL, ']'
    jmp testHamdy3
    okHamdy3:
    JMP BasedRelativeMode
    
    DirectMode:
    Direct input+1 ; 3rd 
    mov checkSrcSize,0
    JMP ExitSrcMode
    
    testHamdy3:
    JZ RegIndirect
    jmp okHamdy3
    
    
    
    RegIndirect:
    RegisterIndirect input+1 ; 4th 
    mov checkSrcSize,0
    JMP ExitSrcMode
    
    BasedRelativeMode:
    BasedRelative input+1 ; 5th 
    mov checkSrcSize,0
    
    ExitSrcMode:
    POP CX
             
endM DetectSourceMode

;----------------EXECUTE INSTRUCTION---------------- 

executeInstruction macro input
    cmp input+6,'['
    jmp test0
    ok0:
    CheckDestination input+6
    MOV DI,9 
    jmp tosource
    test0:
    jz mshReg
    jmp ok0
    
    mshReg:
    cmp input+8,']'
    jmp test1
    ok1:
    DirectDestination input+7
    MOV DI,10 
    jmp tosource
    test1:
    jnz mshDirect
    jmp ok1
    
    mshDirect:
    cmp input+9,']'
    jmp test2
    ok2:
    RegIndirect input+7
    mov di,11 
    jmp tosource
    test2:
    jnz mshIndirect
    jmp ok2
    
    mshIndirect:
    cmp input+11,']'
    jmp test3
    ok3:
    BasedRelativeDES input+7
    mov di,13
    jmp tosource
    test3:
    jnz tosource
    jmp ok3
            
    tosource:
    cmp di,9
    JMP src0
    oksrc0:
    DetectSourceMode input+9
    jmp insjmp
    src0:
    jnz nextdi0
    jmp oksrc0
    
    nextdi0:
    cmp di,10
    JMP src1
    oksrc1:
    DetectSourceMode input+10
    jmp insjmp
    src1:
    jnz nextdi1
    jmp oksrc1
    
    nextdi1:
    cmp di,11 
    JMP src2
    oksrc2:
    DetectSourceMode input+11
    jmp insjmp
    src2:
    jnz nextdi2
    jmp oksrc2
    
    nextdi2:
    cmp di,13
    JMP src3
    oksrc3:
    DetectSourceMode input+13
    jmp insjmp
    src3:
    jnz insjmp
    jmp oksrc3
    
    insjmp:
    mov al,checkDesSize
    mov ah,checkSrcSize
    cmp al,ah
    
    jmp instest0
    insok0:
    cmp al,0
    jmp instest1
    insok1:
    
    cmp al,1
    jmp  instest2
    insok2:
    jmp executeins
    instest2:
    jnz insok2
    jmp executeins05 
    
    
    
    instest1:
    jnz insok1
    jmp invalidop
    
    instest0:
    
    jz insok0
    add al,ah
    cmp al,2
    jmp instest4
    insok4:
    cmp al,1
    jmp instest2
    instest4:
    jbe insok4 
    jmp invalidop
    
    executeins:
    checkInsruction  input+2
    jmp leaveexecute
    executeins05:
    checkInsruction05  input+2
    jmp leaveexecute
    invalidop:
    printmsg invalid
    jmp leaveexecute
    leaveexecute:
endm executeInstruction

;---------------------dataSegment------------------------

.data
instruction db 16,?, 16 dup('$')
;input db 16,?, 16 dup('$')
newline db 10,13,'$'
invalid db "invalid Operation$"
  
               
;---------------------REGISTERS---------------------

AXREG LABEL WORD 
ALREG db 12H 
AHREG db 13H 
 
BXREG LABEL WORD 
BLREG db 05H 
BHREG db 00H 
 
CXREG LABEL WORD 
CLREG db 8h 
CHREG db 6h 
 
DXREG LABEL WORD 
DLREG db 1h 
DHREG db 34h

SIREG dw 0007H 
DIREG dw 000AH 
BPREG dw ?

memory db 16 dup(?)

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

;--------------------Validation Variables---------------
checkDesSize db 0
checkSrcSize db 0
               
;----------------------------------------------------
.code
    main proc far
        mov AX,@DATA
        mov DS,AX
        mov ES,AX
        enterins:
        ;push_all
        readmsg instruction
        executeInstruction instruction
        printmsg newline
        ;mov checkDesSize,2
        ;printmsg ADHAM
        
        ;pop_all
        jmp enterins  
        ;mov dx,word ptr BLREG
        ;printhexa dx
        ;MOV CX, 3 
        ;MOV SI, offset ax_str  
        ;MOV DI, offset ax_str 
        ;REPE CMPSB
        ;MOV DL,CL
        ;add dl,30h
        ;mov ah,2
        ;int 21h
HLT         
main endp
end main