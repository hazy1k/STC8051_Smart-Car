/*--------------------------------------------------------------------------
             LPCARM֮IAPӦ�þ�����FLASH����д��C++�������

IAPȫ���Խ������������ϵ�У����磺 
1.Flash֮����д��.              (�˵���򵥵�����Ҫ)
2.Flash֮�������ͱ���.          (Flash��������EEPROM,����STCMCU�Ĵ���EEPROM)
3.������ƷHex�ļ�֮Զ�̴��뻹ԭ.(���ܽ���)
��Щ������󷢲������ٸ������˽ڷ��������˰桱��

ͬʱ��ũҲ����Ұ�������~~~��ϲ��λ���귢���~~~

�˵ع��棺���ñ��ı���ע������������
��ũHotPower 2007.2.12 �������������˵� http://HotPower.21ic.org/
---------------------------------------------------------------------------*/

#include "LPC213XDEF.h"
#include "main.h"
#include <string.h>
#include <stdio.h>
/*-----------------------------------
     ����0�жϷ������
-----------------------------------*/
extern "C" void IRQ_UART0 (void) __irq
{
unsigned int i;
unsigned char ch;
  switch(U0->IIR & 0x0f) {
    case 0x06://������״̬
	  switch (U0->LSR) {
	    case 0x63:
		  break;
	  }
	  break;
/*-----------------------------------------------------------------
    ���ڽ��ղ��ִ���
��whileѭ����FIFO�п��ٵ�ȡ��ȫ�����ݣ�Ҳ�ɲ���ѭ��ÿ��ȡ��һ���ֽ�
�����ݵ��ﲻ��FIFO�Ĺ�Ч��
-----------------------------------------------------------------*/
    case 0x04://�������ݿ���
    case 0x0c://�ַ���ʱָʾ
	  while (U0->LSR & 0x01) {//��FIFO��ȡ��ȫ������
	    ch = U0->RBR;//��FIFO��ȡ��1���ַ�������
	    Uart.RxBuffer[Uart.RxCount ++] = ch;//�ݴ��뻺����
	  }
      break;
/*-----------------------------------------------------------------
    ���ڷ��ͼ���ִ���
����U0->IIR & 0x0f==1ʱΪLPCARM�����ж�,���������ģ�⼤��UART0�ж�
���ô�©����ʵ�ַǵ��˼�����ﵽʵս��Ҫ��
-----------------------------------------------------------------*/
	case 0x01://LPCARM�����ж�,���������ģ�⼤��UART0�ж�
     if (!(VIC->SoftInt & (1 << VICIntSel_UART0))) {//Ӳ��UART0�ж�
	   break;//������UART0�ж��˳�
	 }
	 //���˳ɹ����������ģ���ж�͵�����~~~�������У��Դﵽ�������ַ���Ŀ��
/*-----------------------------------------------------------------
    ���ڷ��Ͳ��ִ���
������Ҫ�ǳ�ֵ�����LPCARM��16���ֽڵ�FIFO��ʵ�֡�����FIFO��
-----------------------------------------------------------------*/
    case 0x02://THRE�ж�
  	  Uart.TxBusy = Uart.TxCount != Uart.TxdCount;//��֤FIFO����ȫ������ʱ���������ղ��ܾ�����
	  for (i = 0; (i < 16) && (Uart.TxCount != Uart.TxdCount); i ++) {//1��д��FIFO���16���ֽ�
		ch = Uart.TxBuffer[Uart.TxdCount ++];//ȡ��������1���ֽ�����
	    U0->THR = ch;//��������1���ֽ�����д��FIFO
	  }
	  VIC->SoftIntClr = (1 << VICIntSel_UART0);//�����������������־������
	  break;
  }
  VIC->VectAddr = 0x00;		/* ֪ͨVIC�жϴ������							*/
}


int main (void) {
char str[512];
unsigned int result;
unsigned int i, j;
unsigned char *ramptr, *flashptr;
/*-------------------------------------------------------------------------
    ����д�����ص��ࡣȱ�㲻֪��ַ�ʹ�С
--------------------------------------------------------------------------*/
//  Iap.SelSector(7, 7);//ѡ������7
//  Iap.EraseSector(7, 7);//��������7
//  Iap.SelSector(0, 26);//ѡ��ȫ������
//  Iap.EraseSector(0, 26);//����ȫ���������������϶���ɾ��1��������
/*-------------------------------------------------------------------------
    ��ַд�����ص㷢�Ρ��ŵ��ַ�ʹ�С�Լ�����
--------------------------------------------------------------------------*/
//  Iap.EraseFlash(0x00000000,0x0007cfff);//��������0~26  500KByte(������)

//  Iap.EraseFlash(0x00000000,0x00000000);//��������0       4KByte
//  Iap.EraseFlash(0x00007000,0x00007fff);//��������7       4KByte
//  Iap.EraseFlash(0x00008000,0x0000ffff);//��������8      32KByte
//  Iap.EraseFlash(0x00070000,0x00077fff);//��������21     32KByte
//  Iap.EraseFlash(0x00078000,0x00078fff);//��������22      4KByte
//  Iap.EraseFlash(0x0007c000,0x0007cfff);//��������26      4KByte
  Uart.puts("������ʶ��: ");
  Uart.Wait();//�ȴ��������ݷ��ͽ������ܲ���IAP
  result = Iap.ReadPartID();
  if (result != CMD_SUCCESS) {
    Uart.puts("ʧ��    ");
  }
  else {
    sprintf(str, "%d    ", Iap.result[1]);
    Uart.puts(str);
    Uart.puts("��������: ");
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
	       strcpy(str, "��Ч����");
	}
    Uart.puts(str);//��ʾ������������
  }
  Uart.puts("    Boot���뼰�汾��: ");
  Uart.Wait();//�ȴ��������ݷ��ͽ������ܲ���IAP
  result = Iap.ReadBootLoaderID();
  if (result != CMD_SUCCESS) {
    Uart.puts("ʧ��\n");
  }
  else {
    sprintf(str, "%1d.%02d\n", Iap.result[1] >> 8, Iap.result[1] & 0xff);
    Uart.puts(str);
  }
  Uart.puts("����Flash����7(0x00007000~0x00007fff 4K�ֽ�): ");
  Uart.Wait();//�ȴ��������ݷ��ͽ������ܲ���IAP
//  result = Iap.SelSector(7, 7);
//  result = Iap.EraseSector(7, 7);
  result = Iap.EraseFlash(0x00007000, 0x00007fff);
  if (result != CMD_SUCCESS) {
    Uart.puts("ʧ��\n");
  }
  else {
    Uart.puts("�ɹ�\n");
  }
  Uart.puts("���Flash����7(0x00007000~0x00007fff 4K�ֽ�): ");
  Uart.Wait();//�ȴ��������ݷ��ͽ������ܲ���IAP
//  result = Iap.BlankCheck(7, 7);
  result = Iap.CheckFlash(0x00007000, 0x00007fff);
  if (result != CMD_SUCCESS) {
    Uart.puts("ʧ��\n");
  }
  else {
    Uart.puts("�հ�\n");
  }
  Uart.puts("RAM(0x40000000~0x40000fff)д��Flash(0x00007000~0x00007fff 4K�ֽ�): ");
  Uart.Wait();//�ȴ��������ݷ��ͽ������ܲ���IAP
//  result = Iap.SelSector(7, 7);
//  result = Iap.UploadtoFlash(0x00007000, 0x40000000, 4096);
  result = Iap.WriteFlash(0x00007000, 0x40000000, 4096);
  if (result != CMD_SUCCESS) {
    Uart.puts("ʧ��\n");
  }
  else {
    Uart.puts("�ɹ�\n");
  }
  Uart.puts("���Flash����7(0x00007000~0x00007fff 4K�ֽ�): ");
  Uart.Wait();//�ȴ��������ݷ��ͽ������ܲ���IAP
//  result = Iap.BlankCheck(7, 7);
  result = Iap.CheckFlash(0x00007000, 0x00007fff);
  if (result != CMD_SUCCESS) {
    Uart.puts("ʧ��\n");
  }
  else {
    Uart.puts("�հ�\n");
  }
  Uart.puts("RAM(0x40000f00~0x40000fff)�Ƚ�Flash����7(0x00007f00~0x00007fff 256�ֽ�): ");
  Uart.Wait();//�ȴ��������ݷ��ͽ������ܲ���IAP
  result = Iap.CompareFlash(0x00007f00, 0x40000f00, 256);
  if (result != CMD_SUCCESS) {
    Uart.puts("ʧ��\n");
  }
  else {
    Uart.puts("�ɹ�\n");
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
	Uart.Wait();//�ȴ��������ݷ��ͽ���
  }
  Uart.Wait();//�ȴ��������ݷ��ͽ������ܲ���IAP
  Uart.puts("Flash����д������(0x00007000~0x000070ff 256�ֽ�): ");
  Uart.Wait();//�ȴ��������ݷ��ͽ������ܲ���IAP
//  result = Iap.SelSector(7, 7);
//  result = Iap.EraseSector(7, 7);
  result = Iap.EraseFlash(0x00007000, 0x00007fff);
  if (result == CMD_SUCCESS) {
    Iap.ReadFlash(0x00007000,(unsigned char*)&str, 256);//����ȫ0xff
    for(i = 0; i < 256; i += 2) {
      str[i] = 0x5f;
    }
    Iap.WriteFlash(0x00007000, (unsigned int)&str, 256);//1��д��0x5f
    if (Iap.result[0] != CMD_SUCCESS) {
      Uart.puts("1��д��0x5fʧ��  ");
    }
    else {
      Uart.puts("1��д��0x5f�ɹ�  ");
    }
    for(i = 0; i < 256; i += 2) {
      str[i] = 0xf5;
    }
    Iap.WriteFlash(0x00007000, (unsigned int)&str, 256);//2��д��0xf5
    if (Iap.result[0] != CMD_SUCCESS) {
      Uart.puts("2��д��0xf5ʧ��\n");
    }
    else {
      Uart.puts("2��д��0xf5�ɹ�\n");
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
	  Uart.Wait();//�ȴ��������ݷ��ͽ���
    }
  }
  while(1) {
  }
}
