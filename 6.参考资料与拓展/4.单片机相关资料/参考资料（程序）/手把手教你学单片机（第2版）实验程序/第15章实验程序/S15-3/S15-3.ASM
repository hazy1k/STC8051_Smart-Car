	ORG 0000H
	AJMP MAIN
	ORG 030H
MAIN:	MOV P0,#00H
	ACALL DEL10S
	ACALL KEY
	MOV P0,#0FFH
	ACALL DEL10S
	ACALL KEY
	AJMP MAIN
KEY:	JB P3.0,RE
	CPL C
	JC NEXT1
	MOV P1,#00H
	AJMP NEXT2
NEXT1:	MOV P1,#0FFH
NEXT2:	ACALL DEL1S
RE:	RET
DEL1S:	MOV R5,#0FFH
F1:	MOV R6,#0FFH
F2:	DJNZ R6,F2
	DJNZ R5,F1
	RET
DEL10S:	MOV R0,0AH
LOOP:	ACALL DEL1S
	DJNZ R0,LOOP
	RET
	END
