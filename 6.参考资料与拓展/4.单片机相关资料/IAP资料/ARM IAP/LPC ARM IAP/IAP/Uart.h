#ifndef __IAPUART_H
#define __IAPUART_H

class UartObj;

#define Fosc            11059200                    //Crystal frequence,10MHz~25MHz，should be the same as actual status. 
						    //应当与实际一至晶振频率,10MHz~25MHz，应当与实际一至
#define Fcclk           (Fosc * 1)                  //System frequence,should be (1~32)multiples of Fosc,and should be equal or less  than 60MHz. 
						    //系统频率，必须为Fosc的整数倍(1~32)，且<=60MHZ
#define Fcco            (Fcclk * 4)                 //CCO frequence,should be 2、4、8、16 multiples of Fcclk, ranged from 156MHz to 320MHz. 
						    //CCO频率，必须为Fcclk的2、4、8、16倍，范围为156MHz~320MHz
#define Fpclk           (Fcclk / 1) * 1             //VPB clock frequence , must be 1、2、4 multiples of (Fcclk / 4).
						    //VPB时钟频率，只能为(Fcclk / 4)的1、2、4倍
#define	UART_BPS	9600				// 串口通讯波特率


class UartObj {//系统串口类
public:
  UartObj(void);
  void Init(void);
  void putchar(unsigned char); 
  void puts(const char []);
  void Wait(void);
public:
  volatile unsigned char RxBuffer[256], TxBuffer[256];
  volatile unsigned char RxCount, TxCount;
  volatile unsigned char RxdCount, TxdCount;
  volatile unsigned char TxBusy;
};

#endif  // __IAPUART_H
