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
MAIN:	MOV SP,#60H
	LCALL INITIAL
	LCALL CLS
;*******程序启动********
START:	MOV A,#10000000B
	LCALL WRITE_COM
	MOV A,P2
	CPL A
	JNB ACC.1,DONE2
	LCALL DEL
	JNB ACC.1,DONE2
	MOV DPTR,#LINE1
	LCALL DISP
	LJMP START
DONE2:	JNB ACC.2,DONE3
	LCALL DEL
	JNB ACC.2,DONE3
	MOV DPTR,#LINE2
	LCALL DISP
	LJMP START
DONE3:	JNB ACC.3,DONE4
	LCALL DEL
	JNB ACC.3,DONE4
	MOV DPTR,#LINE3
	LCALL DISP
	LJMP START
DONE4:	JNB ACC.4,DONE0
	LCALL DEL
	JNB ACC.4,DONE0
	MOV DPTR,#LINE4
	LCALL DISP
	LJMP START
DONE0:	MOV DPTR,#LINE0
	LCALL DISP
	LJMP START
;*******显示字符串到LCM子程序********
DISP:	PUSH ACC
DISP_LOOP:CLR A
	MOVC A,@A+DPTR
	JZ END_DISP
	LCALL WRITE_DATA
	INC DPTR
	SJMP DISP_LOOP
END_DISP:POP ACC
	RET
;****** 启动LCM子程序******
INITIAL:MOV A,#00111000B
	LCALL WRITE_COM
	MOV A,#00001100B  
	LCALL WRITE_COM 
	MOV A,#00000110B 
	LCALL WRITE_COM 
	RET
;******查询忙碌标志信号子程序******
CHECK_BUSY:	PUSH ACC
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
;****** 写指令到LCM子程序******
WRITE_COM:	LCALL CHECK_BUSY
	CLR E
	CLR RS 
	CLR R_W
	SETB E
	MOV DB0_DB7,A
	CLR E
	RET
;****** 写数据到LCM子程序******
WRITE_DATA:	LCALL CHECK_BUSY
	CLR E
	SETB RS 
	CLR R_W
	SETB E
	MOV  DB0_DB7,A
	CLR E
	RET
;*******清除LCM子程序*******
CLS:	MOV A,#00000001B
	LCALL WRITE_COM
	RET
;****延时子程序****
DEL:	MOV R6,#5
L1:	MOV R7,#248
	DJNZ R7,$
	DJNZ R6,L1
	RET
;*******显示内容********
LINE0:	DB " Hello-Normal !!!",00H
LINE1:	DB " Over temp. ?????",00H
LINE2:	DB " Over speed ?????",00H
LINE3:	DB " Not water ??????",00H
LINE4:	DB " Not oil ????????",00H
;************************
	END
