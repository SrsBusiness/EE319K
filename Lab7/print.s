; print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for the Kentec EB-LM4F120-L35
;
; As part of Lab 7, students need to implement these two functions

;  Data pin assignments:
;  PB0-7   LCD parallel data input
;
;  Control pin assignments:
;  PA4     RD  Read control signal             -------------------------
;  PA5     WR  Write control signal            | PA7 | PA6 | PA5 | PA4 |
;  PA6     RS  Register/Data select signal     | CS  | RS  | WR  | RD  |
;  PA7     CS  Chip select signal              -------------------------
;
;  Touchpad pin assignments:
;  PA2     Y-                                  -------------  -------------
;  PA3     X-                                  | PA3 | PA2 |  | PE5 | PE4 |
;  PE4     X+    AIN9                          | X-  | Y-  |  | Y+  | X+  |
;  PE5     Y+    AIN8  
                    

	PRESERVE8
    IMPORT   LCD_OutChar
    IMPORT   LCD_Goto
    IMPORT   LCD_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix
	
local 	EQU 0
step1	EQU 0
step2	EQU 4
step3	EQU 8
step4	EQU 12



    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
    ALIGN          

	
;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number 
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
		PUSH  	{R4-R11, LR}
		SUB		SP, #4
		MOV		R4, SP
		CMP 	R0, #10
		BLO		output
		MOV 	R2, #10
		UDIV	R3, R0, R2
		MUL		R1, R3, R2
		SUB		R1, R0, R1
		STR		R1, [R4, #local]		;PUSH	{R1}
		MOVS 	R0, R3
		BL		LCD_OutDec
		LDR		R0, [R4, #local]		;POP 	{R0}
output	ADD		R0, R0, #0x30
		PUSH 	{R0-R3}
		BL		LCD_OutChar
		POP		{R0-R3}
		ADD		SP, #4
		POP		{R4-R11, LR}
		BX  	LR
;* * * * * * * * End of LCD_OutDec * * * * * * * * 

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999 
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 " 
;       R0=3,    then output "0.003 " 
;       R0=89,   then output "0.089 " 
;       R0=123,  then output "0.123 " 
;       R0=9999, then output "9.999 " 
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
		PUSH  	{R4-R11, LR}
		MOV		R1, #9999
		CMP		R0, R1			
		BHI		GREATER				
		SUB 	SP, #16				
		MOV		R2, #10				
		
		UDIV	R1, R0, R2			;R1 = x/10
		MUL		R4, R1, R2			;R1 = (x/10)*10
		SUB		R3, R0, R4			;R3 = ORIG - (x/10)*10
		ADD		R3, R3, #0x30		;make ascii
	    STR		R3, [SP, #step1]	;store in stack
		MOV		R0, R1
		
		
		UDIV	R1, R0, R2			;R1 = x/10
		MUL		R4, R1, R2			;R1 = (x/10)*10
		SUB		R3, R0, R4			;R3 = ORIG - (x/10)*10
		ADD		R3, R3, #0x30		;make ascii
	    STR		R3, [SP, #step2]	;store in stack
		MOV		R0, R1
		
		UDIV	R1, R0, R2			;R1 = x/10
		MUL		R4, R1, R2			;R1 = (x/10)*10
		SUB		R3, R0, R4			;R3 = ORIG - (x/10)*10
		ADD		R3, R3, #0x30		;make ascii
	    STR		R3, [SP, #step3]	;store in stack
		MOV		R0, R1
		
		UDIV	R1, R0, R2			;R1 = x/10
		MUL		R4, R1, R2			;R1 = (x/10)*10
		SUB		R3, R0, R4			;R3 = ORIG - (x/10)*10
		ADD		R3, R3, #0x30		;make ascii
	    STR		R3, [SP, #step4]	;store in stack
		MOV		R0, R1
		
		LDR		R0, [SP, #step4]
		PUSH 	{R0}
		BL		LCD_OutChar
		POP		{R0}
		
		MOV 	R0, #'.'
		BL		LCD_OutChar
		
		LDR		R0, [SP, #step3]
		BL		LCD_OutChar
		
		LDR		R0, [SP, #step2]
		BL		LCD_OutChar
		
		LDR		R0, [SP, #step1]
		BL		LCD_OutChar
		ADD	SP, #16
		B done
		
		
		
		
GREATER	
		MOV R0, #'*'
		PUSH 	{R0}
		BL		LCD_OutChar
		POP		{R0}
		
		MOV 	R0, #'.'
		PUSH 	{R0}
		BL		LCD_OutChar
		POP		{R0}
		
		MOV R0, #'*'
		PUSH 	{R0}
		BL		LCD_OutChar
		POP		{R0}
		
		MOV R0, #'*'
		PUSH 	{R0}
		BL		LCD_OutChar
		POP		{R0}
		
		MOV R0, #'*'
		PUSH 	{R0}
		BL		LCD_OutChar
		POP		{R0}

done	
		POP 	{R4-R11, LR}
		BX  LR
;* * * * * * * * End of LCD_OutFix * * * * * * * * 

   
    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file
    
