#ifndef __IAPUART_H
#define __IAPUART_H

class UartObj;

#define Fosc            11059200                    //Crystal frequence,10MHz~25MHz��should be the same as actual status. 
						    //Ӧ����ʵ��һ������Ƶ��,10MHz~25MHz��Ӧ����ʵ��һ��
#define Fcclk           (Fosc * 1)                  //System frequence,should be (1~32)multiples of Fosc,and should be equal or less  than 60MHz. 
						    //ϵͳƵ�ʣ�����ΪFosc��������(1~32)����<=60MHZ
#define Fcco            (Fcclk * 4)                 //CCO frequence,should be 2��4��8��16 multiples of Fcclk, ranged from 156MHz to 320MHz. 
						    //CCOƵ�ʣ�����ΪFcclk��2��4��8��16������ΧΪ156MHz~320MHz
#define Fpclk           (Fcclk / 1) * 1             //VPB clock frequence , must be 1��2��4 multiples of (Fcclk / 4).
						    //VPBʱ��Ƶ�ʣ�ֻ��Ϊ(Fcclk / 4)��1��2��4��
#define	UART_BPS	9600				// ����ͨѶ������


class UartObj {//ϵͳ������
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
