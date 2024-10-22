;********89C51引脚定义********
	RS BIT P3.3
	R_W BIT P3.4
	E BIT P3.5
	DB0_DB7 EQU P1
;*******程序开始********
	ORG 0000H
	LJMP MAIN
;*******主程序*******
	ORG 0030H
MAIN:	MOV SP,#70H
	LCALL INITIAL
	MOV A,#11001010B
	LCALL WRITE_COM
	MOV A,#46H
	LCALL WRITE_DATA
	SJMP $
;****** 启动LCM子程序******
INITIAL:MOV A,#00111000B
	LCALL WRITE_COM
	MOV A,#00001110B 
	LCALL WRITE_COM 
	MOV A,#00000110B 
	LCALL WRITE_COM 
	RET
;*******查询忙碌标志信号子程序********
CHECK_BUSY: 	PUSH ACC
BUSY_LOOP:	CLR E
	SETB R_W
	CLR RS
	SETB E
	MOV A, DB0_DB7
	CLR E
	JB ACC.7,BUSY_LOOP
	POP ACC
	LCALL DEL
	RET
;****** 写指令到LCM子程序*******
WRITE_COM: 	LCALL CHECK_BUSY
	CLR E
	CLR RS 
	CLR R_W
	SETB E
	MOV  DB0_DB7,A
	CLR E
	RET
;****** 写数据到LCM子程序******
WRITE_DATA: 	LCALL CHECK_BUSY
	CLR E
	SETB RS 
	CLR R_W
	SETB E
	MOV  DB0_DB7,A
	CLR E
	RET
;****延时子程序****
DEL:	MOV R6,#5
L1:	MOV R7,#248
	DJNZ R7,$
	DJNZ R6,L1
	RET
;*********************
	END

