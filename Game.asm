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
adham db "hamdy el 3abeet$"
  
               
;---------------------REGISTERS---------------------

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
        PUSHF
        GO
        ;Draw_BK
        enterins: 
        INPUTFIELD
        draw  3A1bh 
        draw  3A39h
        drawbyte 0000h
        drawbyte 0018h
        mov si,444ch
        mov_cursor si
        readmsg instruction
        executeInstruction instruction 
         ;executeInstruction instruction
        resetins instruction+2
        jmp enterins  
HLT         
main endp
end main