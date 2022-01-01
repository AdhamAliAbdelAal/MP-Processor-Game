SearchForbiddenLetter1 MACRO ins
    local CheckLoop_AH
    local SetFL
    push_all
    MOV BX,0
    CheckLoop_AH:
    MOV AL, BYTE PTR ins[BX]
        CMP AL,FL1
        JNE SetFL
        MOV Cl,1
        MOV FL_Found1,Cl
        SetFL:
        INC BX
        CMP AL,0Dh
        JNE CheckLoop_AH
    pop_all
endM SearchForbiddenLetter1

SearchForbiddenLetter2 MACRO ins
    local CheckLoop_AH2
    local SetFL2
    push_all
    MOV BX,0
    CheckLoop_AH2:
    MOV AL, BYTE PTR ins[BX]
        CMP AL,FL2
        JNE SetFL2
        MOV Cl,1
        MOV FL_Found2,Cl
        SetFL2:
        INC BX
        CMP AL,0Dh
        JNE CheckLoop_AH2
    pop_all
endM SearchForbiddenLetter2

FL_screen macro ;; Start Screen
 push_all
    clear 
    mov_cursor 0400h 
    printmsg  FL_str 
    mov_cursor 0c35h
    readchar FL1
    printchar FL1
    mov_cursor 0f35h
    readchar FL2
    printchar FL2 
    ;wait_enter    
 pop_all
endm FL_screen

FL_Main MACRO
    local FL_p2
    local EX_FL
    MOV CL,player
    CMP CL,1
    JE FL_p2
    SearchForbiddenLetter1 instruction+2
    JMP EX_FL
    FL_p2:
    SearchForbiddenLetter2 instruction+2
    EX_FL: 
ENDM FL_Main