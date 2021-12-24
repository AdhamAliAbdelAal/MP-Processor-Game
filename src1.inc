;---------------DETECT SOURCE--------------
 
CheckSource MACRO Ins
    local JumpAX
    local JumpBX
    local JumpCX
    local JumpDX
    local JumpAL
    local JumpAH
    local JumpBL
    local JumpBH
    local JumpCL
    local JumpCH
    local JumpDL
    local JumpDH
    local JumpDI
    local JumpSI
    local JumpBP
    local Found  
    checkEQUALITY ax_str,Ins    
    JNZ JumpAX  
    MOV DX, WORD PTR ALREG 
    mov checkSrcSize,2 
    JMP Found  
    JumpAX:  
      
    checkEQUALITY bx_str,Ins     
    JNZ JumpBX  
    MOV DX, WORD PTR BLREG
    mov checkSrcSize,2  
    JMP Found  
    JumpBX:  
      
    checkEQUALITY cx_str,Ins    
    JNZ JumpCX  
    MOV DX, WORD PTR CLREG
    mov checkSrcSize,2  
    JMP Found  
    JumpCX:  
      
    checkEQUALITY dx_str,Ins     
    JNZ JumpDX  
    MOV DX, WORD PTR DLREG
    mov checkSrcSize,2  
    JMP Found  
    JumpDX: 
     
    checkEQUALITY al_str,Ins     
    JNZ JumpAL
    MOV DL, ALREG
    mov checkSrcSize,1  
    JMP Found  
    JumpAL: 
            
    checkEQUALITY ah_str,Ins     
    JNZ JumpAH     
    MOV DL, AHREG
    mov checkSrcSize,1  
    JMP Found  
    JumpAH: 
     
    checkEQUALITY bl_str,Ins     
    JNZ JumpBL  
    MOV DL, BLREG
    mov checkSrcSize,1  
    JMP Found  
    JumpBL: 
     
    checkEQUALITY bh_str,Ins     
    JNZ JumpBH  
    MOV DL, BHREG
    mov checkSrcSize,1  
    JMP Found  
    JumpBH: 
     
    checkEQUALITY cl_str,Ins     
    JNZ JumpCL  
    MOV DL, CLREG
    mov checkSrcSize,1  
    JMP Found  
    JumpCL: 
     
    checkEQUALITY ch_str,Ins     
    JNZ JumpCH  
    MOV DL, CHREG
    mov checkSrcSize,1  
    JMP Found  
    JumpCH: 
     
    checkEQUALITY dl_str,Ins    
    JNZ JumpDL  
    MOV DL, DLREG
    mov checkSrcSize,1  
    JMP Found  
    JumpDL: 
     
    checkEQUALITY dh_str,Ins     
    JNZ JumpDH  
    MOV DL, DHREG 
    mov checkSrcSize,1 
    JMP Found  
    JumpDH: 
     
    checkEQUALITY si_str,Ins     
    JNZ JumpSI  
    MOV DX, SIREG
    mov checkSrcSize,2  
    JMP Found  
    JumpSI: 
     
    checkEQUALITY di_str,Ins     
    JNZ JumpDI  
    MOV DX, DIREG
    mov checkSrcSize,2  
    JMP Found  
    JumpDI: 
     
    checkEQUALITY bp_str,Ins     
    JNZ JumpBP  
    MOV DX, BPREG
    mov checkSrcSize,2  
    JMP Found  
    JumpBP: 
     
    Found: ;EXIT  
endm CheckSource