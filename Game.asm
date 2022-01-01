Include des1.inc
include ins1.inc
include ins2.inc
include utility.inc
include src1.inc
include src2.inc
include srcval.inc
include BasRel.inc
include cute.inc     

.model huge


;---------------------dataSegment------------------------

.data
instruction db 16,?, 16 dup('$')
;input db 16,?, 16 dup('$')
newline db 10,13,'$'
invalid db "invalid Operation$"
;adham db "hamdy el 3abeet$"
  
               
;---------------------REGISTERS---------------------  
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

; PLAYER 1

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

; PLAYER 2

AXREG2 LABEL WORD 
ALREG2 db 09H 
AHREG2 db 00H 
 
BXREG2 LABEL WORD 
BLREG2 db 03H 
BHREG2 db 00H 
 
CXREG2 LABEL WORD 
CLREG2 db 0fh 
CHREG2 db 12h 
 
DXREG2 LABEL WORD 
DLREG2 db 42h 
DHREG2 db 0abh

SIREG2 dw 0006H 
DIREG2 dw 000BH 
BPREG2 dw ?

memory db 0,1,2,3,4,5,6,7,8,9,0ah,0bh,0ch,0dh,0eh,0fh   
memory2 db 16 dup(?)
;-----------------------------------------------

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
checkDesSize db 100
checkSrcSize db 50
               
;---------------------------------------------------- 
player db 0          
;-------------------POWER UPS--------------------
pow1 db "P1$" 
pow2 db "P2$"
pow3 db "P3$"
pow4 db "P4$"
pow5 db "P5$"   

OFFSET_P4 dw ?      
IS_P4 db 1
;------------------------------------------------
DRAWREG_PLAYERS MACRO
    INPUTFIELD
    ;player one drawings
    mov bp,0
    draw  3A1bh,bp
    drawbyte 0000h,bp 
    ;player two drawings 
    mov bp,14
    draw  3A39h,bp
    add bp,2
    drawbyte 0018h,bp
    mov_cursor 444ch
ENDM DRAWREG_PLAYERS

.code
    main proc far
        mov AX,@DATA
        mov DS,AX
        mov ES,AX
        PUSHF
        GO
        ;Draw_BK
        mov cl,1
        enterins:
        DRAWREG_PLAYERS 
        readmsg instruction 
        checkEQUALITY pow1,instruction+2
        jmp Checkp2Jump 
        OkP1: 
        INPUTFIELD
        resetins instruction+2
        readmsg instruction 
        xor player,1
        CALL executeInstruction 
        xor player,1 
        jmp ENDCHECKS      
        
        Checkp2Jump:
        jnz CheckP2
        jmp OkP1 

        CheckP2:
        checkEQUALITY pow2,instruction+2
        jmp Checkp3Jump
        OkP2:  
        INPUTFIELD
        resetins instruction+2
        readmsg instruction 
        CALL executeInstruction 
        xor player,1  
        CALL executeInstruction
        xor player,1
        jmp ENDCHECKS
        
        Checkp3Jump:
        jnz CheckP3
        jmp OkP2 

        CheckP3:
        checkEQUALITY pow3,instruction+2
        jnz CheckP4 
        ;hamdy logic
        jmp ENDCHECKS
        
        CheckP4:
        checkEQUALITY pow4,instruction+2
        jnz CheckP5 
        mov IS_P4,0
        jmp ENDCHECKS
        
        CheckP5:
        checkEQUALITY pow5,instruction+2
        jnz NORMALEXE 
        mov al,0
        mov cx,28
        REP STOSB
        jmp ENDCHECKS
          
         
         
        NORMALEXE: 
        CALL executeInstruction
        ;--check for p4
        cmp IS_P4,0
        jnz ENDCHECKS
        mov bx,OFFSET_P4
        mov ax,[bx]
        and ax,0FFFEH
        mov [bx],ax 
        mov IS_P4,1 
        
        
        ENDCHECKS:
        resetins instruction+2 
        xor player,1
        jmp enterins    
HLT         
main endp
;----------------EXECUTE INSTRUCTION---------------- 

executeInstruction PROC near 
    push_all
    cmp instruction+6,'['
    jmp test0
    ok0:
    CheckDestination instruction+6
    MOV DI,9 
    jmp tosource
    test0:
    jz mshReg
    jmp ok0
    
    mshReg:
    cmp instruction+8,']'
    jmp test1
    ok1:
    DirectDestination instruction+7
    MOV DI,10 
    jmp tosource
    test1:
    jnz mshDirect
    jmp ok1
    
    mshDirect:
    cmp instruction+9,']'
    jmp test2
    ok2:
    RegIndirect instruction+7
    mov di,11 
    jmp tosource
    test2:
    jnz mshIndirect
    jmp ok2
    
    mshIndirect:
    cmp instruction+11,']'
    jmp test3
    ok3:
    BasedRelativeDES instruction+7
    mov di,13
    jmp tosource
    test3:
    jnz tosource
    jmp ok3
            
    tosource:             
    mov OFFSET_P4,bx
    cmp di,9
    JMP src0
    oksrc0:
    DetectSourceMode instruction+9
    jmp insjmp
    src0:
    jnz nextdi0
    jmp oksrc0
    
    nextdi0:
    cmp di,10
    JMP src1
    oksrc1:
    DetectSourceMode instruction+10
    jmp insjmp
    src1:
    jnz nextdi1
    jmp oksrc1
    
    nextdi1:
    cmp di,11 
    JMP src2
    oksrc2:
    DetectSourceMode instruction+11
    jmp insjmp
    src2:
    jnz nextdi2
    jmp oksrc2
    
    nextdi2:
    cmp di,13
    JMP src3
    oksrc3:
    DetectSourceMode instruction+13
    jmp insjmp
    src3:
    jnz insjmp
    jmp oksrc3
    
    insjmp:
    mov al,checkDesSize
    mov ah,checkSrcSize 
    mov_cursor 424Ah 
    printhexa AX
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
    jmp instest3
    insok3:
    cmp al,1
    jmp instest2
    instest3:
    jbe insok3
    mov_cursor 404Ah 
    printhexa AX 
    jmp invalidop
    
    executeins:
    checkInsruction  instruction+2
    jmp leaveexecute
    executeins05:
    checkInsruction05  instruction+2
    jmp leaveexecute
    invalidop:     
    ;mov_cursor 424ch
    printmsg invalid
    jmp leaveexecute
    leaveexecute: 
    MOV checkDesSize, 100
    MOV checkSrcSize , 50
    pop_all        
    ret
executeInstruction endp
end main  
