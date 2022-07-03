;----------REGISTER INDIRECT ADDRESSING MODE----------

RegisterIndirect MACRO input
    local RegBX
    local RI_Found
    local RegSI
    local RegDI
    local temp1_ah
    local cont1
    local execah1
    local temp1_ah2
    local cont2
    local execah2
    PUSH BX
    PUSH CX
    
    checkPlayer_des memory,memory2  
    
    checkEQUALITY bx_str,input     
    JNZ RegBX  
    checkPlayer_src10 BLREG,BLREG2
    CMP CX, 001Eh
    JNC RI_Found
    ADD BX, CX
    MOV DX, [BX]
    mov checkSrcSize,0   
    JMP RI_Found  
    RegBX:   
     
    checkEQUALITY si_str,input     
    JNZ RegSI  
    checkPlayer_src10 SIREG,SIREG2
    CMP CX, 001Eh
    JNC RI_Found
    ADD BX, CX
    MOV DX, [BX] 
    mov checkSrcSize,0 
    JMP RI_Found  
    RegSI: 
     
    checkEQUALITY di_str,input     
    JNZ RegDI  
    checkPlayer_src10 DIREG,DIREG2
    CMP CX, 001Eh
    JNC RI_Found
    ADD BX, CX
    MOV DX, [BX] 
    mov checkSrcSize,0 
    JMP RI_Found  
    RegDI: 
     
    RI_Found: ;EXIT
    
    POP CX
    POP BX
endM RegisterIndirect

;---------------DIRECT ADDRESSING MODE----------------

Direct MACRO input
    local NotPossible
    local Letter
    local ExitValA
    local strL1
    local strL2
    local strL3
    local strL4
    local strL5
    local strL6
    PUSH BX
 
    MOV CH, BYTE PTR input
    MOV CL, BYTE PTR input[1]
    CMP CL,93
    JNZ NotPossible
    MOV DX, 0
    checkPlayer_des memory,memory2
    MOV AH,58
    CMP CH,AH
    JNC Letter
    SUB CH, 30h
    JMP ExitValA
    Letter:
        SUB CH, 31h
        MOV AH,10H
        CMP CH, AH
        JNE strL1
        MOV CH, 0Ah
        JMP ExitValA
        strL1:
        MOV AH,11H
        CMP CH, AH
        JNE strL2
        MOV CH, 0Bh
        JMP ExitValA
        strL2:
        MOV AH,12H
        CMP CH, AH
        JNE strL3
        MOV CH, 0Ch
        JMP ExitValA
        strL3:
        MOV AH,13H
        CMP CH, AH
        JNE strL4
        MOV CH, 0Dh
        JMP ExitValA
        strL4:
        MOV AH,14H
        CMP CH, AH
        JNE strL5
        MOV CH, 0Eh
        JMP ExitValA
        strL5:
        MOV AH,15H
        CMP CH, AH
        JNE strL6
        MOV CH, 0Fh
        JMP ExitValA
        strL6:
        
    ExitValA:
        ADD BL,CH
        MOV DX,[BX]
        
    NotPossible:
    mov checkSrcSize,0
    POP BX    
endM Direct