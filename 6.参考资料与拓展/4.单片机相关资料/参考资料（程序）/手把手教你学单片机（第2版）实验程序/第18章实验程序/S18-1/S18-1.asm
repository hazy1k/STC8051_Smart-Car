;********89C51���Ŷ���********
	RS BIT P3.3
	R_W BIT P3.4
	E BIT P3.5
	DB0_DB7 EQU P1
;*******����ʼ********
	ORG 0000H
	LJMP MAIN
;*******������ʼ*******
	ORG 0030H
MAIN:	MOV SP,#70H
;*******LCM��ʼ��*******
	MOV A,#00111000B
;-----------��LCMæµ-----------
	PUSH ACC
BUSY_LOOP:	CLR E
	SETB R_W
	CLR RS
	SETB E
	MOV A, DB0_DB7
	CLR E
	JB ACC.7,BUSY_LOOP
	POP ACC
	LCALL DEL
;----------дָ�LCM---------
	CLR E
	CLR R_W
	CLR RS
	SETB E
	MOV DB0_DB7,A
	CLR E
;***************************
	MOV A,#00001110B
;-----------��LCMæµ-----------
	PUSH ACC
BUSY_LOOP1:	CLR E
	SETB R_W
	CLR RS
	SETB E
	MOV A, DB0_DB7
	CLR E
	JB ACC.7,BUSY_LOOP1
	POP ACC
	LCALL DEL
;----------дָ�LCM------------
	CLR E
	CLR R_W
	CLR RS
	SETB E
	MOV DB0_DB7,A
	CLR E
;***************************
	MOV A,#00000110B
;-----------��LCMæµ------------
	PUSH ACC
BUSY_LOOP2:	CLR E
	SETB R_W
	CLR RS
	SETB E
	MOV A, DB0_DB7
	CLR E
	JB ACC.7,BUSY_LOOP2
	POP ACC
	LCALL DEL
;-----------дָ�LCM-------------
	CLR E
	CLR R_W
	CLR RS
	SETB E
	MOV DB0_DB7,A
	CLR E
;*******LCM��ʼ������*******
;****�趨��ʾ��ַ��д��LCM****
	MOV A,#10000000B
;-----------��LCMæµ-----------
	PUSH ACC
BUSY_LOOP3:	CLR E
	SETB R_W
	CLR RS
	SETB E
	MOV A, DB0_DB7
	CLR E
	JB ACC.7,BUSY_LOOP3
	POP ACC
	LCALL DEL
;-----------дָ�LCM------------
	CLR E
	CLR R_W
	CLR RS
	SETB E
	MOV DB0_DB7,A
	CLR E
;****����ʾ�ַ���ASCII��д��LCM****
	MOV A,#41H
;------------��LCMæµ-------------
	PUSH ACC
BUSY_LOOP4:	CLR E
	SETB R_W
	CLR RS
	SETB E
	MOV A, DB0_DB7
	CLR E
	JB ACC.7,BUSY_LOOP4
	POP ACC
	LCALL DEL
;-----------д���ݵ�LCM------------
	CLR E
	CLR R_W
	SETB RS
	SETB E
	MOV DB0_DB7,A
	CLR E
;*****************************
	SJMP $
;*****���������*****
;****��ʱ�ӳ���ʼ****
DEL:	MOV R6,#5
L1:	MOV R7,#248
	DJNZ R7,$
	DJNZ R6,L1
	RET
;*******��ʱ�ӳ������********
	END
;*******�������*******
