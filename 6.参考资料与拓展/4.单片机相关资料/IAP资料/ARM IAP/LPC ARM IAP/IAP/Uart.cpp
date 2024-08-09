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
  PINSEL->PIN_SEL0 |= (P0_0_TXD0 << P0_0_PINSEL) | (P0_1_RXD0 << P0_1_PINSEL); //设置I/O连接到UART0

  U0->LCR = 0x83;// DLAB=1,允许设置波特率
  Fdiv  = (Fpclk / 16) / UART_BPS;// 设置波特率38400
  U0->DLM = Fdiv / 256;
  U0->DLL = Fdiv % 256;
  U0->LCR = 0x03;
  U0->FCR = 0xc7;/* 初始化FIFO 接收14个字节就中断*/
  U0->IER = 0x07;/* 允许接收发送中断 */
  VIC->VectAddrs[0] = (unsigned int)IRQ_UART0;
  VIC->VectCntls[0]   = VICIntSel_Enable//使能IRQ中断
                      | VICIntSel_UART0;//获取UART0的IRQ级别
  VIC->IntEnable |= (1 << VICIntSel_UART0);
}

void UartObj::putchar(unsigned char ch)
{
  TxBuffer[TxCount] = ch;
  TxCount ++;
  if (ch == '\n') {
/*-----------------------------------------------------------------
    串口激活部分代码
当Uart.TxBusy=1时表示串口忙正在发送数据，这是就不需用软件激活。
因为串口FIFO中最后一个字节的数据发送结束时还要引发一次中断。
否则在Uart.TxBusy=0时，由于串口闲，不可能进入发送中断。故需两种
办法来激活发送中断：
1.取出一个字节发送出去，在发送中断里再发送后续字节。
2.用VIC->SoftInt = (1 << VICIntSel_UART0);//模拟51的TI=1来引发发送中断
-----------------------------------------------------------------*/
	if (!TxBusy) {//发送器不忙可以立即发送
	  VIC->SoftInt = (1 << VICIntSel_UART0);//模拟51的TI=1来引发发送中断
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
  while(TxBusy);//等待串口数据发送结束
}
