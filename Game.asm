EXTRN BG:far
EXTRN imgW:word
EXTRN imgH:word
EXTRN img:byte

Include des1.inc
include ins1.inc
include ins2.inc
include utility.inc
include src1.inc
include src2.inc
include srcval.inc
include BasRel.inc
include cute.inc
include FL.inc
include MAIN.inc     
include GUN.INC
.model huge
.stack 64

;---------------------dataSegment------------------------

.data
instruction db 16,?, 16 dup('$')
;input db 16,?, 16 dup('$')
newline db 10,13,'$'
invalid db "Invalid Operation$"
forbidden_Letter db "NOT ALLOWED!$"
FL1 db ?
FL2 db ?
FL_Found1 db 0
FL_Found2 db 0 
FL_str1  db   '                                                                ',0ah,0dh
    DB   '        ===============================================================',0ah,0dh
    DB   '        ||                                                           ||',0ah,0dh                                        
    DB   '        ||              *    MP Processor Game   *                   ||',0ah,0dh
    DB   '        ||                                                           ||',0ah,0dh
    DB   '        ||-----------------------------------------------------------||',0ah,0dh 
    DB   '        ||                                                           ||',0ah,0dh
    DB   '        ||                                                           ||',0ah,0dh      
    DB   '        ||           Enter Forbidden Letter (player 1):              ||',0ah,0dh
    DB   '        ||                                                           ||',0ah,0dh      
    DB   '        ||                                                           ||',0ah,0dh         
    DB   '        ===============================================================',0ah,0dh  
    db   '                                                                    ',0ah,0dh     
    db   '                                                                    ',0ah,0dh
    DB   '$',0ah,0dh
    
FL_str2  db   '                                                               ',0ah,0dh
    DB   '        ===============================================================',0ah,0dh
    DB   '        ||                                                           ||',0ah,0dh                                        
    DB   '        ||              *    MP Processor Game   *                   ||',0ah,0dh
    DB   '        ||                                                           ||',0ah,0dh
    DB   '        ||-----------------------------------------------------------||',0ah,0dh 
    DB   '        ||                                                           ||',0ah,0dh   
    DB   '        ||                                                           ||',0ah,0dh
    DB   '        ||           Enter Forbidden Letter (player 2):              ||',0ah,0dh
    DB   '        ||                                                           ||',0ah,0dh   
    DB   '        ||                                                           ||',0ah,0dh         
    DB   '        ===============================================================',0ah,0dh  
    db   '                                                                    ',0ah,0dh     
    db   '                                                                    ',0ah,0dh
    DB   '$',0ah,0dh
FL_changed1 db 0
FL_changed2 db 0

Level_selection  db   '                                                       ',0ah,0dh
    DB   '                ====================================================',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh                                        
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||--------------------------------------------------||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                    Choose Level:                 ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh         
    DB   '                ====================================================',0ah,0dh  
    db   '                                                                    ',0ah,0dh     
    db   '                                                                    ',0ah,0dh
    DB   '$',0ah,0dh
  
InitialP1  db   '                                                             ',0ah,0dh
    DB   '               =====================================================',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh                                        
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||--------------------------------------------------||',0ah,0dh
    DB   '               ||                    (PLAYER 1)                    ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                   AX:                            ||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                   BX:                            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||                   CX:                            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                   DX:                            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                   SI:                            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                   DI:                            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                   BP:                            ||',0ah,0dh         
    DB   '                ====================================================',0ah,0dh  
    db   '                                                                    ',0ah,0dh     
    db   '                                                                    ',0ah,0dh
    DB   '$',0ah,0dh
    
InitialP2  db   '                                                             ',0ah,0dh
    DB   '               =====================================================',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh                                        
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||--------------------------------------------------||',0ah,0dh
    DB   '               ||                    (PLAYER 2)                    ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                   AX:                            ||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                   BX:                            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||                   CX:                            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                   DX:                            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                   SI:                            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                   DI:                            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                   BP:                            ||',0ah,0dh         
    DB   '                ====================================================',0ah,0dh  
    db   '                                                                    ',0ah,0dh     
    db   '                                                                    ',0ah,0dh
    DB   '$',0ah,0dh
    
Points_Screen  db   '                                                            ',0ah,0dh
    DB   '        ===============================================================',0ah,0dh
    DB   '        ||                                                           ||',0ah,0dh                                        
    DB   '        ||              *    MP Processor Game   *                   ||',0ah,0dh
    DB   '        ||                                                           ||',0ah,0dh
    DB   '        ||-----------------------------------------------------------||',0ah,0dh 
    DB   '        ||                            |                              ||',0ah,0dh   
    DB   '        ||                            |                              ||',0ah,0dh
    DB   '        ||   Player 1 (Points):       |     Player 2 (Points):       ||',0ah,0dh
    DB   '        ||                            |                              ||',0ah,0dh   
    DB   '        ||                            |                              ||',0ah,0dh         
    DB   '        ===============================================================',0ah,0dh  
    db   '                                                                    ',0ah,0dh     
    db   '                                                                    ',0ah,0dh
    DB   '$',0ah,0dh
  
regval db 10,?, 10 dup('$')               
;---------------------REGISTERS---------------------  
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

; PLAYER 1

AXREG LABEL WORD 
ALREG db 12H 
AHREG db 13H 
 
BXREG LABEL WORD 
BLREG db 05H 
BHREG db 00H 
 
CXREG LABEL WORD 
CLREG db 8h 
CHREG db 6h 
 
DXREG LABEL WORD 
DLREG db 1h 
DHREG db 34h

SIREG dw 0007H 
DIREG dw 000AH 
BPREG dw ?

; PLAYER 2

AXREG2 LABEL WORD 
ALREG2 db 09H 
AHREG2 db 00H 
 
BXREG2 LABEL WORD 
BLREG2 db 03H 
BHREG2 db 00H 
 
CXREG2 LABEL WORD 
CLREG2 db 0fh 
CHREG2 db 12h 
 
DXREG2 LABEL WORD 
DLREG2 db 42h 
DHREG2 db 0abh

SIREG2 dw 0006H 
DIREG2 dw 000BH 
BPREG2 dw ?

memory db 0,1,2,3,4,5,6,7,8,9,0ah,0bh,0ch,0dh,0eh,0fh   
memory2 db 16 dup(?)   

FREG dw 0
FREG2 dw 0
;-----------------------------------------------

;------------------INSTRUCTION STRINGS---------------

mov_str db "MOV$"
add_str db "ADD$"
adc_str db "ADC$"
sub_str db "SUB$"
sbb_str db "SBB$"
and_str db "AND$"
mul_str db "MUL$"
div_str db "DIV$"
xor_str db "XOR$"
nop_str db "NOP$" 
shr_str db "SHR$" 
shl_str db "SHL$" 
sar_str db "SAR$" 
clc_str db "CLC$" 
ror_str db "ROR$" 
rcl_str db "RCL$" 
rcr_str db "RCR$" 
rol_str db "ROL$" 
inc_str db "INC$" 
dec_str db "DEC$"

;-------------------REGISTER STRINGS-----------------

ax_str db "AX$" 
al_str db "AL$" 
ah_str db "AH$" 
 
bx_str db "BX$" 
bl_str db "BL$" 
bh_str db "BH$" 
 
cx_str db "CX$" 
cl_str db "CL$" 
ch_str db "CH$" 
 
dx_str db "DX$" 
dl_str db "DL$" 
dh_str db "DH$"

si_str db "SI$"
di_str db "DI$"
bp_str db "BP$"

;--------------------Validation Variables---------------
checkDesSize db 100
checkSrcSize db 50
               
;---------------------------------------------------- 
mainPlayer db 0
player db 0
level db '1'
value db ?

pointer dw ?   
GAME_Main_STR  db   '        ',0ah,0dh
    DB   '                ====================================================',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh                                        
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||--------------------------------------------------||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||            To Start chatting press F1            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||            To start the game press F2            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||            To end the program press ESC          ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '                ====================================================',0ah,0dh  
    db   '                                                                    ',0ah,0dh     
    db   '                                                                    ',0ah,0dh
    db   '                                                                    ',0ah,0dh  
    DB   80 DUP('-'),'$',0ah,0dh  
    DB   '$',0ah,0dh 
           
GAME_Start2_STR  db   '        ',0ah,0dh 
    DB   '                ====================================================',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh                                         
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||--------------------------------------------------||',0ah,0dh  
    DB   '               ||                                                  ||',0ah,0dh    
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||  Enter your Second Player:                       ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh    
    DB   '               ||                                                  ||',0ah,0dh    
    DB   '               ||  Intial Points for Second Player:                ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh    
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||               Press Enter key to continue        ||',0ah,0dh  
    DB   '               ||                   * MAX point 200 *              ||',0ah,0dh 
    DB   '               ||               * MAX Name 15 characters *         ||',0ah,0dh    
    DB   '                ====================================================',0ah,0dh   
    db   '                                                                    ',0ah,0dh      
    db   '                                                                    ',0ah,0dh 
    DB   '$',0ah,0dh  
    
    
   GAME_Start_STR  db   '        ',0ah,0dh 
    DB   '                ====================================================',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh                                         
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||--------------------------------------------------||',0ah,0dh  
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||  Enter your First Player:                        ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh       
    DB   '               ||  Intial Points for First Player:                 ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh    
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh    
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||               Press Enter key to continue        ||',0ah,0dh  
    DB   '               ||                   * MAX point 200 *              ||',0ah,0dh        
    DB   '               ||               * MAX Name 15 characters *         ||',0ah,0dh    
    DB   '                ====================================================',0ah,0dh   
    db   '                                                                    ',0ah,0dh      
    db   '                                                                    ',0ah,0dh 
    DB   '$',0ah,0dh
      
msg_name db 9,9,9,"Enter your name:" ,10,13," $"
msg_point db 9,9,9,"intial points:",10,13," $"
msg_keyEnter db 9,9,9,"Press enter key to continue $"


STR_Point db  10,?,10 duP('$')
STR_Point2 db  10,?,10 duP('$')  
player_name db 15,?,15 dup('$') 
player_name2 db 15,?,15 dup('$') 
tab db 9,9,9,'$'      
    

emptysttr db "$"        
ClEAR_LINE    DB 80 DUP(' '),'$'
F1_STR  DB '-You send a chat invitation to ','$'
F2_STR  DB '-You send a game invitation to ','$'

get1_STR  DB 'Sent a chat invitation tO you ','$'
get2_STR  DB 'Sent a game invitation tO you ','$'


begin_nof db 0      
notication db 80 DUP('$'),'$'   
;;------------------- gun ----------------------- 
	WINDOW_HEIGHT_TOP DW 64h                ;the height of the window (200 pixels)  
    WINDOW_HEIGHT_BOTTOM DW 96h 
    PADDLE_VELOCITY_Y DW 3h
     
    WINDOW_WIDTH DW 7Dh                 ;the width of the window (320 pixels)
	WINDOW_HEIGHT DW 0a0h                ;the height of the window (200 pixels)
	;WINDOW_BOUNDS DW 6                  ;variable used to check collisions early
	
   
   TIME_AUX DB 0                        ;variable used when checking if the time has changed
	                     
    ;BALL_ORIGINAL_X DW 19h              ;X position of the ball on the beginning of a game
	;BALL_ORIGINAL_Y DW 96h               ;Y position of the ball on the beginning of a game
	BALL_X DW 28h                       ;current X position (column) of the ball
	BALL_Y DW 96h                        ;current Y position (line) of the ball
	BALL_SIZE DW 06h                     ;size of the ball (how many pixels does the ball have in width and height)
;	BALL_VELOCITY_X DW 05h               ;X (horizontal) velocity of the ball
	BALL_VELOCITY_Y DW 14h   
	
	
	PADDLE_LEFT_X DW 1Eh                 ;current X position of the left paddle
	PADDLE_LEFT_Y DW 96h                 ;current Y position of the left paddle
	PLAYER_ONE_POINTS DB 0              ;current points of the left player (player one)
	
	PADDLE_RIGHT_X DW 0BAh               ;current X position of the right paddle
	PADDLE_RIGHT_Y DW 96h                ;current Y position of the right paddle
	PLAYER_TWO_POINTS DB 0             ;current points of the right player (player two)
	
	PADDLE_WIDTH DW 06h                  ;default paddle width
	PADDLE_HEIGHT DW 25h                 ;default paddle height
	PADDLE_VELOCITY DW 0Fh               ;default paddle velocity   
	
	GUN DB 1h 
	GUN2 DB 1h
	
	level_color db 0
	
	green_color db 0
	light_blue_color db 0
	yellow_color db 0
	red_color db 0
	blue_color db 0  
	 
	 
	Target_x dw 10h 
	Target_y dw 10h
	Target_Velocity dw 8h 
	Target_SIZE DW 10h 
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;mahmoud
	
	;level2_color db 0h
	
	;Target2_x dw 0A5h  
	;Target2_y dw 10h
	;Target2_Velocity dw 1h 
	;Target2_SIZE DW 10h 
	
	BALL2_X DW 0C4h                       ;current X position (column) of the ball
	BALL2_Y DW 96h                        ;current Y position (line) of the ball
	BALL2_SIZE DW 06h                     ;size of the ball (how many pixels does the ball have in width and height)
	BALL2_VELOCITY_X DW 05h               ;X (horizontal) velocity of the ball
	BALL2_VELOCITY_Y DW 14h   
	
	
	WINDOW_WIDTH2 DW 104h ;260             
	WINDOW_HEIGHT2 DW 0C8h               
	
	
	
	LEFT_PADDEL_LIMIT_FROM_LEFT  DW 5h
	RIGHT_PADDEL_LIMIT_FROM_LEFT  DW 0AAh
    Target1_start_x	DW 0h 
    Target2_start_x	DW 0A5h
               
               
     level_color2 db 0h
	
	green_color2 db 0
	light_blue_color2 db 0
	yellow_color2 db 0
	red_color2 db 0
	blue_color2 db 0     
     turn db 0                  
	 bullet db 0
	 bullet2 db 0 
       ;;;;;;;;
       color_ball db 3h
       color_ball2  db 0ch 
       
;-------------------POWER UPS--------------------
pow1 db "P1$" 
pow2 db "P2$"
pow3 db "P3$"
pow4 db "P4$"
pow5 db "P5$"   

OFFSET_P4 dw ?      
IS_P4 db 1
REGSCLEARED DB 0
;------------------------------------------------
Target1_VAL_STR db  10,?,10 duP('$') 
Target2_VAL_STR db  10,?,10 duP('$') 
TARGET1 DW 105Eh 
TARGET2 DW 105Eh
;------------Targets screen----------
TARGET1_STR  db   '        ',0ah,0dh 
    DB   '                ====================================================',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh                                         
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||--------------------------------------------------||',0ah,0dh  
    DB   '               ||                     (Player 1)                   ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh       
    DB   '               ||  Choose Target for the second player:            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh  
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '                ====================================================',0ah,0dh   
    db   '                                                                    ',0ah,0dh      
    db   '                                                                    ',0ah,0dh 
    DB   '$',0ah,0dh  
  
  TARGET2_STR  db   '        ',0ah,0dh 
    DB   '                ====================================================',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh                                         
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||--------------------------------------------------||',0ah,0dh  
    DB   '               ||                     (Player 2)                   ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh       
    DB   '               ||  Choose Target for the first player:             ||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh     
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '                ====================================================',0ah,0dh   
    db   '                                                                    ',0ah,0dh      
    db   '                                                                    ',0ah,0dh 
    DB   '$',0ah,0dh

Processor1 db 2
Processor2 db 1    
number db ?
WINNER DB 'CONGRATULATIONS PLAYER',' $'
WON DB ' HAS WON$'
FE_PLAYER_KESEB DB 0
  
  
cong_screen    db   '        ',0ah,0dh
    DB   '                ====================================================',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh                                        
    DB   '               ||            *    MP Processor Game   *            ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||--------------------------------------------------||',0ah,0dh 
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh      
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||                                                  ||',0ah,0dh
    DB   '               ||GAME HAS ENDED                                    ||',0ah,0dh   
    DB   '               ||                                                  ||',0ah,0dh         
    DB   '                ====================================================',0ah,0dh  
    db   '                                                                    ',0ah,0dh     
    db   '                                                                    ',0ah,0dh
    DB   '$',0ah,0dh   
      
;-------------------------------- 
;------Initial Points---------
POINT DB 50
POINT2 DB 40
;-------------------------------------   
;--------Power Ups Limits--------
LimitP31 db 0
LimitP32 db 0
LimitP51 db 0
LimitP52 db 0

;--------------------------------

Player_Turn db "Player:$"
Processor_Select db 1
   
Is_limitedP3 macro 
    local nafezP3ady
     mov bx,offset LimitP31
     add bl,player
     mov al,[bx]
     cmp al,1
     jnz nafezP3ady
     jmp ENDCHECKS  
     nafezP3ady:  
     mov al,1
     mov [bx],al   
endm Is_limitedP3    
Is_limitedP5 macro  
    local nafezP5ady
     mov bx,offset LimitP51
     add bl,player
     mov al,[bx]
     cmp al,1
     jnz nafezP5ady
     jmp ENDCHECKS  
     nafezP5ady:
     mov al,1
     mov [bx],al   
endm Is_limitedP5

     

.code
    main proc far
        mov AX,@DATA
        mov DS,AX
        mov ES,AX
        ;PUSHF
        
        ;;;;;;;;;;;;;;;;;;;;;;;;;;; first screen (Defining Usernames) 
        clear      
        ;start_screen   
                             
        ;;;;;;;;;;;;;;;;;;;;;;;;;;; second screen (Main Screen)
        MAINHAMDY: 
        clear     
        ;main_screen
        SelectLevel
        
        MOV AL,level
        SUB AL,30h
        CMP AL,1
        JMP FIXX1
        IP1: 
        DrawInitialP1
        DrawInitialP2
        TAGET_1
        TAGET_2
        JMP CONT1
        FIXX1:
        JE CONT1
        JMP IP1
        CONT1:
        GO
        ;draw_bk 153,117,0,0,img1
	  
	               
	    ;DRAW_BK 56,176,0,117,IMG2
	     
	     
	    ;DRAW_bk 320,113,173,0,IMG3 
	    
	    
	    ;DRAW_BK 320,176,262,114,IMG4
        mov cl,1
        
        enterins:
        MOV Processor_Select,1
        mov Processor1,2
        mov Processor2,1
        PlayerTurn 
        CheckWinner1
        CheckWinner2
        CMP FE_PLAYER_KESEB,1
        JE RAND_END
        JMP CONTINUE_GAME
        RAND_END:
        JMP ENDGAME
        CONTINUE_GAME:
        DRAWREG_PLAYERS
        DrawTargetPoints
        DrawTargetPoints2
        mov_cursor 444ch
        readmsg instruction 
        checkEQUALITY pow1,instruction+2
        jmp Checkp2Jump 
        OkP1:
        MOV Processor_Select,0
        detectPoints 5
        INPUTFIELD 444ch
        resetins instruction+2
        readmsg instruction 
        xor player,1
        CALL executeInstruction 
        xor player,1
        
        jmp ENDCHECKS      
        
        Checkp2Jump:
        jnz CheckP2
        jmp OkP1
         

        CheckP2:
        checkEQUALITY pow2,instruction+2
        jmp Checkp3Jump
        OkP2:
        MOV Processor_Select,0
        detectPoints 3  
        INPUTFIELD 444ch
        resetins instruction+2
        readmsg instruction 
        CALL executeInstruction 
        xor player,1  
        CALL executeInstruction
        xor player,1
        
        jmp ENDCHECKS
        
        Checkp3Jump:
        jnz CheckP3
        jmp OkP2 

        CheckP3:
        checkEQUALITY pow3,instruction+2
        jmp CheckForP4
        YesPower3:
        MOV Processor_Select,0
        Is_limitedP3
        detectPoints 8
        MOV CL,player
        CMP CL,0
        jmp TestFlTest
        Yesp1:
        MOV CL,1
        MOV FL_changed2,CL
        FL_screen2
        GO
        ;draw_bk 153,117,0,0,img1
	  
	               
	    ;DRAW_BK 56,176,0,117,IMG2
	     
	     
	    ;DRAW_bk 320,113,173,0,IMG3 
	    
	    
	    ;DRAW_BK 320,176,262,114,IMG4
        
        jmp ENDCHECKS 
        TestFlTest:
        je ch0
        jmp Yesp1 
        ch0:            
        MOV CL,1
        MOV FL_changed1,CL
        FL_screen
        GO
        ;draw_bk 153,117,0,0,img1
	  
	               
	    ;DRAW_BK 56,176,0,117,IMG2
	     
	     
	    ;DRAW_bk 320,113,173,0,IMG3 
	    
	    
	    ;DRAW_BK 320,176,262,114,IMG4 
                 
        jmp ENDCHECKS
        
        CheckForP4:
        jnz CheckP4
        jmp YesPower3
        
        
        CheckP4:
        checkEQUALITY pow4,instruction+2
        jmp LawP5
        ya3amP4:
        MOV Processor_Select,0
        detectPoints 2 
        mov IS_P4,0
        INPUTFIELD 494ch
        jmp ENDCHECKS
         
        LawP5: 
        jnz CheckP5
        jmp ya3amP4
         
        CheckP5:
        checkEQUALITY pow5,instruction+2
        jmp lawnormal
        ya3amP5:
        MOV Processor_Select,0  
        Is_limitedP5
        detectPoints 30  
        mov al,0
        mov cx,28
        MOV DI,offset ALREG
        REP STOSB 
        INPUTFIELD 494ch
        jmp ENDCHECKS
        lawnormal:
        jnz NORMALEXE  
        jmp ya3amP5 
         
        NORMALEXE:
        mov_cursor 444ch
        SelectProcessor 
        CALL executeInstruction
        ;--check for p4
        cmp IS_P4,0
        jnz ENDCHECKS2
        mov bx,OFFSET_P4
        mov ax,[bx]
        and ax,0FFFEH
        mov [bx],ax 
        ;mov_cursor 374ch
        ;printhexa AX
        mov IS_P4,1
        JMP ENDCHECKS 
        
        ENDCHECKS2:
        mov al,level
        sub al,30h
        CMP al,1
        JE ENDCHECKS
        CMP PLAYER,1
        JE CCONTT2
        MOV AL,Processor1
        SUB AL,30H
        CMP AL,2
        JE ENDCHECKS
        xor player,1
        jmp ENDCHECKS
        ccontt2:
        MOV AL,Processor2
        SUB AL,30H
        CMP AL,1
        JE ENDCHECKS
        xor player,1
        
        ENDCHECKS:
        resetins instruction+2 
        xor player,1
        ;---------------------------------------
        MOV AH, 00h        
        INT 1AH          
                
        MOV BH, 57   ; 57 --> ASCII for (9) 
        MOV AH, DL  
        CMP AH, BH      
        JA RANDOM  

        MOV BH, 48   ; 48 --> ASCII for (0)
        MOV AH, DL   
        CMP AH, BH
        JB RANDOM 
        
        JMP  CHECK_TIME
        RANDOM:
        JMP enterins
     ;-------------------------------------------------------------
     PUSH_ALL
          CLEAR_SCREEN
        ; get the system time 
       CHECK_TIME: 
       
       
                 
        MOV AH,2Ch
       INT 21h
        
        CMP DL,TIME_AUX  
        JE  CHECK_TIME
        
        MOV TIME_AUX,DL     ;UPDATE TIME
        
        
            ; CLEAR_SCREEN
             
             ;;;;;;;;;;;;;;;;;;
            ; MOV AH, 06h   
             ;   XOR AL, AL    
             ;   XOR CX, CX     
             ;   MOV DX, 184FH  
            ;   MOV BH, 0h    
            ;    INT 10H
         ;          MOV AH,00h
        ;MOV AL,02
        ;INT 10h      
       ; ccealr
       blacked 192,48,128,0
	      
	 blacked 173,200,145,48
	 
	 blacked 262,200,56,113
	 
	 blacked 320,200,0,176
	    
      ; DrawTargetPoints
      ; DrawTargetPoints2 
      ; DRAWREG_PLAYERS
         ;draw_bk 153,117,0,0,img1
	  
	               
	    ;DRAW_BK 56,176,0,117,IMG2
	     
	     
	    ;DRAW_bk 320,113,173,0,IMG3 
	    
	    
	    ;DRAW_BK 320,176,262,114,IMG4
                             
                                           
             cmp turn,5
             jl first 
                jmp exitGUN
               first:
               
                           
          Move_Target  Target_x, Target_y,WINDOW_WIDTH2,Target1_start_x  
           Draw_Target  Target_x, Target_y   
            
          
             
            MOVE_PADDLES           ;move the two paddles 
                Draw_paddles
         
                
            
            
			  CMP GUN,0            ;; if fire or not
		    JE fire_f
		  
		   jmp not_fire_loop_f 
		   
		   
		   
		       
           fire_f:
           
           
         MOVE_BALL BALL_X,BALL_Y, Target_x , Target_y,PADDLE_LEFT_X,PADDLE_LEFT_Y,Target1_start_x,green_color,light_blue_color,yellow_color,red_color,blue_color,POINT,GUN     
         Draw_Ball  BALL_X,BALL_Y,color_ball
      
          not_fire_loop_f:     
          
           
			CMP GUN2,0            ;; if fire or not
		    JE fire_s
		  
		   jmp not_fire_loop_s 
		       
           fire_s:
           
           
         MOVE_BALL BALL2_X,BALL2_Y, Target_x , Target_y,PADDLE_RIGHT_X,PADDLE_RIGHT_Y,Target1_start_x,green_color2,light_blue_color2,yellow_color2,red_color2,blue_color2,POINT2,GUN2     
         Draw_Ball  BALL2_X,BALL2_Y,color_ball2
      
          not_fire_loop_s:
          
          
            JMP  CHECK_TIME    
               

         exitGUN:
         MOV TURN,0
               MOV level_color,0
                MOV bullet,0  
                MOV bullet2,0
          mov gun,1
          mov gun2,1   
        blacked 192,48,128,0
	      
	 blacked 173,200,145,48
	 
	 blacked 262,200,56,113
	 
	 blacked 320,200,0,176
           DrawTargetPoints
       DrawTargetPoints2 
       DRAWREG_PLAYERS
          ;draw_bk 153,117,0,0,img1
	  
	               
	    ;DRAW_BK 56,176,0,117,IMG2
	     
	     
	    ;DRAW_bk 320,113,173,0,IMG3 
	    
	    
	    ;DRAW_BK 320,176,262,114,IMG4
	    POP_ALL  
        jmp enterins
        toScoreScreen:
        DrawPointsScreen         
        JMP MAINHAMDY
        ENDGAME:    
HLT         
main endp
;----------------EXECUTE INSTRUCTION---------------- 

executeInstruction PROC near 
    push_all
    INPUTFIELD 494ch       
    cmp player,0
    jz playerOne
    mov al,FL2
    JMP HAMDYEDIT
    playerOne:
    mov al,FL1
    HAMDYEDIT:
    mov cl,instruction+1
    ADD CL,1
    mov ch,0 
    mov di,2
    add di,offset instruction 
    REPNE SCASB
    cmp cx,0
    jmp TestForbidden
    YallaNafez:   
    checkINSEQUALITY instruction+2,nop_str
    jnz mshnop
    jmp leaveexecute
    mshnop:
    cmp instruction+6,'['
    jmp test0
    ok0:
    CheckDestination instruction+6
    MOV DI,9 
    jmp tosource
    test0:
    jz mshReg
    jmp ok0
    
    mshReg:
    cmp instruction+8,']'
    jmp test1
    ok1:
    DirectDestination instruction+7
    MOV DI,10 
    jmp tosource
    test1:
    jnz mshDirect
    jmp ok1
    
    mshDirect:
    cmp instruction+9,']'
    jmp test2
    ok2:
    RegIndirect instruction+7
    mov di,11 
    jmp tosource
    test2:
    jnz mshIndirect
    jmp ok2
    
    mshIndirect:
    cmp instruction+11,']'
    jmp test3
    ok3:
    BasedRelativeDES instruction+7
    mov di,13
    jmp tosource
    test3:
    jnz tosource
    jmp ok3
            
    tosource:             
    mov OFFSET_P4,bx
    cmp di,9
    JMP src0
    oksrc0:
    DetectSourceMode instruction+9
    jmp insjmp
    src0:
    jnz nextdi0
    jmp oksrc0
    
    nextdi0:
    cmp di,10
    JMP src1
    oksrc1:
    DetectSourceMode instruction+10
    jmp insjmp
    src1:
    jnz nextdi1
    jmp oksrc1
    
    nextdi1:
    cmp di,11 
    JMP src2
    oksrc2:
    DetectSourceMode instruction+11
    jmp insjmp
    src2:
    jnz nextdi2
    jmp oksrc2
    
    nextdi2:
    cmp di,13
    JMP src3
    oksrc3:
    DetectSourceMode instruction+13
    jmp insjmp
    src3:
    jnz insjmp
    jmp oksrc3
    
    insjmp:
    mov al,checkDesSize
    mov ah,checkSrcSize 
    ;mov_cursor 424Ah 
    ;printhexa AX
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
    ;mov_cursor 404Ah 
    ;printhexa AX 
    jmp invalidop
    
    executeins:
    checkInsruction  instruction+2
    jmp leaveexecute
    executeins05:
    checkInsruction05  instruction+2
    jmp leaveexecute
    invalidop:     
    MOV AL,LEVEL
    SUB AL,30H
    CMP AL,1
    je ccc
    cmp player,1
    je inv_p1
    mov al,processor1
    sub al,30h
    cmp al,2
    je ccc
    jmp cont_inv
    inv_p1:
    mov al,processor2
    sub al,30h
    cmp al,1
    je ccc
    cont_inv:
    xor player,1
    decPoints 1
    xor player,1
    mov_cursor 4a4ch
    printmsg invalid
    JMP leaveexecute
    ccc:
    mov_cursor 4a4ch
    printmsg invalid
    decPoints 1
    jmp leaveexecute
    TestForbidden:
    ;PUSHF
    ;mov_cursor 404ch
     
    ;POPF
    jnz Forbidden
    jmp YallaNafez
    Forbidden:
    mov_cursor 4a4dh
    printmsg forbidden_Letter
    ;decPoints 1
    xor player,1
    leaveexecute: 
    MOV checkDesSize, 100
    MOV checkSrcSize , 50 
    pop_all        
    ret
executeInstruction endp

;-----------------Initialization-----------------------
init proc near
    mov dx,3fbh ; Line Control Register
    mov al,10000000b ;Set Divisor Latch Access Bit
    out dx,al ;Out it            
    mov dx,3f8h
    mov al,0ch 
    out dx,al
    mov dx,3f9h
    mov al,00h
    out dx,al
    mov dx,3fbh
    mov al,00011011b
    out dx,al
    ret
init endp    
;--------------------------------------------
;-------------Receive------------------------
receive proc near 
mov dx , 3FDH ; Line Status Register  

CHK:
in al , dx
AND al,1
jz CHK

mov dx , 03F8H
in al , dx
mov VALUE , al

ret
receive endp
;--------------------------------------------------

;---------------------Send------------------------
send proc near
mov dx , 3FDH ; Line Status Register   

CheckSend:
In al , dx ;Read Line Status
AND al , 00100000b
JZ CheckSend

mov dx , 3F8H ; Transmit data register
mov al,VALUE
out dx , al



ret
send endp
;------------------------------------------------------
end main  
