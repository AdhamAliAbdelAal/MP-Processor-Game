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
    checkPlayer_src ALREG,ALREG2 
    mov checkSrcSize,2 
    JMP Found  
    JumpAX:  
      
    checkEQUALITY bx_str,Ins     
    JNZ JumpBX  
    checkPlayer_src BLREG,BLREG2
    mov checkSrcSize,2  
    JMP Found  
    JumpBX:  
      
    checkEQUALITY cx_str,Ins    
    JNZ JumpCX  
    checkPlayer_src CLREG,CLREG2
    mov checkSrcSize,2  
    JMP Found  
    JumpCX:  
      
    checkEQUALITY dx_str,Ins     
    JNZ JumpDX  
    checkPlayer_src DLREG,DLREG2
    mov checkSrcSize,2  
    JMP Found  
    JumpDX: 
     
    checkEQUALITY al_str,Ins     
    JNZ JumpAL
    checkPlayer_src05 ALREG,ALREG2
    mov checkSrcSize,1  
    JMP Found  
    JumpAL: 
            
    checkEQUALITY ah_str,Ins     
    JNZ JumpAH     
    checkPlayer_src05 AHREG,AHREG2
    mov checkSrcSize,1  
    JMP Found  
    JumpAH: 
     
    checkEQUALITY bl_str,Ins     
    JNZ JumpBL  
    checkPlayer_src05 BLREG,BLREG2
    mov checkSrcSize,1  
    JMP Found  
    JumpBL: 
     
    checkEQUALITY bh_str,Ins     
    JNZ JumpBH  
    checkPlayer_src05 BHREG,BHREG2
    mov checkSrcSize,1  
    JMP Found  
    JumpBH: 
     
    checkEQUALITY cl_str,Ins     
    JNZ JumpCL  
    checkPlayer_src05 CLREG,CLREG2
    mov checkSrcSize,1  
    JMP Found  
    JumpCL: 
     
    checkEQUALITY ch_str,Ins     
    JNZ JumpCH  
    checkPlayer_src05 CHREG,CHREG2
    mov checkSrcSize,1  
    JMP Found  
    JumpCH: 
     
    checkEQUALITY dl_str,Ins    
    JNZ JumpDL  
    checkPlayer_src05 DLREG,DLREG2
    mov checkSrcSize,1  
    JMP Found  
    JumpDL: 
     
    checkEQUALITY dh_str,Ins     
    JNZ JumpDH  
    checkPlayer_src05 DHREG,DHREG2 
    mov checkSrcSize,1 
    JMP Found  
    JumpDH: 
     
    checkEQUALITY si_str,Ins     
    JNZ JumpSI  
    checkPlayer_src SIREG,SIREG2
    mov checkSrcSize,2  
    JMP Found  
    JumpSI: 
     
    checkEQUALITY di_str,Ins     
    JNZ JumpDI  
    checkPlayer_src DIREG,DIREG2
    mov checkSrcSize,2  
    JMP Found  
    JumpDI: 
     
    checkEQUALITY bp_str,Ins     
    JNZ JumpBP  
    checkPlayer_src BPREG,BPREG2
    mov checkSrcSize,2  
    JMP Found  
    JumpBP: 
     
    Found: ;EXIT  
endm CheckSource