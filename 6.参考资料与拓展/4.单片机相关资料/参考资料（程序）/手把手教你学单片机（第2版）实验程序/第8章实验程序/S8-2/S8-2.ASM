	ORG 0000H
	LJMP MAIN
	ORG 030H
MAIN:	MOV A,#59H
        ANL A,#0FH
       	SWAP A
	ANL P1,#0FH
	ORL P1,A
	ACALL DEL
	AJMP MAIN
DEL: 	MOV R7,#0FFH
DEL1:	MOV R6,#0FFH
DEL2:   MOV R5,#01FH
DEL3:	DJNZ R5,DEL3
	DJNZ R6,DEL2
	DJNZ R7,DEL1
	RET
	END
