		WDTRST EQU 0A6H
		ORG 0000H
		LJMP START
		ORG 030H
START:MOV WDTRST,#01EH
		MOV WDTRST,#0E1H
		;*****************
MAIN:	MOV R0,#08H
		CLR C
		MOV A,#0FFH
PLAYP1:RLC A
		MOV P1,A
		ACALL D10MS
		CLR C
		DJNZ R0, PLAYP1
		;***************
		MOV R0,#08H
		CLR C
		MOV A,#0FFH
PLAYP3:RLC A
		MOV P3,A
		ACALL D10MS
		CLR C
		DJNZ R0, PLAYP3
		;***************
		MOV R0,#08H
		CLR C
		MOV A,#0FFH
PLAYP2:RLC A
		MOV P2,A
		ACALL D10MS
		CLR C
		DJNZ R0, PLAYP2
		;***************
		MOV R0,#08H
		CLR C
		MOV A,#0FFH
PLAYP0:RRC A
		MOV P0,A
		ACALL D10MS
		CLR C
		DJNZ R0, PLAYP0
		;***************
		MOV P0,#0FFH
		MOV P1,#0FFH
		MOV P2,#0FFH
		MOV P3,#0FFH
		AJMP MAIN
		;***************
D10MS:MOV R7,#18
DEL1:	MOV R6,#255
DEL2:	DJNZ R6,DEL2
		DJNZ R7,DEL1
		RET
		END
