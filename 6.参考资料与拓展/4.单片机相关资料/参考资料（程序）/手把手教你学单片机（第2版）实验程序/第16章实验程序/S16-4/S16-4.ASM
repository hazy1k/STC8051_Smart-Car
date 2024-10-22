	FLAG BIT 25H.0
	DI_DA DATA 20H
	SEC DATA 21H
	MIN DATA 22H
	HOUR DATA 23H
;*************************
	ORG 0000H
	LJMP MAIN
	ORG 000BH
	LJMP CLOCK
	ORG 030H
MAIN:	MOV TMOD,#01H
	MOV TL0,#0B0H
	MOV TH0,#3CH
	SETB ET0
	SETB TR0
	MOV DI_DA,#00H
	SETB EA
BEGIN:	MOV P3,#7FH
	MOV A,P3
	CJNE A,#7FH,NEXT
	SETB P3.7
	ACALL CONV
	ACALL DIS
	JB FLAG,FLAG_SEC
	SETB P2.7
	AJMP BEGIN
FLAG_SEC:CLR P2.7
	AJMP BEGIN
NEXT:	ACALL KEY
	AJMP BEGIN
;***********************
KEY:	ACALL DEL10MS
	JB P3.0,HOUR_KEY
MIN_ADJ:CLR C
	MOV A,MIN
	INC A
	DA A
	CJNE A,#60H,X1
	CLR A
X1:	MOV MIN,A
	ACALL DIS
	ACALL DEL200MS
	MOV P3,#7FH
	JNB P3.0,MIN_ADJ
HOUR_KEY:JB P3.1,X2
HOUR_ADJ:CLR C
	MOV A,HOUR
	INC A
	DA A
	CJNE A,#24H,X3
	CLR A
X3:	MOV HOUR,A
	ACALL DIS
	ACALL DEL200MS
X2:	MOV P3,#7FH
	JNB P3.1,HOUR_ADJ
	SETB P3.7
	RET
;***********************
CONV:	MOV A,DI_DA
	CJNE A,#0AH,F1
	SETB FLAG
F1:	CJNE A,#14H,DONE
	CLR FLAG
	MOV DI_DA,#00H
	MOV A,SEC
	ADD A,#01H
	DA A
	MOV SEC,A
	CJNE A,#60H,DONE
	MOV SEC,#00H
	MOV A,MIN
	ADD A,#01H
	DA A
	MOV MIN,A
	CJNE A,#60H,DONE
	MOV MIN,#00H
	MOV A,HOUR
	ADD A,#01H
	DA A
	MOV HOUR,A
	CJNE A,#24H,DONE
	MOV HOUR,#00H
DONE:	RET
;***********************
DIS:	MOV A,MIN
	ANL A,#0FH
	MOV DPTR,#TAB
	MOVC A,@A+DPTR
	MOV P0,A
	ACALL DEL1MS
	MOV A,MIN
	SWAP  A
	ANL A,#0FH
	MOVC A,@A+DPTR
	MOV P1,A
	ACALL DEL1MS
	MOV A,HOUR
	ANL A,#0FH
	MOVC A,@A+DPTR
	MOV P2,A
	ACALL DEL1MS
	MOV A,HOUR
	SWAP  A
	ANL A,#0FH
	MOVC A,@A+DPTR
	MOV P3,A
	ACALL DEL1MS
	RET
;**********************
CLOCK:	MOV TL0,#0B0H
	MOV TH0,#3CH
	INC DI_DA
	RETI
;***************************
DEL1MS:MOV R6,#02H
DEL1:	MOV R7,#0FFH
	DJNZ R7,$
	DJNZ R6,DEL1
	RET
DEL10MS:MOV R5,#10H
TX1:	MOV R4,#0FFH
	DJNZ R4,$
	DJNZ R5,TX1
	RET
DEL200MS:MOV R3,#14H
TX2:	ACALL DEL10MS
	DJNZ R3,TX2
	RET
;***************************
TAB:	DB 0C0H,0F9H,0A4H,0B0H,099H,092H,082H,0F8H
	DB 080H,090H,088H,083H,0C6H,0A1H,086H,08EH
	END
	
