;---------------DETECT SOURCE (Val)--------------
CheckSourceVal MACRO Ins
    PUSH BX
    MOV CL, 0
    MOV BX, 0
    
    ;------Determine string size--------
    Sizeloop:
        MOV CH, BYTE PTR Ins[BX]
        INC BX
        INC CL
        MOV AH,0DH
        CMP CH, AH
        JNE Sizeloop
    DEC CL
    ;-----------------------------------
    
    MOV DX, 0
    MOV BX, 0  
    MainLoop:
        MOV CH, BYTE PTR Ins[BX]
        MOV AH,57
        CMP CH,AH
        JNC Str
        SUB CH, 30h
        JMP EXITval
        Str:
            SUB CH, 31h
            MOV AH,10H
            CMP CH, AH
            JNE L1
            MOV CH, 0Ah
            JMP Exitval
            L1:
            MOV AH,11H
            CMP CH, AH
            JNE L2
            MOV CH, 0Bh
            JMP Exitval
            L2:
            MOV AH,12H
            CMP CH, AH
            JNE L3
            MOV CH, 0Ch
            JMP Exitval
            L3:
            MOV AH,13H
            CMP CH, AH
            JNE L4
            MOV CH, 0Dh
            JMP Exitval
            L4:
            MOV AH,14H
            CMP CH, AH
            JNE L5
            MOV CH, 0Eh
            JMP Exitval
            L5:
            MOV AH,15H
            CMP CH, AH
            JNE L6
            MOV CH, 0Fh
            JMP Exitval
            L6:
        Exitval:
            ADD DL, CH
            MOV AH,1
        CMP CL, AH
        JZ PreventShift
        MOV AH,CL
        MOV CL,4
        SHL DX, CL
        MOV CL,AH
        PreventShift:
        INC BX
        DEC CL
    JNZ MainLoop
    POP BX
ENDM CheckSourceVal