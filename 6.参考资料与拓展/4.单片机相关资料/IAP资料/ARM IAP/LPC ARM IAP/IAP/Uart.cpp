#include "LPC213XDEF.h"
#include "uart.h"

extern "C" void IRQ_UART0 (void) __irq;

UartObj::UartObj(void)
{
  Init();
}

void UartObj::Init(void)
{
unsigned int Fdiv;
  TxCount = 0;
  RxCount = 0;
  TxdCount = 0;
  RxdCount = 0;
  TxBusy = 0;
  PINSEL->PIN_SEL0 |= (P0_0_TXD0 << P0_0_PINSEL) | (P0_1_RXD0 << P0_1_PINSEL); //����I/O���ӵ�UART0

  U0->LCR = 0x83;// DLAB=1,�������ò�����
  Fdiv  = (Fpclk / 16) / UART_BPS;// ���ò�����38400
  U0->DLM = Fdiv / 256;
  U0->DLL = Fdiv % 256;
  U0->LCR = 0x03;
  U0->FCR = 0xc7;/* ��ʼ��FIFO ����14���ֽھ��ж�*/
  U0->IER = 0x07;/* ������շ����ж� */
  VIC->VectAddrs[0] = (unsigned int)IRQ_UART0;
  VIC->VectCntls[0]   = VICIntSel_Enable//ʹ��IRQ�ж�
                      | VICIntSel_UART0;//��ȡUART0��IRQ����
  VIC->IntEnable |= (1 << VICIntSel_UART0);
}

void UartObj::putchar(unsigned char ch)
{
  TxBuffer[TxCount] = ch;
  TxCount ++;
  if (ch == '\n') {
/*-----------------------------------------------------------------
    ���ڼ���ִ���
��Uart.TxBusy=1ʱ��ʾ����æ���ڷ������ݣ����ǾͲ�����������
��Ϊ����FIFO�����һ���ֽڵ����ݷ��ͽ���ʱ��Ҫ����һ���жϡ�
������Uart.TxBusy=0ʱ�����ڴ����У������ܽ��뷢���жϡ���������
�취��������жϣ�
1.ȡ��һ���ֽڷ��ͳ�ȥ���ڷ����ж����ٷ��ͺ����ֽڡ�
2.��VIC->SoftInt = (1 << VICIntSel_UART0);//ģ��51��TI=1�����������ж�
-----------------------------------------------------------------*/
	if (!TxBusy) {//��������æ������������
	  VIC->SoftInt = (1 << VICIntSel_UART0);//ģ��51��TI=1�����������ж�
	}
  }
}

void UartObj::puts(const char str[])
{
  while (*str) {
    putchar(*str++);
  }
}

void UartObj::Wait(void)
{
  while(TxBusy);//�ȴ��������ݷ��ͽ���
}
