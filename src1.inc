;---------------DETECT SOURCE--------------
 
CheckSource MACRO Ins  
    checkEQUALITY ax_str,Ins    
    JNZ JumpAX  
    MOV DX, WORD PTR ALREG  
    JMP Found  
    JumpAX:  
      
    checkEQUALITY bx_str,Ins     
    JNZ JumpBX  
    MOV DX, WORD PTR BLREG  
    JMP Found  
    JumpBX:  
      
    checkEQUALITY cx_str,Ins    
    JNZ JumpCX  
    MOV DX, WORD PTR CLREG  
    JMP Found  
    JumpCX:  
      
    checkEQUALITY dx_str,Ins     
    JNZ JumpDX  
    MOV DX, WORD PTR DLREG  
    JMP Found  
    JumpDX: 
     
    checkEQUALITY al_str,Ins     
    JNZ JumpAL
    MOV DL, ALREG  
    JMP Found  
    JumpAL: 
            
    checkEQUALITY ah_str,Ins     
    JNZ JumpAH     
    MOV DL, AHREG  
    JMP Found  
    JumpAH: 
     
    checkEQUALITY bl_str,Ins     
    JNZ JumpBL  
    MOV DL, BLREG  
    JMP Found  
    JumpBL: 
     
    checkEQUALITY bh_str,Ins     
    JNZ JumpBH  
    MOV DL, BHREG  
    JMP Found  
    JumpBH: 
     
    checkEQUALITY cl_str,Ins     
    JNZ JumpCL  
    MOV DL, CLREG  
    JMP Found  
    JumpCL: 
     
    checkEQUALITY ch_str,Ins     
    JNZ JumpCH  
    MOV DL, CHREG  
    JMP Found  
    JumpCH: 
     
    checkEQUALITY dl_str,Ins    
    JNZ JumpDL  
    MOV DL, DLREG  
    JMP Found  
    JumpDL: 
     
    checkEQUALITY dh_str,Ins     
    JNZ JumpDH  
    MOV DL, DHREG  
    JMP Found  
    JumpDH: 
     
    checkEQUALITY si_str,Ins     
    JNZ JumpSI  
    MOV DX, SIREG  
    JMP Found  
    JumpSI: 
     
    checkEQUALITY di_str,Ins     
    JNZ JumpDI  
    MOV DX, DIREG  
    JMP Found  
    JumpDI: 
     
    checkEQUALITY bp_str,Ins     
    JNZ JumpBP  
    MOV DX, BPREG  
    JMP Found  
    JumpBP: 
     
    Found: ;EXIT  
endm CheckSource