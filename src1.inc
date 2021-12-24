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
    MOV AH,7
    INT 21H    
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