;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;    
;;---------------- Draw Target -------------------------------
Draw_Target macro TEMP_X , TEMP_Y
          local   DRAW_BALL_HORIZONTAL
          local   light_blue
          local    yellow
          local     red
          local      blue
          local      con
          push_all
         MOV CX,TEMP_X                    ;set the initial column (X)
		MOV DX,TEMP_Y                    ;set the initial line (Y)
		
		DRAW_BALL_HORIZONTAL:
			MOV AH,0Ch                   ;set the configuration to writing a pixel
			
			Cmp level_color,0h
			jne light_blue
			MOV AL,2h 					 ;; green
			jmp con    
			
			light_blue:
			Cmp level_color,1h
			jne yellow 
			MOV AL,9h 					 ;; light blue
			jmp con
			  
			  yellow:
			Cmp level_color,2h
			jne red 
			MOV AL,0eh 					 ;; yellow
			jmp con
			
			red:
			Cmp level_color,3h
			jne blue 
			MOV AL,4h 					 ;; red
			jmp con 
			
			blue:
			
			MOV AL,1h 					 ;; blue
			jmp con 
			 
			 con:
			MOV BH,00h 					 ;set the page number 
			INT 10h    					 ;execute the configuration
			
			INC CX     					 ;CX = CX + 1
			MOV AX,CX          	  		 ;CX - BALL_X > BALL_SIZE (Y -> We go to the next line,N -> We continue to the next column
			SUB AX,TEMP_X
			CMP AX,Target_SIZE
			JNG DRAW_BALL_HORIZONTAL
			
			MOV CX,TEMP_X 				 ;the CX register goes back to the initial column
			INC DX       				 ;we advance one line
			
			MOV AX,DX             		 ;DX - BALL_Y > BALL_SIZE (Y -> we exit this procedure,N -> we continue to the next line
			SUB AX,TEMP_Y
			CMP AX,Target_SIZE
			JNG DRAW_BALL_HORIZONTAL
		
		
      pop_all 
endm Draw_Target 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
 
;;---------------- Move Target -------------------------------
Move_Target macro TEMP_Xr , TEMP_Y ,W_W,START
          local  con_target 
           push_all
      MOV AX,Target_Velocity   ;MOVE THE BALL VERTICAL
    
    ADD TEMP_Xr,AX            ;the ADD to move the TARGET TO RIGHT
        
        MOV AX,W_W        
        CMP TEMP_Xr,AX 
                   
        
        Jl con_target   ;; IF LESS THAN WW CON TARGET
        
           initial_target TEMP_Xr, TEMP_Y,START
         
          con_target:
          
      pop_all    
endm Move_Target    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  

;;----------------  initial target    -------------------------------
initial_target macro TEMP_Xx ,TEMP_Y,START1
          ; local exit
           ;local first
           push_all  
           inc turn
           ;cmp turn, 5  ;; SET GUN 1 TO SWITCH PLAYER
           ;jne first
            ;mov gun,1
           
           ;first:
           
 MOV AX,START1          
           
 mov TEMP_Xx ,AX
mov	TEMP_Y , 15h
 inc level_color   ;; SWITCH COLOR
 ;cmp level_color,5h        ;; SWITCH TO INITIAL VALUE (0)
 ;jne exit
    ;  mov level_color,0h
; exit:          
 
 pop_all
endm initial_target

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;                 

;;----------------  Draw paddles    -------------------------------  
Draw_paddles   macro  
   	       local DRAW_PADDLE_RIGHT_HORIZONTAL
   	       local DRAW_PADDLE_LEFT_HORIZONTAL
	          push_all
	        MOV CX,PADDLE_LEFT_X 			 ;set the initial column (X)
		MOV DX,PADDLE_LEFT_Y 			 ;set the initial line (Y)
	
	DRAW_PADDLE_LEFT_HORIZONTAL:
			MOV AH,0Ch 		;12			 ;set the configuration to writing a pixel
			MOV AL,3h 		;15			 ;choose white as color
			MOV BH,00h 					 ;set the page number 
			INT 10h    					 ;execute the configuration
			
			INC CX     				 	 ;CX = CX + 1
			MOV AX,CX         			 ;CX - PADDLE_LEFT_X > PADDLE_WIDTH (Y -> We go to the next line,N -> We continue to the next column
			SUB AX,PADDLE_LEFT_X
			CMP AX,PADDLE_HEIGHT
			JNG DRAW_PADDLE_LEFT_HORIZONTAL
			
			MOV CX,PADDLE_LEFT_X 		 ;the CX register goes back to the initial column
			INC DX       				 ;we advance one line
			
			MOV AX,DX            	     ;DX - PADDLE_LEFT_Y > PADDLE_HEIGHT (Y -> we exit this procedure,N -> we continue to the next line
			SUB AX,PADDLE_LEFT_Y
			CMP AX,PADDLE_WIDTH
			JNG DRAW_PADDLE_LEFT_HORIZONTAL
			
			
		MOV CX,PADDLE_RIGHT_X 			 ;set the initial column (X)
		MOV DX,PADDLE_RIGHT_Y 			 ;set the initial line (Y)
		
			DRAW_PADDLE_RIGHT_HORIZONTAL:
			MOV AH,0Ch 					 ;set the configuration to writing a pixel
			MOV   AL,0Ch 	
			MOV BH,00h 					 ;set the page number 
			INT 10h    					 ;execute the configuration
			
			INC CX     					 ;CX = CX + 1
			MOV AX,CX         			 ;CX - PADDLE_RIGHT_X > PADDLE_WIDTH (Y -> We go to the next line,N -> We continue to the next column
			SUB AX,PADDLE_RIGHT_X
			CMP AX,PADDLE_HEIGHT
			JNG DRAW_PADDLE_RIGHT_HORIZONTAL
			
			MOV CX,PADDLE_RIGHT_X		 ;the CX register goes back to the initial column
			INC DX       				 ;we advance one line
			
			MOV AX,DX            	     ;DX - PADDLE_RIGHT_Y > PADDLE_HEIGHT (Y -> we exit this procedure,N -> we continue to the next line
			SUB AX,PADDLE_RIGHT_Y
			CMP AX,PADDLE_WIDTH
			JNG DRAW_PADDLE_RIGHT_HORIZONTAL
		
         pop_all
endm   Draw_paddles
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  


 ;;----------------  clac_point    -------------------------------
clac_point macro tg,tbl,ty,tr,tb,tp  
   local  less
   local   light_blue
   local   yellow
   local   red
   local   blue
   local   exit  
   local   exit_g 
   local   exit_lb  
   local   exit_y
   local   exit_r
   local   exit_b   
   
   push_all
             cmp   tp,100
             jl less
                
                 jmp exit  
                 
               less:
                 
                cmp  level_color,0h ;; green
                jne light_blue
                cmp tg,40 
                je  exit_g
                inc tg
                  add tp,1
     
                exit_g:
                 
                jmp exit
           
       light_blue:
                cmp  level_color,1h    ;; light blue 
                jne yellow
               
                cmp tbl,35 
                je  exit_lb 
                 inc tbl
               add tp,2
                exit_lb:
                  
                 jmp exit 
                 
        yellow: 
                cmp  level_color,2h   ;; yellow
                jne red
                
                cmp ty,30
                je  exit_y
               inc ty
                add tp,3
                 exit_y:  
                   
                 jmp exit 

         red: 
                cmp  level_color,3h   ;; red
                jne blue
               
                cmp tr,25 
                je  exit_r
                inc tr
                  add tp,4
                exit_r:  
                 
                jmp exit 
                
          blue:
                   
                cmp blue_color,20      ;; blue
                je  exit_b
                inc tb        
               add tp,5 
                exit_b:        
                 
               
      exit: 
            
            pop_all
   endm clac_point
;;;;;;;;;;;;;;;;;;;;;;;;;;;;    
    
 ;;----------------  CLEAR SCREEN    -------------------------------
CLEAR_SCREEN macro
        
         push_all
        MOV AH,00h
        MOV AL,13h
        INT 10h   
        pop_all
   endm CLEAR_SCREEN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;---------------- Draw Ball   -------------------------------
Draw_Ball macro   TEMP_X , TEMP_Y,co
                  local   DRAW_BALL_HORIZONTAL 
                  
                  push_all
		MOV CX,TEMP_X                    ;set the initial column (X)
		MOV DX,TEMP_Y                    ;set the initial line (Y)
		
		DRAW_BALL_HORIZONTAL:
			MOV AH,0Ch                   ;set the configuration to writing a pixel
			MOV AL,co 					 ;choose white as color
			MOV BH,00h 					 ;set the page number 
			INT 10h    					 ;execute the configuration
			
			INC CX     					 ;CX = CX + 1
			MOV AX,CX          	  		 ;CX - BALL_X > BALL_SIZE (Y -> We go to the next line,N -> We continue to the next column
			SUB AX,TEMP_X
			CMP AX,BALL_SIZE
			JNG DRAW_BALL_HORIZONTAL
			
			MOV CX,TEMP_X 				 ;the CX register goes back to the initial column
			INC DX       				 ;we advance one line
			
			MOV AX,DX             		 ;DX - BALL_Y > BALL_SIZE (Y -> we exit this procedure,N -> we continue to the next line
			SUB AX,TEMP_Y
			CMP AX,BALL_SIZE
			JNG DRAW_BALL_HORIZONTAL   
			
			pop_all
endm    Draw_Ball
		      
;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;---------------- MOVE BALL   -------------------------------
 MOVE_BALL macro TEMP_X , TEMP_Y , T_x, T_y ,P_x,P_y,T_START ,tgc,tblc,tyc,trc,tbc,tpc,gg  
                   LOCAL RESET_POSITION
                   LOCAL exit_c
                   LOCAL Ball_border
                   local  hit
                   local l1
                   local l2 
                   push_all
    
        MOV AX,BALL_VELOCITY_Y   ;MOVE THE BALL VERTICAL
        sub TEMP_Y,AX            ;the sub to move the ball up not down
        
       
                               
   ;;----------- check if hit target  -----------
         mov ax,21h 
         cmp TEMP_Y,ax 
        
          jng l1
          jmp Ball_border 
          
          
          l1:
         mov ax, T_x
         sub ax,5h 
         cmp TEMP_X, ax
        
          jnl  l2
           jmp Ball_border
           
          l2: 
         mov ax, T_x
         add ax,10h  
         cmp TEMP_X,ax
        
           jng hit
            jmp Ball_border
           
          hit:   
         clac_point  tgc,tblc,tyc,trc,tbc,tpc
        initial_target  T_x, T_y,T_START
         
         Ball_border:
        MOV AX,0fh        
        CMP TEMP_Y,AX 
        
         jl RESET_POSITION
        jmp exit_c
        
         RESET_POSITION:
            
             MOV DH,1h
           MOV gg,DH
             FIX_BALL_POSITION1 TEMP_X , TEMP_Y , P_x,P_y
                        
           
     
           exit_c:  
           pop_all
endm MOVE_BALL
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;
 
 ;;---------------- FIX BALL POSITION1   ------------------------------- 
  FIX_BALL_POSITION1  macro tEMP_X , tEMP_Y , p_x ,p_y
    
    push_all
        
        MOV BX,10h
      
      ADD BX,p_x
      MOV tEMP_X,BX ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
         
      
       
      MOV BX,p_y
      MOV tEMP_Y,BX  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
                    
                    pop_all
 endm FIX_BALL_POSITION1
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;           


  
 ;;----------------printnum2   ------------------------------- 
printnum2 macro num
    push_all
    mov ah,0
    mov al,num
    mov cl,10
    div cl
    
    mov dl,al
    mov dh,ah
    add dl,30h
    mov ah,2
    int 21h
    
    mov dl,dh
    add dl,30h
    mov ah,2
    int 21h  
    pop_all
endm printnum2        

;;;;;;;;;;;;;;;;;;;

 ;-----------------------------------------------------MOVE CURSOR----------------------------
 mov_cursor macro num       ;; Move Cursor       
      push_all
     mov ah,2 
mov bx,0
mov dx,num
int 10h    
pop_all
endm mov_cursor    
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;-----------------Initialization-----------------------
initgame macro 
    
    push_all
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
    
    pop_all
    
endm initgame     
;--------------------------------------------
;-------------Receive------------------------
receive1 macro    
    local Ball2
    local exit_p
    local MOVE_PADDLE1
    local MOVE_PADDLE2
    local MOVE_PADDLE3
    local MOVE_PADDLE4 
    local MOVE_PADDLE_RIGHT_DOWN 
    local MOVE_PADDLE_RIGHT_UP
    local MOVE_PADDLE_RIGHT_RIGHT
    local MOVE_PADDLE_RIGHT_LEFT
    local FIX_PADDLE_RIGHT_POSITION  
    local FIX_PADDLE_RIGHT_POSITION1
    local FIX_PADDLE_RIGHT_POSITION2
    local FIX_PADDLE_RIGHT_POSITION3
    local FIX_PADDLE_RIGHT_POSITION4
    local lol2
    local EXIT_PADDLE_MOVEMENT2
    local mmm
    ;local CHK
     push_all 
mov dx , 3FDh ; Line Status Register
In al , dx ;Read Line Status
;AND al , 00100000b
AND AL,1
;JZ CheckSend
jnz mmm
jmp exit_p
mmm:

mov dx , 3F8h ; Transmit data register
IN al,DX
MOV VALUE , al 
inc Di 

cmp VALUE,4Dh
JNE MOVE_PADDLE1 
    jmp MOVE_PADDLE_RIGHT_RIGHT 
       ;jmp exit_p
     MOVE_PADDLE1:
      
     
CMP VALUE,4Bh ;'s'
		JNE MOVE_PADDLE2
	    jmp MOVE_PADDLE_RIGHT_LEFT
		;jmp exit_p
		 
		MOVE_PADDLE2: 
		 
		CMP VALUE,48h 
		JNE MOVE_PADDLE3 
		jmp MOVE_PADDLE_RIGHT_UP
		;jmp exit_p
		MOVE_PADDLE3:
		CMP VALUE,50h 
		  		
	  JNE MOVE_PADDLE4
		jmp MOVE_PADDLE_RIGHT_DOWN  
		;jmp exit_p 
		 MOVE_PADDLE4:
		CMP VALUE,39H  
        ;JNE BALL2
         jne lol2
         jmp ball2
         lol2:
          		 
		  jmp EXIT_PADDLE_MOVEMENT2 
                   
;exit_p:  
 
;;;;;;;;;;;;;--------------------------------------------------

MOVE_PADDLE_RIGHT_RIGHT: 
	
	  	
	MOV AX,PADDLE_VELOCITY
			ADD PADDLE_RIGHT_X,AX
			
			MOV AX,WINDOW_WIDTH2
			CMP PADDLE_RIGHT_X,AX
			JL  FIX_PADDLE_RIGHT_POSITION1
			
			MOV AX,PADDLE_VELOCITY
			SUB PADDLE_RIGHT_X,AX
			
			 
			
			 FIX_PADDLE_RIGHT_POSITION1:
				
                      cmp gun2,1
                   
                    je  FIX_PADDLE_RIGHT_POSITION     
                    
	
	            JMP  EXIT_PADDLE_MOVEMENT2     
	
	
	MOVE_PADDLE_RIGHT_LEFT:
	
		
		
		         MOV AX,PADDLE_VELOCITY
                 SUB PADDLE_RIGHT_X,AX  
		        
	  
                MOV AX,LEFT_PADDEL_LIMIT_FROM_LEFT
                CMP PADDLE_RIGHT_X,AX
                Jg FIX_PADDLE_RIGHT_POSITION
                
                
                MOV AX,PADDLE_VELOCITY
                add PADDLE_RIGHT_X,AX     
                
                FIX_PADDLE_RIGHT_POSITION2:
			     
                  cmp gun2,1
                    
                    je  FIX_PADDLE_RIGHT_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT2   
	
	
	MOVE_PADDLE_RIGHT_UP: 
	
	 MOV AX,PADDLE_VELOCITY_Y
                SUB PADDLE_RIGHT_Y,AX  
		        
                MOV AX,WINDOW_HEIGHT_TOP
                CMP PADDLE_RIGHT_Y,AX
                Jg FIX_PADDLE_RIGHT_POSITION 
                
                
                
                
                
                MOV AX,PADDLE_VELOCITY_Y
                add PADDLE_RIGHT_Y,AX  
              
               FIX_PADDLE_RIGHT_POSITION3:  
                  cmp gun2,1
                    
                    je  FIX_PADDLE_RIGHT_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT2  
	
	MOVE_PADDLE_RIGHT_DOWN:
	   
	     MOV AX,PADDLE_VELOCITY_Y
                ADD PADDLE_RIGHT_Y,AX  
		
                MOV AX,WINDOW_HEIGHT_BOTTOM
                CMP PADDLE_RIGHT_Y,AX
                JL FIX_PADDLE_RIGHT_POSITION 
                
                
                
                
                
                MOV AX,PADDLE_VELOCITY_Y
                sub PADDLE_RIGHT_Y,AX  
                  FIX_PADDLE_RIGHT_POSITION4: 
                  cmp gun2,1
                    
                    je  FIX_PADDLE_RIGHT_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT2  
		
	 
	 FIX_PADDLE_RIGHT_POSITION:
		
                    
                    MOV BX,10h
                    ADD BX,PADDLE_RIGHT_X
                    MOV BALL2_X,BX
                   
                    MOV BX,PADDLE_RIGHT_Y
                    MOV BALL2_Y,BX   
				JMP EXIT_PADDLE_MOVEMENT2   
	
				
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;				
				
		
		
             
             
             EXIT_PADDLE_MOVEMENT2:
             
             
                    jmp exit_p
              Ball2:
                    
                   CMP bullet2,2
                   JE exit_p 
                   INC bullet2  
                   MOV DH,0  
                   MOV GUN2,DH     
      
             
                
                exit_p: 
                

pop_all

endm receive1



;--------------------------------------------------
;---------------------Send------------------------
 send1 macro       
   local BALL
   local exit_p
   local MOVE_PADDLE1
   local MOVE_PADDLE2
   local MOVE_PADDLE3
   local MOVE_PADDLE4  
   local MOVE_PADDLE_RIGHT
   local MOVE_PADDLE_LEFT
   local MOVE_PADDLE_DOWN
   local MOVE_PADDLE_UP
   local FIX_PADDLE_LEFT_BOTTOM_POSITION
   local FIX_PADDLE_LEFT_TOP_POSITION 
   local FIX_PADDLE_LEFT_TOP_POSITION0
   local FIX_PADDLE_LEFT_TOP_POSITION1
   local FIX_PADDLE_LEFT_TOP_POSITION2
   local mmm 
   local lol
   local EXIT_PADDLE_MOVEMENT
   ;local CheckSend
   
   push_all
mov dx , 3FDh ; Line Status Register
In al , dx ;Read Line Status
AND al , 00100000b
;AND AL,1
;JZ CheckSend
jnz mmm
jmp exit_p
mmm:

mov dx , 3F8h ; Transmit data register
MOV AL,VALUE 
OUT DX , AL 
;mov VALUE,AL
inc si 


cmp VALUE,4Dh
JNE MOVE_PADDLE1 
    jmp MOVE_PADDLE_RIGHT 
     ;jmp exit_p
     MOVE_PADDLE1:
      
     
        CMP VALUE,4Bh ;'s'
		JNE MOVE_PADDLE2
	    jmp MOVE_PADDLE_LEFT
		;jmp exit_p		 
		MOVE_PADDLE2: 
		 
		CMP VALUE,48h 
		JNE MOVE_PADDLE3 
		jmp MOVE_PADDLE_UP
		;jmp exit_p
		MOVE_PADDLE3:
	
		CMP VALUE,50h 		  		
	  JNE MOVE_PADDLE4
		jmp MOVE_PADDLE_DOWN  
		;jmp exit_p 
		 MOVE_PADDLE4:
		 
 CMP VALUE,39H  
        ;JNE BALL
        jne lol
        jmp BALL
        lol:  
        jmp EXIT_PADDLE_MOVEMENT
;;;----------------------------------------------------

 MOVE_PADDLE_RIGHT:
			MOV AX,PADDLE_VELOCITY
			ADD PADDLE_LEFT_X,AX
			
			MOV AX,WINDOW_WIDTH2
			CMP PADDLE_LEFT_X,AX
			JL FIX_PADDLE_LEFT_TOP_POSITION
			
			MOV AX,PADDLE_VELOCITY
			SUB PADDLE_LEFT_X,AX
			
			 
			
			FIX_PADDLE_LEFT_TOP_POSITION:
				
                      cmp gun,1
                   
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT
			
		MOVE_PADDLE_LEFT:
		         MOV AX,PADDLE_VELOCITY
                 SUB PADDLE_LEFT_X,AX  
		        
	  
                MOV AX,LEFT_PADDEL_LIMIT_FROM_LEFT
                CMP PADDLE_LEFT_X,AX
                Jg FIX_PADDLE_LEFT_BOTTOM_POSITION
                
                
                MOV AX,PADDLE_VELOCITY
                add PADDLE_LEFT_X,AX     
                
                FIX_PADDLE_LEFT_TOP_POSITION0:
			     
                  cmp gun,1
                    
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT   
				    
				    
				    
				    
				    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;up and down
         MOVE_PADDLE_UP:
		        
		        MOV AX,PADDLE_VELOCITY_Y
                SUB PADDLE_LEFT_Y,AX  
		        
                MOV AX,WINDOW_HEIGHT_TOP
                CMP PADDLE_LEFT_Y,AX
                Jg FIX_PADDLE_LEFT_BOTTOM_POSITION 
                
                
                
                
                
                MOV AX,PADDLE_VELOCITY_Y
                add PADDLE_LEFT_Y,AX  
              
              FIX_PADDLE_LEFT_TOP_POSITION1:  
                  cmp gun,1
                    
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT  				    
		
		MOVE_PADDLE_DOWN:     
		
		          MOV AX,PADDLE_VELOCITY_Y
                ADD PADDLE_LEFT_Y,AX  
		
                MOV AX,WINDOW_HEIGHT_BOTTOM
                CMP PADDLE_LEFT_Y,AX
                JL FIX_PADDLE_LEFT_BOTTOM_POSITION 
                
                
                
                
                
                MOV AX,PADDLE_VELOCITY_Y
                sub PADDLE_LEFT_Y,AX  
                 FIX_PADDLE_LEFT_TOP_POSITION2: 
                  cmp gun,1
                    
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT  
		
				    
				    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  
				    
				    
				    
				
        	
			FIX_PADDLE_LEFT_BOTTOM_POSITION:
		
                    
                    MOV BX,10h
                    ADD BX,PADDLE_LEFT_X
                    MOV BALL_X,BX
                   
                    MOV BX,PADDLE_LEFT_Y
                    MOV BALL_Y,BX   
				JMP EXIT_PADDLE_MOVEMENT       
				
				
				
	EXIT_PADDLE_MOVEMENT:
		       jmp exit_p     
		            
              Ball:
                    
                    CMP bullet,2
                    JE exit_p 
                  INC bullet  
                   MOV DH,0  
                   MOV GUN,DH     
                
                
               
           exit_p:  			

pop_all

endm send1 
;;;;--------------------------------------------------------

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;								
;--------------------------------------------------
;---------------------SendOFRIGHTPLAYER------------------------
 send2 macro       
    local Ball2
    local exit_p
    local MOVE_PADDLE1
    local MOVE_PADDLE2
    local MOVE_PADDLE3
    local MOVE_PADDLE4 
    local MOVE_PADDLE_RIGHT_DOWN 
    local MOVE_PADDLE_RIGHT_UP
    local MOVE_PADDLE_RIGHT_RIGHT
    local MOVE_PADDLE_RIGHT_LEFT
    local FIX_PADDLE_RIGHT_POSITION  
    local FIX_PADDLE_RIGHT_POSITION1
    local FIX_PADDLE_RIGHT_POSITION2
    local FIX_PADDLE_RIGHT_POSITION3
    local FIX_PADDLE_RIGHT_POSITION4
    local lol2
    local EXIT_PADDLE_MOVEMENT2
    local mmm
    ;local CHK
     push_all 
mov dx , 3FDh ; Line Status Register
In al , dx ;Read Line Status
AND al , 00100000b
;AND AL,1
;JZ CheckSend
jnz mmm
jmp exit_p
mmm:

mov dx , 3F8h ; Transmit data register
MOV AL,VALUE 
OUT DX , AL 
;mov VALUE,AL
inc si 


cmp VALUE,4Dh
JNE MOVE_PADDLE1 
    jmp MOVE_PADDLE_RIGHT_RIGHT 
       ;jmp exit_p
     MOVE_PADDLE1:
      
     
CMP VALUE,4Bh ;'s'
		JNE MOVE_PADDLE2
	    jmp MOVE_PADDLE_RIGHT_LEFT
		;jmp exit_p
		 
		MOVE_PADDLE2: 
		 
		CMP VALUE,48h 
		JNE MOVE_PADDLE3 
		jmp MOVE_PADDLE_RIGHT_UP
		;jmp exit_p
		MOVE_PADDLE3:
		CMP VALUE,50h 
		  		
	  JNE MOVE_PADDLE4
		jmp MOVE_PADDLE_RIGHT_DOWN  
		;jmp exit_p 
		 MOVE_PADDLE4:
		CMP VALUE,39H  
        ;JNE BALL2
         jne lol2
         jmp ball2
         lol2:
          		 
		  jmp EXIT_PADDLE_MOVEMENT2 
                   
;exit_p:  
 
;;;;;;;;;;;;;--------------------------------------------------

MOVE_PADDLE_RIGHT_RIGHT: 
	
	  	
	MOV AX,PADDLE_VELOCITY
			ADD PADDLE_RIGHT_X,AX
			
			MOV AX,WINDOW_WIDTH2
			CMP PADDLE_RIGHT_X,AX
			JL  FIX_PADDLE_RIGHT_POSITION1
			
			MOV AX,PADDLE_VELOCITY
			SUB PADDLE_RIGHT_X,AX
			
			 
			
			 FIX_PADDLE_RIGHT_POSITION1:
				
                      cmp gun2,1
                   
                    je  FIX_PADDLE_RIGHT_POSITION     
                    
	
	            JMP  EXIT_PADDLE_MOVEMENT2     
	
	
	MOVE_PADDLE_RIGHT_LEFT:
	
		
		
		         MOV AX,PADDLE_VELOCITY
                 SUB PADDLE_RIGHT_X,AX  
		        
	  
                MOV AX,LEFT_PADDEL_LIMIT_FROM_LEFT
                CMP PADDLE_RIGHT_X,AX
                Jg FIX_PADDLE_RIGHT_POSITION
                
                
                MOV AX,PADDLE_VELOCITY
                add PADDLE_RIGHT_X,AX     
                
                FIX_PADDLE_RIGHT_POSITION2:
			     
                  cmp gun2,1
                    
                    je  FIX_PADDLE_RIGHT_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT2   
	
	
	MOVE_PADDLE_RIGHT_UP: 
	
	 MOV AX,PADDLE_VELOCITY_Y
                SUB PADDLE_RIGHT_Y,AX  
		        
                MOV AX,WINDOW_HEIGHT_TOP
                CMP PADDLE_RIGHT_Y,AX
                Jg FIX_PADDLE_RIGHT_POSITION 
                
                
                
                
                
                MOV AX,PADDLE_VELOCITY_Y
                add PADDLE_RIGHT_Y,AX  
              
               FIX_PADDLE_RIGHT_POSITION3:  
                  cmp gun2,1
                    
                    je  FIX_PADDLE_RIGHT_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT2  
	
	MOVE_PADDLE_RIGHT_DOWN:
	   
	     MOV AX,PADDLE_VELOCITY_Y
                ADD PADDLE_RIGHT_Y,AX  
		
                MOV AX,WINDOW_HEIGHT_BOTTOM
                CMP PADDLE_RIGHT_Y,AX
                JL FIX_PADDLE_RIGHT_POSITION 
                
                
                
                
                
                MOV AX,PADDLE_VELOCITY_Y
                sub PADDLE_RIGHT_Y,AX  
                  FIX_PADDLE_RIGHT_POSITION4: 
                  cmp gun2,1
                    
                    je  FIX_PADDLE_RIGHT_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT2  
		
	 
	 FIX_PADDLE_RIGHT_POSITION:
		
                    
                    MOV BX,10h
                    ADD BX,PADDLE_RIGHT_X
                    MOV BALL2_X,BX
                   
                    MOV BX,PADDLE_RIGHT_Y
                    MOV BALL2_Y,BX   
				JMP EXIT_PADDLE_MOVEMENT2   
	
				
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;				
				             
             
             EXIT_PADDLE_MOVEMENT2:
             
             
                    jmp exit_p
              Ball2:
                    
                   CMP bullet2,2
                   JE exit_p 
                   INC bullet2  
                   MOV DH,0  
                   MOV GUN2,DH     
      
             
                
                exit_p: 
                
;;;;;;;;;;;;;--------------------------------------------------

pop_all

endm send2 		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;-------------ReceiveOF RIGHT PLAYER------------------------
receive2 macro    
   local BALL
   local exit_p
   local MOVE_PADDLE1
   local MOVE_PADDLE2
   local MOVE_PADDLE3
   local MOVE_PADDLE4  
   local MOVE_PADDLE_RIGHT
   local MOVE_PADDLE_LEFT
   local MOVE_PADDLE_DOWN
   local MOVE_PADDLE_UP
   local FIX_PADDLE_LEFT_BOTTOM_POSITION
   local FIX_PADDLE_LEFT_TOP_POSITION 
   local FIX_PADDLE_LEFT_TOP_POSITION0
   local FIX_PADDLE_LEFT_TOP_POSITION1
   local FIX_PADDLE_LEFT_TOP_POSITION2
   local mmm 
   local lol
   local EXIT_PADDLE_MOVEMENT
     
   push_all
mov dx , 3FDh ; Line Status Register
In al , dx ;Read Line Status
;AND al , 00100000b
AND AL,1
;JZ CheckSend
jnz mmm
jmp exit_p
mmm:

mov dx , 3F8h ; Transmit data register
IN al,DX
MOV VALUE , al 
inc Di 


cmp VALUE,4Dh
JNE MOVE_PADDLE1 
    jmp MOVE_PADDLE_RIGHT 
     ;jmp exit_p
     MOVE_PADDLE1:
      
     
        CMP VALUE,4Bh ;'s'
		JNE MOVE_PADDLE2
	    jmp MOVE_PADDLE_LEFT
		;jmp exit_p		 
		MOVE_PADDLE2: 
		 
		CMP VALUE,48h 
		JNE MOVE_PADDLE3 
		jmp MOVE_PADDLE_UP
		;jmp exit_p
		MOVE_PADDLE3:
	
		CMP VALUE,50h 		  		
	  JNE MOVE_PADDLE4
		jmp MOVE_PADDLE_DOWN  
		;jmp exit_p 
		 MOVE_PADDLE4:
		 
 CMP VALUE,39H  
        ;JNE BALL
        jne lol
        jmp BALL
        lol:  
        jmp EXIT_PADDLE_MOVEMENT
;;;----------------------------------------------------

 MOVE_PADDLE_RIGHT:
			MOV AX,PADDLE_VELOCITY
			ADD PADDLE_LEFT_X,AX
			
			MOV AX,WINDOW_WIDTH2
			CMP PADDLE_LEFT_X,AX
			JL FIX_PADDLE_LEFT_TOP_POSITION
			
			MOV AX,PADDLE_VELOCITY
			SUB PADDLE_LEFT_X,AX
			
			 
			
			FIX_PADDLE_LEFT_TOP_POSITION:
				
                      cmp gun,1
                   
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT
			
		MOVE_PADDLE_LEFT:
		         MOV AX,PADDLE_VELOCITY
                 SUB PADDLE_LEFT_X,AX  
		        
	  
                MOV AX,LEFT_PADDEL_LIMIT_FROM_LEFT
                CMP PADDLE_LEFT_X,AX
                Jg FIX_PADDLE_LEFT_BOTTOM_POSITION
                
                
                MOV AX,PADDLE_VELOCITY
                add PADDLE_LEFT_X,AX     
                
                FIX_PADDLE_LEFT_TOP_POSITION0:
			     
                  cmp gun,1
                    
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT   
				    

				    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;up and down
         MOVE_PADDLE_UP:
		        
		        MOV AX,PADDLE_VELOCITY_Y
                SUB PADDLE_LEFT_Y,AX  
		        
                MOV AX,WINDOW_HEIGHT_TOP
                CMP PADDLE_LEFT_Y,AX
                Jg FIX_PADDLE_LEFT_BOTTOM_POSITION 
                
                
                
                
                
                MOV AX,PADDLE_VELOCITY_Y
                add PADDLE_LEFT_Y,AX  
              
              FIX_PADDLE_LEFT_TOP_POSITION1:  
                  cmp gun,1
                    
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT  				    
		
		MOVE_PADDLE_DOWN:     
		
		          MOV AX,PADDLE_VELOCITY_Y
                ADD PADDLE_LEFT_Y,AX  
		
                MOV AX,WINDOW_HEIGHT_BOTTOM
                CMP PADDLE_LEFT_Y,AX
                JL FIX_PADDLE_LEFT_BOTTOM_POSITION 
                
                
                
                
                
                MOV AX,PADDLE_VELOCITY_Y
                sub PADDLE_LEFT_Y,AX  
                 FIX_PADDLE_LEFT_TOP_POSITION2: 
                  cmp gun,1
                    
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT  
		
				    
				    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  

			FIX_PADDLE_LEFT_BOTTOM_POSITION:
		
                    
                    MOV BX,10h
                    ADD BX,PADDLE_LEFT_X
                    MOV BALL_X,BX
                   
                    MOV BX,PADDLE_LEFT_Y
                    MOV BALL_Y,BX   
				JMP EXIT_PADDLE_MOVEMENT       
				
				
				
	EXIT_PADDLE_MOVEMENT:
		       jmp exit_p     
		            
              Ball:
                    
                    CMP bullet,2
                    JE exit_p 
                  INC bullet  
                   MOV DH,0  
                   MOV GUN,DH     
                
                
               
           exit_p:  			
				
pop_all

endm receive2






;-----------------------------------------------PRINT MSG

;printmsg macro msg       
 ;   push_all
  ;  mov ah,9
  ;  mov dx,offset msg
   ; int 21h     
   ; pop_all
;endm printmsg

;-----------------------------------CLEAR
;clear macro                     ;; Clear string 
 ;    push_all
  ;  mov ax,0600h
   ; mov bh,07
   ; mov cx,0
   ; mov dx,184FH
   ; int 10h  
   ; pop_all
;endm clear

;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;