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
    local test0  
    local test1
    local test2
    local test3
    local ok0
    local ok1
    local ok2 
    local ok3
    local mshReg
    local mshDirect
    local mshIndirect 
    local tosource
    local oksrc0
    local oksrc1
    local oksrc2
    local oksrc3
    local src0
    local src1
    local src2
    local src3    
    local nextdi0  
    local nextdi1
    local nextdi2
    local insjmp
    local insok0 
    local insok1  
    local insok2
    local insok3
    local instest0
    local instest1
    local instest2
    local instest3     
    local invalidop
    push_all
    
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
    jmp instest3
    insok3:
    cmp al,1
    jmp instest2
    instest3:
    jbe insok3 
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
    pop_all
endm executeInstruction
