;********89C51引脚定义********
	RS BIT P3.3
	R_W BIT P3.4
	E BIT P3.5
	DB0_DB7 EQU P1
;*******程序开始********
	ORG 0000H
	LJMP MAIN
;*******主程序开始*******
	ORG 0030H
MAIN:	MOV SP,#70H
;*******LCM初始化*******
	MOV A,#00111000B
;-----------判LCM忙碌-----------
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
;----------写指令到LCM---------
	CLR E
	CLR R_W
	CLR RS
	SETB E
	MOV DB0_DB7,A
	CLR E
;***************************
	MOV A,#00001110B
;-----------判LCM忙碌-----------
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
;----------写指令到LCM------------
	CLR E
	CLR R_W
	CLR RS
	SETB E
	MOV DB0_DB7,A
	CLR E
;***************************
	MOV A,#00000110B
;-----------判LCM忙碌------------
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
;-----------写指令到LCM-------------
	CLR E
	CLR R_W
	CLR RS
	SETB E
	MOV DB0_DB7,A
	CLR E
;*******LCM初始化结束*******
;****设定显示地址并写入LCM****
	MOV A,#10000000B
;-----------判LCM忙碌-----------
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
;-----------写指令到LCM------------
	CLR E
	CLR R_W
	CLR RS
	SETB E
	MOV DB0_DB7,A
	CLR E
;****将显示字符的ASCII码写入LCM****
	MOV A,#41H
;------------判LCM忙碌-------------
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
;-----------写数据到LCM------------
	CLR E
	CLR R_W
	SETB RS
	SETB E
	MOV DB0_DB7,A
	CLR E
;*****************************
	SJMP $
;*****主程序结束*****
;****延时子程序开始****
DEL:	MOV R6,#5
L1:	MOV R7,#248
	DJNZ R7,$
	DJNZ R6,L1
	RET
;*******延时子程序结束********
	END
;*******程序结束*******
