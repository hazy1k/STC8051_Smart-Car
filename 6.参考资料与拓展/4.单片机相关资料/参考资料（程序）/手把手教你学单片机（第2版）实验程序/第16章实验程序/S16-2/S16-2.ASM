	ORG 0000H
	LJMP MAIN
	ORG 030H
MAIN:	MOV P3,# 0F9H
	ACALL DEL0_5S
	MOV P3,#0FFH
	MOV P2,# 0A4H
	ACALL DEL0_5S
	MOV P2,#0FFH
	MOV P1,#0B0H
	ACALL DEL0_5S
	MOV P1,#0FFH
	MOV P0,#99H
	ACALL DEL0_5S
	MOV P0,#0FFH
	AJMP MAIN
DEL0_5S:MOV R5,#04H
DEL1:	MOV R6,#0FFH
DEL2:	MOV R7,#0FFH
DEL3:	DJNZ R7,DEL3
	DJNZ R6,DEL2
	DJNZ R5,DEL1
	RET
	END
