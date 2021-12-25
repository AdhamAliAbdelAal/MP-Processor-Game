;--------------Based Relative--------------------

BasedRelative macro Ins 
    local JumpBX1
    local Found_ES
    local exit_ES_N
    local exit_ES 
    LOCAL Letter_ES
    LOCAL strL1_ES
    LOCAL strL2_ES
    LOCAL strL3_ES
    LOCAL strL4_ES
    LOCAL strL5_ES
    LOCAL strL6_ES
    local ExitValA_ES
    push ax
    push bx
    push cx
     checkEQUALITY bp_str,Ins   
    JNZ JumpBX1  
    MOV AX, WORD PTR BPREG
    CMP AX, 001Eh
     JNC exit_ES_N  
    JMP Found_ES  
    JumpBX1:  
      
    checkEQUALITY bx_str,Ins     
    JNZ exit_ES_N  
    MOV AX, WORD PTR BLREG 
     CMP AX, 001Eh
     JNC exit_ES_N 
    JMP Found_ES 
    
    exit_ES_N:
         JMP exit_ES 
    Found_ES:
           mov Bx,offset memory 
           MOV CL,0H
           MOV CH,BYTE PTR Ins+3 
        push ax
        push bx
         
                MOV AH,58
                CMP CH,AH
                JNC Letter_ES
                SUB CH, 30h
                JMP ExitValA_ES
                Letter_ES:
                    SUB CH, 31h
                    MOV AH,10H
                    CMP CH, AH
                    JNE strL1_ES
                    MOV CH, 0Ah
                    JMP ExitValA_ES
                    strL1_ES:
                    MOV AH,11H
                    CMP CH, AH
                    JNE strL2_ES
                    MOV CH, 0Bh
                    JMP ExitValA_ES
                    strL2_ES:
                    MOV AH,12H
                    CMP CH, AH
                    JNE strL3_ES
                    MOV CH, 0Ch
                    JMP ExitValA_ES
                    strL3_ES:
                    MOV AH,13H
                    CMP CH, AH
                    JNE strL4_ES
                    MOV CH, 0Dh
                    JMP ExitValA_ES
                    strL4_ES:
                    MOV AH,14H
                    CMP CH, AH
                    JNE strL5_ES
                    MOV CH, 0Eh
                    JMP ExitValA_ES
                    strL5_ES:
                    MOV AH,15H
                    CMP CH, AH
                    JNE strL6_ES
                    MOV CH, 0Fh
                    JMP ExitValA_ES
                    strL6_ES:
                ExitValA_ES:
                  
        pop bx 
        pop ax   
           MOV CL,CH
           MOV CH,0H
           ADD bX,cX
           add Bx,Ax
           MOV AX, 001Eh
           ADD AX, offset memory
           CMP BX,AX
           JNC exit_ES  
           MOV DX, [BX]       
    exit_ES:
 
    pop cx
    pop bx 
    pop ax 
endm BasedRelative