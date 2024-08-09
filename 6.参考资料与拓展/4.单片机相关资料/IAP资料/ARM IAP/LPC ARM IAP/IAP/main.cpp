/*--------------------------------------------------------------------------
             LPCARM之IAP应用举例及FLASH二次写入C++程序祥解

IAP全攻略将会衍生出许多系列，例如： 
1.Flash之二次写入.              (此点最简单但最重要)
2.Flash之计数器和变量.          (Flash做真正的EEPROM,而非STCMCU鼓吹的EEPROM)
3.公开产品Hex文件之远程代码还原.(加密解密)
这些将在随后发布。至少赶在情人节发个“情人版”。

同时菜农也给大家拜早年了~~~恭喜各位明年发大菜~~~

菜地公告：引用本文必须注明出处！！！
菜农HotPower 2007.2.12 于西安大雁塔菜地 http://HotPower.21ic.org/
---------------------------------------------------------------------------*/

#include "LPC213XDEF.h"
#include "main.h"
#include <string.h>
#include <stdio.h>
/*-----------------------------------
     串口0中断服务程序
-----------------------------------*/
extern "C" void IRQ_UART0 (void) __irq
{
unsigned int i;
unsigned char ch;
  switch(U0->IIR & 0x0f) {
    case 0x06://接收线状态
	  switch (U0->LSR) {
	    case 0x63:
		  break;
	  }
	  break;
/*-----------------------------------------------------------------
    串口接收部分代码
用while循环从FIFO中快速地取出全部数据，也可不用循环每次取出一个字节
的数据但达不到FIFO的功效。
-----------------------------------------------------------------*/
    case 0x04://接收数据可用
    case 0x0c://字符超时指示
	  while (U0->LSR & 0x01) {//从FIFO中取出全部数据
	    ch = U0->RBR;//从FIFO中取出1个字符的数据
	    Uart.RxBuffer[Uart.RxCount ++] = ch;//暂存入缓冲区
	  }
      break;
/*-----------------------------------------------------------------
    串口发送激活部分代码
由于U0->IIR & 0x0f==1时为LPCARM保留中断,可用于软件模拟激活UART0中断
利用此漏洞来实现非典的思想来达到实战的要求。
-----------------------------------------------------------------*/
	case 0x01://LPCARM保留中断,可用于软件模拟激活UART0中断
     if (!(VIC->SoftInt & (1 << VICIntSel_UART0))) {//硬件UART0中断
	   break;//正常的UART0中断退出
	 }
	 //至此成功利用了软件模拟中断偷入敌阵~~~继续运行，以达到发送首字符的目的
/*-----------------------------------------------------------------
    串口发送部分代码
这里主要是充分地利用LPCARM的16个字节的FIFO来实现“无限FIFO”
-----------------------------------------------------------------*/
    case 0x02://THRE中断
  	  Uart.TxBusy = Uart.TxCount != Uart.TxdCount;//保证FIFO发送全部结束时，缓冲区空不拒绝发送
	  for (i = 0; (i < 16) && (Uart.TxCount != Uart.TxdCount); i ++) {//1次写入FIFO最多16个字节
		ch = Uart.TxBuffer[Uart.TxdCount ++];//取出缓冲区1个字节数据
	    U0->THR = ch;//将缓冲区1个字节数据写入FIFO
	  }
	  VIC->SoftIntClr = (1 << VICIntSel_UART0);//这里必须清除此软件标志！！！
	  break;
  }
  VIC->VectAddr = 0x00;		/* 通知VIC中断处理结束							*/
}


int main (void) {
char str[512];
unsigned int result;
unsigned int i, j;
unsigned char *ramptr, *flashptr;
/*-------------------------------------------------------------------------
    扇区写法，特点简洁。缺点不知地址和大小
--------------------------------------------------------------------------*/
//  Iap.SelSector(7, 7);//选择扇区7
//  Iap.EraseSector(7, 7);//擦除扇区7
//  Iap.SelSector(0, 26);//选择全部扇区
//  Iap.EraseSector(0, 26);//擦除全部扇区，哈哈，肯定刚删除1个就死机
/*-------------------------------------------------------------------------
    地址写法，特点发晕。优点地址和大小自己掌握
--------------------------------------------------------------------------*/
//  Iap.EraseFlash(0x00000000,0x0007cfff);//擦除扇区0~26  500KByte(倒塌了)

//  Iap.EraseFlash(0x00000000,0x00000000);//擦除扇区0       4KByte
//  Iap.EraseFlash(0x00007000,0x00007fff);//擦除扇区7       4KByte
//  Iap.EraseFlash(0x00008000,0x0000ffff);//擦除扇区8      32KByte
//  Iap.EraseFlash(0x00070000,0x00077fff);//擦除扇区21     32KByte
//  Iap.EraseFlash(0x00078000,0x00078fff);//擦除扇区22      4KByte
//  Iap.EraseFlash(0x0007c000,0x0007cfff);//擦除扇区26      4KByte
  Uart.puts("器件标识号: ");
  Uart.Wait();//等待串口数据发送结束才能操作IAP
  result = Iap.ReadPartID();
  if (result != CMD_SUCCESS) {
    Uart.puts("失败    ");
  }
  else {
    sprintf(str, "%d    ", Iap.result[1]);
    Uart.puts(str);
    Uart.puts("器件名称: ");
    switch(Iap.result[1]) {
	  case Device_LPC2131:
	       strcpy(str, "LPC2131");
		   break;
	  case Device_LPC2132:
	       strcpy(str, "LPC2132");
		   break;
	  case Device_LPC2134:
	       strcpy(str, "LPC2134");
		   break;
	  case Device_LPC2136:
	       strcpy(str, "LPC2136");
		   break;
	  case Device_LPC2138:
	       strcpy(str, "LPC2138");
		   break;
	  default:
	       strcpy(str, "无效器件");
	}
    Uart.puts(str);//显示器件具体名称
  }
  Uart.puts("    Boot代码及版本号: ");
  Uart.Wait();//等待串口数据发送结束才能操作IAP
  result = Iap.ReadBootLoaderID();
  if (result != CMD_SUCCESS) {
    Uart.puts("失败\n");
  }
  else {
    sprintf(str, "%1d.%02d\n", Iap.result[1] >> 8, Iap.result[1] & 0xff);
    Uart.puts(str);
  }
  Uart.puts("擦除Flash扇区7(0x00007000~0x00007fff 4K字节): ");
  Uart.Wait();//等待串口数据发送结束才能操作IAP
//  result = Iap.SelSector(7, 7);
//  result = Iap.EraseSector(7, 7);
  result = Iap.EraseFlash(0x00007000, 0x00007fff);
  if (result != CMD_SUCCESS) {
    Uart.puts("失败\n");
  }
  else {
    Uart.puts("成功\n");
  }
  Uart.puts("查空Flash扇区7(0x00007000~0x00007fff 4K字节): ");
  Uart.Wait();//等待串口数据发送结束才能操作IAP
//  result = Iap.BlankCheck(7, 7);
  result = Iap.CheckFlash(0x00007000, 0x00007fff);
  if (result != CMD_SUCCESS) {
    Uart.puts("失败\n");
  }
  else {
    Uart.puts("空白\n");
  }
  Uart.puts("RAM(0x40000000~0x40000fff)写入Flash(0x00007000~0x00007fff 4K字节): ");
  Uart.Wait();//等待串口数据发送结束才能操作IAP
//  result = Iap.SelSector(7, 7);
//  result = Iap.UploadtoFlash(0x00007000, 0x40000000, 4096);
  result = Iap.WriteFlash(0x00007000, 0x40000000, 4096);
  if (result != CMD_SUCCESS) {
    Uart.puts("失败\n");
  }
  else {
    Uart.puts("成功\n");
  }
  Uart.puts("查空Flash扇区7(0x00007000~0x00007fff 4K字节): ");
  Uart.Wait();//等待串口数据发送结束才能操作IAP
//  result = Iap.BlankCheck(7, 7);
  result = Iap.CheckFlash(0x00007000, 0x00007fff);
  if (result != CMD_SUCCESS) {
    Uart.puts("失败\n");
  }
  else {
    Uart.puts("空白\n");
  }
  Uart.puts("RAM(0x40000f00~0x40000fff)比较Flash扇区7(0x00007f00~0x00007fff 256字节): ");
  Uart.Wait();//等待串口数据发送结束才能操作IAP
  result = Iap.CompareFlash(0x00007f00, 0x40000f00, 256);
  if (result != CMD_SUCCESS) {
    Uart.puts("失败\n");
  }
  else {
    Uart.puts("成功\n");
  }
  flashptr = (unsigned char *)0x00007f00;//Flash
  ramptr = (unsigned char *)0x40000f00;//Flash
  for(i = 0;i < 16; i ++) {
    sprintf(str, "0x%08X: ", flashptr);//Flash
    Uart.puts(str);
    for(j = 0;j < 16; j ++) {
      sprintf(str, "%02X ", *flashptr++);//Flash
      Uart.puts(str);
	}
    sprintf(str, "0x%08X: ", ramptr);//Flash
    Uart.puts(str);
    for(j = 0;j < 16; j ++) {
      sprintf(str, "%02X ", *ramptr++);//Flash
      Uart.puts(str);
	}
	Uart.puts("\n");
	Uart.Wait();//等待串口数据发送结束
  }
  Uart.Wait();//等待串口数据发送结束才能操作IAP
  Uart.puts("Flash二次写入扇区(0x00007000~0x000070ff 256字节): ");
  Uart.Wait();//等待串口数据发送结束才能操作IAP
//  result = Iap.SelSector(7, 7);
//  result = Iap.EraseSector(7, 7);
  result = Iap.EraseFlash(0x00007000, 0x00007fff);
  if (result == CMD_SUCCESS) {
    Iap.ReadFlash(0x00007000,(unsigned char*)&str, 256);//读入全0xff
    for(i = 0; i < 256; i += 2) {
      str[i] = 0x5f;
    }
    Iap.WriteFlash(0x00007000, (unsigned int)&str, 256);//1次写入0x5f
    if (Iap.result[0] != CMD_SUCCESS) {
      Uart.puts("1次写入0x5f失败  ");
    }
    else {
      Uart.puts("1次写入0x5f成功  ");
    }
    for(i = 0; i < 256; i += 2) {
      str[i] = 0xf5;
    }
    Iap.WriteFlash(0x00007000, (unsigned int)&str, 256);//2次写入0xf5
    if (Iap.result[0] != CMD_SUCCESS) {
      Uart.puts("2次写入0xf5失败\n");
    }
    else {
      Uart.puts("2次写入0xf5成功\n");
    }
    flashptr = (unsigned char *)0x00007000;
    ramptr = (unsigned char *)0x00007100;
    for(i = 0;i < 16; i ++) {
      sprintf(str, "0x%08X: ", flashptr);
      Uart.puts(str);
      for(j = 0;j < 16; j ++) {
        sprintf(str, "%02X ", *flashptr++);
        Uart.puts(str);
	  }
      sprintf(str, "0x%08X: ", ramptr);
      Uart.puts(str);
      for(j = 0;j < 16; j ++) {
        sprintf(str, "%02X ", *ramptr++);
        Uart.puts(str);
	  }
	  Uart.puts("\n");
	  Uart.Wait();//等待串口数据发送结束
    }
  }
  while(1) {
  }
}
