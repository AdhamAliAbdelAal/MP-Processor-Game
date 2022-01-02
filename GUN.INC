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
           local exit
           local first
           push_all  
           inc turn
           cmp turn, 5  ;; SET GUN 1 TO SWITCH PLAYER
           jne first
            mov gun,1
           
           first:
           
 MOV AX,START1          
           
 mov TEMP_Xx ,AX
mov	TEMP_Y , 15h
 inc level_color   ;; SWITCH COLOR
 cmp level_color,5h        ;; SWITCH TO INITIAL VALUE (0)
 jne exit
      mov level_color,0h
 exit:          
 
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
			MOV AL,0Fh 		;15			 ;choose white as color
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
			MOV AL,0Fh 					 ;choose white as color
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

;;----------------  Move paddles    -------------------------------
 MOVE_PADDLES macro TEMP_X , TEMP_Y , b_x, b_y ,W_W ,LEFT_LIMIT ,NUMOFBALLS
                       local EXIT_PADDLE_MOVEMENT  
                       local MOVE_PADDLE_LEFT  
                       local FIX_PADDLE_LEFT_TOP_POSITION    
                       local FIX_PADDLE_LEFT_BOTTOM_POSITION
                       local MOVE_PADDLE_RIGHT 
                       local Ball   
                       local exit_p  
                       local MOVE_PADDLE_UP
                       local MOVE_PADDLE_DOWN
                       local momo 
                       local lol                      
                       local FIX_PADDLE_LEFT_TOP_POSITION0
                       local FIX_PADDLE_LEFT_TOP_POSITION1
                       local FIX_PADDLE_LEFT_TOP_POSITION2
                       push_all
           ;       Left paddle movement
		
		;check if any key is being pressed (if not check the other paddle)
		MOV AH,01h
		INT 16h
		JZ momo ;ZF = 1, JZ -> Jump If Zero
		
		;check which key is being pressed (AL = ASCII character)
		MOV AH,00h
		INT 16h
		
		;if it is '' or 'W' move up
		CMP AH,4Dh ;'w'
		JE MOVE_PADDLE_RIGHT
		;CMP AL,57h ;'W'
		;JE MOVE_LEFT_PADDLE_RIGHT
		
		;if it is 's' or 'S' move down
		CMP AH,4Bh ;'s'
		JE MOVE_PADDLE_LEFT
	;	CMP AL,53h ;'S'
		;JE MOVE_LEFT_PADDLE_LEFT
		
		CMP AH,48h 
		JE MOVE_PADDLE_UP 
		
		
		CMP AH,50h 
		JE MOVE_PADDLE_DOWN
		
		
		 CMP AL,20H  
		 
		  JE lol
		    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
		    
		    momo:
		    
		  JMP EXIT_PADDLE_MOVEMENT
		  
		  lol:
		  jmp BALL  
		  
		MOVE_PADDLE_RIGHT:
			MOV AX,PADDLE_VELOCITY
			ADD TEMP_X,AX
			
			MOV AX,W_W
			CMP TEMP_X,AX
			JL FIX_PADDLE_LEFT_TOP_POSITION
			
			MOV AX,PADDLE_VELOCITY
			SUB TEMP_X,AX
			
			 
			
			FIX_PADDLE_LEFT_TOP_POSITION:
				
                      cmp gun,1
                   
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT
			
		MOVE_PADDLE_LEFT:
		         MOV AX,PADDLE_VELOCITY
                 SUB TEMP_X,AX  
		        
	  
                MOV AX,LEFT_LIMIT
                CMP TEMP_X,AX
                Jg FIX_PADDLE_LEFT_BOTTOM_POSITION
                
                
                MOV AX,PADDLE_VELOCITY
                add TEMP_X,AX     
                
                FIX_PADDLE_LEFT_TOP_POSITION0:
			     
                  cmp gun,1
                    
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT   
				    
				    
				    
				    
				    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;up and down
         MOVE_PADDLE_UP:
		        
		        MOV AX,PADDLE_VELOCITY_Y
                SUB TEMP_Y,AX  
		        
                MOV AX,WINDOW_HEIGHT_TOP
                CMP TEMP_Y,AX
                Jg FIX_PADDLE_LEFT_BOTTOM_POSITION 
                
                
                
                
                
                MOV AX,PADDLE_VELOCITY_Y
                add TEMP_Y,AX  
              
              FIX_PADDLE_LEFT_TOP_POSITION1:  
                  cmp gun,1
                    
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT  				    
		
		MOVE_PADDLE_DOWN:     
		
		          MOV AX,PADDLE_VELOCITY_Y
                ADD TEMP_Y,AX  
		
                MOV AX,WINDOW_HEIGHT_BOTTOM
                CMP TEMP_Y,AX
                JL FIX_PADDLE_LEFT_BOTTOM_POSITION 
                
                
                
                
                
                MOV AX,PADDLE_VELOCITY_Y
                sub TEMP_Y,AX  
                 FIX_PADDLE_LEFT_TOP_POSITION2: 
                  cmp gun,1
                    
                    je  FIX_PADDLE_LEFT_BOTTOM_POSITION     
                    
				    jmp  EXIT_PADDLE_MOVEMENT  
		
				    
				    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        	
			FIX_PADDLE_LEFT_BOTTOM_POSITION:
		
                    
                    MOV BX,10h
                    ADD BX,TEMP_X
                    MOV b_x,BX
                   
                    MOV BX,TEMP_Y
                    MOV b_y,BX   
				JMP EXIT_PADDLE_MOVEMENT
				
				
		
		EXIT_PADDLE_MOVEMENT:
		            
		            jmp exit_p
              Ball:
                    
                    CMP NUMOFBALLS,4
                    JE exit_p 
                  INC NUMOFBALLS  
                   MOV DH,0  
                   MOV GUN,DH     
                
                exit_p:
          
               pop_all
 endm MOVE_PADDLES
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
Draw_Ball macro   TEMP_X , TEMP_Y
                  local   DRAW_BALL_HORIZONTAL 
                  
                  push_all
		MOV CX,TEMP_X                    ;set the initial column (X)
		MOV DX,TEMP_Y                    ;set the initial line (Y)
		
		DRAW_BALL_HORIZONTAL:
			MOV AH,0Ch                   ;set the configuration to writing a pixel
			MOV AL,0Fh 					 ;choose white as color
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
 MOVE_BALL macro TEMP_X , TEMP_Y , T_x, T_y ,P_x,P_y,T_START ,tgc,tblc,tyc,trc,tbc,tpc  
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
           MOV GUN,DH
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
;;----------------------------DRAW VERTICAL LINE ---------------------

DRAW_LINE MACRO   
    
    push_all

         MOV CX,160
           MOV DX,0
           MOV AL,5
           MOV AH,0Ch
           
           BACK:INT 10h
           INC DX
           CMP DX, 150
           JNZ BACK       
    
          pop_all
ENDM DRAW_LINE    