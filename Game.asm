include des1.inc
include ins1.inc
include ins2.inc
include utility.inc
include src1.inc
include srcval.inc  
include src2.inc

.model huge
;----------------EXECUTE INSTRUCTION---------------- 

executeInstruction macro input 
CheckDestination input+6
;CheckSourceVal input+9
;RegisterIndirect input+10
;CheckSource input+9
Direct input+10
checkInsruction input+2
endm executeInstruction

;---------------------dataSegment------------------------

.data
instruction db 16,?, 16 dup('$') 
newline db 10,13,'$'
memory db 1h,3h,0Ah,7h,8h,0Eh,6h,2h,0Fh,10h,0Bh,0Ch,13h,14h,15h,16h
adham db "adham$"  
               
;---------------------REGISTERS---------------------

AXREG LABEL WORD 
ALREG db 18H 
AHREG db 44H 
 
BXREG LABEL WORD 
BLREG db 0FH 
BHREG db 00H 
 
CXREG LABEL WORD 
CLREG db 8h 
CHREG db 6h 
 
DXREG LABEL WORD 
DLREG db 1h 
DHREG db 34h

SIREG dw 7h 
DIREG dw 0Ah 
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
        MOV BX,1234H
        readmsg instruction
        executeInstruction instruction  
        ;printmsg newline
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
         
main endp 
end main