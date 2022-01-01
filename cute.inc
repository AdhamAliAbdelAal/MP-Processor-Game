DetectSourceMode MACRO instruction
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
    MOV CL, BYTE PTR instruction
    CMP CL, '['
    jmp testHamdy1
    okHamdy1:
    MOV CL, BYTE PTR instruction+1
    CMP CL, 'G'
    jmp testHamdy2
    okHamdy2:
    CheckSource instruction ; 1st
    JMP ExitSrcMode
    testHamdy2:
    JC Number
    jmp okHamdy2
    Number:
    CheckSourceVal instruction ; 2nd
    mov checkSrcSize,0
    JMP ExitSrcMode
    testHamdy1:
    JZ StartBracket
    jmp okHamdy1
    
    StartBracket:
    MOV CL, BYTE PTR instruction+2
    CMP CL, ']'
    JZ DirectMode 
    MOV CL, BYTE PTR instruction+3
    CMP CL, ']'
    jmp testHamdy3
    okHamdy3:
    JMP BasedRelativeMode
    
    DirectMode:
    Direct instruction+1 ; 3rd 
    JMP ExitSrcMode
    
    testHamdy3:
    JZ RegIndirect
    jmp okHamdy3
    
    
    
    RegIndirect:
    RegisterIndirect instruction+1 ; 4th 
    JMP ExitSrcMode
    
    BasedRelativeMode:
    BasedRelative instruction+1 ; 5th 
    
    ExitSrcMode: 
    POP CX
             
endM DetectSourceMode


                               
                               