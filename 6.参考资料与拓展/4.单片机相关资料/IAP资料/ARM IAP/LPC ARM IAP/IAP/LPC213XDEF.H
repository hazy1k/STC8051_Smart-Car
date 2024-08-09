/*--------------------------------------------------------------------------
文   件   名 :  LPC213XDEF.H
创   建   人 :  ARM爬鸟  HotPower@126.com
创 建 日  期 :  2005.7.23   0:38
最近修改日期 :  2007.2.10  3:30 
创 建  地 点 ： 西安大雁塔村队部 http://hotpower.21ic.org
版   本   号 ： V5.88 (IAP全攻略版)
说        明 ： 已经过硬件调试
                由于在不断更新中，故新旧版本以修改日期为准
备        注 ： 由此文件出现的问题，ARM爬鸟不负任何责任
                经过近一年的应用本头文件相当可靠。
修 改  原 因 ： 全面替代LPC213x.h
菜 地  公 告：	转帖请注明出处：http://hotpower.21ic.org
                菜农的所有LPCARM例程及实战书籍和开源压缩包
				都将采用本头文件。
应 用  简 介：
SystemObj::SystemObj(void)
{
volatile unsigned int start;
  Disable_IRQ();//关中断
  PINSEL->PIN_SEL0 = 0x00000000;  // 设置管脚连接GPIO
  PINSEL->PIN_SEL1 = 0x00000000;  // 设置管脚连接GPIO
  PINSEL->PIN_SEL2 = 0x00000000;  // 设置管脚连接GPIO
  PINSEL->PIN_SEL0 |= (P0_15_EINT2 << P0_15_PINSEL);// P0.15连接到EINT2
  P0->IODIR  = 0x00000000;  // 设置P0口为输入
  P1->IODIR  = 0x00000000;  // 设置P1口为输入
  VIC->IntEnable = 0;
  VIC->SoftIntClr = 0xffffffff;//清除所有软中断标志
  VIC->IntSelect   = 0;//全部中断为IRQ中断或默认中断
  for(int i = 0; i <= 15; i ++) {
    VIC->VectAddrs[i] = i;//刷新向量地址寄存器VICVectAddr0~VICVectAddr15
  }
  for (start = 1; start < 10000; start ++);
  SystemInit();
  Enable_IRQ();//开中断
}
-------------------------------------------------------------------------------*/


#ifndef __LPC213xDEF_H
#define __LPC213xDEF_H

typedef volatile unsigned long LPC_REG;// Hardware register definition

#define __noinit__ __attribute__((zero_init))//变量不初始化为0


typedef unsigned char  uint8; //无符号8位整型变量
typedef signed   char  int8;  //有符号8位整型变量
typedef unsigned short uint16;//无符号16位整型变量
typedef signed   short int16; //有符号16位整型变量
typedef unsigned int   uint32;//无符号32位整型变量
typedef signed   int   int32; //有符号32位整型变量
typedef float          fp32;  //单精度浮点数（32位长度
typedef double         fp64;  //双精度浮点数（64位长度）

#define __0                  (LPC_REG)0 
#define __1                  (LPC_REG)1 
#define __2                  (LPC_REG)2 
#define __3                  (LPC_REG)3 
#define __4                  (LPC_REG)4 
#define __5                  (LPC_REG)5 
#define __6                  (LPC_REG)6 
#define __7                  (LPC_REG)7 
#define __8                  (LPC_REG)8 
#define __9                  (LPC_REG)9 
#define __10                 (LPC_REG)10
#define __11                 (LPC_REG)11
#define __12                 (LPC_REG)12
#define __13                 (LPC_REG)13
#define __14                 (LPC_REG)14
#define __15                 (LPC_REG)15
#define __16                 (LPC_REG)16
#define __17                 (LPC_REG)17
#define __18                 (LPC_REG)18
#define __19                 (LPC_REG)19
#define __20                 (LPC_REG)20
#define __21                 (LPC_REG)21
#define __22                 (LPC_REG)22
#define __23                 (LPC_REG)23
#define __24                 (LPC_REG)24
#define __25                 (LPC_REG)25
#define __26                 (LPC_REG)26
#define __27                 (LPC_REG)27
#define __28                 (LPC_REG)28
#define __29                 (LPC_REG)29
#define __30                 (LPC_REG)30
#define __31                 (LPC_REG)31

#define VICIntSel_Watchdog   0//看门狗中断（WDINT）
#define VICIntSel_SoftInt1   1//保留给软件中断
#define VICIntSel_DbgCommRx  2//ARM内核中断
#define VICIntSel_DbgCommTx  3//ARM内核中断
#define VICIntSel_Time0      4//定时器0中断
#define VICIntSel_Time1      5//定时器1中断
#define VICIntSel_UART0      6//UART0中断
#define VICIntSel_UART1      7//UART1中断
#define VICIntSel_PWM0       8//PWM0中断
#define VICIntSel_I2C0       9//I2C0中断
#define VICIntSel_SPI0      10//SPI0中断
#define VICIntSel_SSP       11//SSP中断
#define VICIntSel_SPI1      11//SPI1中断
#define VICIntSel_PLL       12//PLL中断
#define VICIntSel_RTC       13//RTC中断
#define VICIntSel_EINT0     14//系统控制外部中断0
#define VICIntSel_EINT1     15//系统控制外部中断1
#define VICIntSel_EINT2     16//系统控制外部中断2
#define VICIntSel_EINT3     17//系统控制外部中断3
#define VICIntSel_ADC0      18//A/D转换器0中断
#define VICIntSel_I2C1      19//I2C1中断
#define VICIntSel_BOD       20//掉电检测中断
#define VICIntSel_ADC1      21//A/D转换器1中断
#define VICIntSel_SoftInt22 22//保留给软件中断
#define VICIntSel_SoftInt23 23//保留给软件中断
#define VICIntSel_SoftInt24 24//保留给软件中断
#define VICIntSel_SoftInt25 25//保留给软件中断
#define VICIntSel_SoftInt26 26//保留给软件中断
#define VICIntSel_SoftInt27 27//保留给软件中断
#define VICIntSel_SoftInt28 28//保留给软件中断
#define VICIntSel_SoftInt29 29//保留给软件中断
#define VICIntSel_SoftInt30 30//保留给软件中断
#define VICIntSel_SoftInt31 31//保留给软件中断
#define VICIntSel_Enable    32//使能向量中断

/*--------------------------------------------------------------------
应用示例
  VIC->VectCntls[0]   = VICIntSel_Enable//使能IRQ中断
                      | VICIntSel_EINT0;//获取EINT0的IRQ级别
  VIC->VectAddrs[0]   = (long) IRQ_Eint0;//取INT0中断服务地址
  VIC->IntEnable      = (1 << VICIntSel_EINT0); //使能EINT0中断
----------------------------------------------------------------------*/

/*---------------------------------------------------------------------
                 P0口链接配置位定义
----------------------------------------------------------------------*/

#define P0_0   0//P0.0
  #define TXD0    P0_0//UART0的发送器输出
  #define PWM1    P0_0//脉宽调制器输出1
#define P0_1   1//P0.1
  #define RXD0    P0_1//UART0的接收器输入
  #define PWM3    P0_1//脉宽调制器输出3
#define P0_2   2//P0.2
  #define SCL0    P0_2//I2C0时钟输入/输出。开漏输出(符合I2C规范)
#define P0_3   3//P0.3
  #define SDA0    P0_3//I2C0数据输入/输出。开漏输出(符合I2C规范)
#define P0_4   4//P0.4
  #define SCK0    P0_4//SPI0的串行时钟。SPI时钟从主机输出，从机输入
  #define AD0_6   P0_4//A/D转换器0输入6。该模拟输入总是连接到相应的管脚
#define P0_5   5//P0.5
  #define MISO0   P0_5//SPI0主机输入从机输出端。从机到主机的数据传输
  #define AD0_7   P0_5//A/D转换器0输入7。该模拟输入总是连接到相应的管脚
#define P0_6   6//P0.6
  #define MOSI0   P0_6//SPI0主机输出从机输入端。主机到从机的数据传输
  #define AD1_0   P0_6//A/D转换器1输入0。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_7   7//P0.7
  #define SSEL0   P0_7//SPI0从机选择。选择SPI接口用作从机
  #define PWM2    P0_7//脉宽调制器输出2
#define P0_8   8//P0.8
  #define TXD1    P0_8//UART1的发送器输出
  #define PWM4    P0_8//脉宽调制器输出4
  #define AD1_1   P0_8//A/D转换器1输入1。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_9   9//P0.9
  #define RXD1    P0_9//UART1的接收器输入
  #define PWM6    P0_9//脉宽调制器输出6
#define P0_10 10//P0.10
  #define RTS1    P0_10//UART1请求发送出端（仅用于LP138）
  #define CAP1_0  P0_10//定时器1的捕获输入通道0
  #define AD1_2   P0_10//A/D转换器1输入2。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_11 11//P0.11
  #define CTS1    P0_11//UART1清除发送入端（仅用于LP138）
  #define CAP1_1  P0_11//定时器1的捕获输入通道1
  #define SCL1    P0_11//I2C1时钟输入/输。开漏输出(符合I2C规范）
#define P0_12 12//P0.12
  #define DSR1    P0_12//UART1数据设置就绪端（仅用于 LPC2138）
  #define MAT1_0  P0_12//定时器1的匹配输出通道0
  #define AD1_3   P0_12//A/D转换器1输入3。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_13 13//P0.13
  #define DTR1    P0_13//UART1数据终端就绪
  #define MAT1_1  P0_13//定时器1的匹配输出通道1
  #define AD1_4   P0_13//A/D转换器1输入4。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_14 14//P0.14
  #define DCD1    P0_14//UART1数据载波检测输入（仅用于 LPC2138）
  #define SDA1    P0_14//I2C1数据输入/输出。开漏输出(符合I2C规范）
#define P0_15 15//P0.15
  #define RI1     P0_15//UART1铃响指示输入（仅用于 LPC2138）
  #define AD1_5   P0_15//A/D转换器1输入5。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_16 16//P0.16

#define P0_17 17//P0.17
  #define SCK1    P0_17//SPI1的串行时钟。SPI时钟从主机输出，从机输入
#define P0_18 18//P0.18
  #define MISO1   P0_18//SPI1主机输入从机输出端。从机到主机的数据传输
#define P0_19 19//P0.19
  #define MOSI1   P0_19//SPI1主机输出从机输入端。主机到从机的数据传输
#define P0_20 20//P0.20
  #define SSEL1   P0_20//SPI1从机选择。选择SPI接口用作从机
#define P0_21 21//P0.21
  #define PWM5    P0_21//脉宽调制器输出5
  #define AD1_6   P0_21//A/D转换器1输入6。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_22 22//P0.22
  #define AD1_7   P0_22//A/D转换器1输入7。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_23 23//P0.23
#define P0_24 24//P0.24
#define P0_25 25//P0.25
  #define AD0_4   P0_25//A/D转换器0输入4。该模拟输入总是连接到相应的管脚.D/A 转换器输出（仅用于 LPC2138）
#define P0_26 26//P0.26
  #define AD0_5   P0_26//A/D转换器0输入5。该模拟输入总是连接到相应的管脚
#define P0_27 27//P0.27
  #define AD0_0   P0_27//A/D转换器0输入0。该模拟输入总是连接到相应的管脚
#define P0_28 28//P0.28
  #define AD0_1   P0_28//A/D转换器0输入1。该模拟输入总是连接到相应的管脚
#define P0_29 29//P0.29
  #define AD0_2   P0_29//A/D转换器0输入2。该模拟输入总是连接到相应的管脚
  #define CAP0_3  P0_29//定时器0的捕获输入通道3
  #define MAT0_3  P0_29//定时器0的匹配输出通道3
#define P0_30 30//P0.30
  #define AD0_3   P0_30//A/D转换器0输入3。该模拟输入总是连接到相应的管脚
#define P0_31 31//P0.31

/*------------------------------------------
        P1口GPIO位寻址位定义
-------------------------------------------*/
#define P1_0   0//P1.0
#define P1_1   1//P1.1
#define P1_2   2//P1.2
#define P1_3   3//P1.3
#define P1_4   4//P1.4
#define P1_5   5//P1.5
#define P1_6   6//P1.6
#define P1_7   7//P1.7
#define P1_8   8//P1.8
#define P1_9   9//P1.9
#define P1_10 10//P1.10
#define P1_11 11//P1.11
#define P1_12 12//P1.12
#define P1_13 13//P1.13
#define P1_14 14//P1.14
#define P1_15 15//P1.15
#define P1_16 16//P1.16
#define P1_17 17//P1.17
#define P1_18 18//P1.18
#define P1_19 19//P1.19
#define P1_20 20//P1.20
#define P1_21 21//P1.21
#define P1_22 22//P1.22
#define P1_23 23//P1.23
#define P1_24 24//P1.24
#define P1_25 25//P1.25
#define P1_26 26//P1.26
#define P1_27 27//P1.27
#define P1_28 28//P1.28
#define P1_29 29//P1.29
#define P1_30 30//P1.30
#define P1_31 __31//P1.31

 

/*---------------------------------------
        RTC中断位置寄存器ILR位定义
----------------------------------------*/
#define RTCCIF   0//为1时，计数器增量中断模块产生中断。向该位写入1清除计数器增量中断。
#define RTCALF   1//为1时，报警寄存器产生中断。向该位写入1清除报警中断。


/*---------------------------------------
        RTC时钟控制寄存器CCR位定义
----------------------------------------*/
#define CLKEN    0//时钟使能当该位为1 时，时间计数器使能。
#define CTCRST   1//CTC 复位为1 时，时钟节拍计数器复位。
#define CLKSRC   4//如果该位为1，CTC 计数连接在RTCX1 和RTCX2 两端的32kHz振荡器信号。

/*---------------------------------------
        RTC计数器增量中断寄存器CIIR位定义
----------------------------------------*/
#define IMSEC    0//为1时，秒值的增加产生一次中断。
#define IMMIN    1//为1时，分值的增加产生一次中断。
#define IMHOUR   2//为1时，小时值的增加产生一次中断。
#define IMDOM    3//为1时，日期（月）值的增加产生一次中断。
#define IMDOW    4//为1时，星期值的增加产生一次中断。
#define IMDOY    5//为1时，日期（年）值的增加产生一次中断。
#define IMMON    6//为1时，月值的增加产生一次中断。
#define IMYEAR   7//为1时，年值的增加产生一次中断。

/*---------------------------------------
        RTC报警屏蔽寄存器位AMR位定义
----------------------------------------*/
#define AMRSEC   0//为1 时，秒值不与报警寄存器比较。
#define AMRMIN   1//为1 时，分值不与报警寄存器比较。
#define AMRHOUR  2//为1 时，小时值不与报警寄存器比较。
#define AMRDOM   3//为1 时，日期（月）值不与报警寄存器比较。
#define AMRDOW   4//为1 时，星期值不与报警寄存器比较。
#define AMRDOY   5//为1 时，日期（年）值不与报警寄存器比较。
#define AMRMON   6//为1 时，月值不与报警寄存器比较。
#define AMRYEAR  7//为1 时，年值不与报警寄存器比较。

/*---------------------------------------
        TX中断寄存器TXIR位定义
----------------------------------------*/
#define MR0      0//匹配通道0中断标志
#define MR1      1//匹配通道1中断标志
#define MR2      2//匹配通道2中断标志
#define MR3      3//匹配通道3中断标志
#define CR0      4//捕获通道0事件中断标志
#define CR1      5//捕获通道0事件中断标志
#define CR2      6//捕获通道0事件中断标志
#define CR3      7//捕获通道0事件中断标志



/*---------------------------------------
        UARTX标识中断寄存器UXIIR
----------------------------------------*/
#define IIR0     0//中断挂起 0：至少有1个中断被挂起(挂起的中断可通过UXIER3:1确定)
#define IIR1     1//中断标识1
#define IIR2     2//中断标识2
#define IIR3     3//中断标识3


/*---------------------------------------
        UARTX线状态寄存器UXLSR
----------------------------------------*/
#define RDR      0//接收数据就绪
#define OE		 1//溢出错误
#define PE		 2//奇偶错误
#define FE		 3//帧错误
#define BI		 4//间隔中断
#define THRE     5//发送保持寄存器空
#define TEMT     6//发送器空
#define RXFE     7//Rx FIFO错误

/*---------------------------------------
        I2C控制置位寄存器I2CONSET位定义
----------------------------------------*/
#define AA       2//应答标志。
#define SI       3//I2C中断标志。
#define STO      4//停止标志。
#define STA      5//起始标志。
#define I2EN     6//I2C接口使能。

/*---------------------------------------
        I2C控制清零寄存器I2CONCLR位定义
----------------------------------------*/
#define AAC      2//应答标志。
#define SIC      3//I2C中断标志。
#define STAC     5//起始标志。
#define I2ENC    6//I2C接口使能。


/*---------------------------------------
        I2C运行状态代码定义
----------------------------------------*/
#define I2C_START	    	      0x08 //已发送起始条件
#define I2C_REP_START		      0x10 //已发送重复起始条件
/* Master Transmitter */			   //主发送器模式
#define I2C_MT_SLA_ACK		      0x18 //已发送SLA+W,且已接收ACK
#define I2C_MT_SLA_NACK		      0x20 //已发送SLA+W,且未接收ACK
#define I2C_MT_DATA_ACK		      0x28 //已发送I2DAT 中的数据字节，且已接收ACK
#define I2C_MT_DATA_NACK	      0x30 //已发送I2DAT 中的数据字节，且未接收ACK
#define I2C_MT_ARB_LOST		      0x38
/* Master Receiver */				   //主接收器模式
#define I2C_MR_ARB_LOST		      0x38
#define I2C_MR_SLA_ACK		      0x40 //已发送SLA+R,且已接收ACK
#define I2C_MR_SLA_NACK		      0x48 //已发送SLA+R,且未接收ACK
#define I2C_MR_DATA_ACK		      0x50
#define I2C_MR_DATA_NACK	      0x58
/* Slave Transmitter */
#define I2C_ST_SLA_ACK	     	  0xA8
#define I2C_ST_ARB_LOST_SLA_ACK	  0xB0
#define I2C_ST_DATA_ACK		      0xB8
#define I2C_ST_DATA_NACK	      0xC0
#define I2C_ST_LAST_DATA	      0xC8
/* Slave Receiver */
#define I2C_SR_SLA_ACK		      0x60
#define I2C_SR_ARB_LOST_SLA_ACK	  0x68
#define I2C_SR_GCALL_ACK	  	  0x70
#define I2C_SR_ARB_LOST_GCALL_ACK 0x78
#define I2C_SR_DATA_ACK		      0x80
#define I2C_SR_DATA_NACK		  0x88
#define I2C_SR_GCALL_DATA_ACK	  0x90
#define I2C_SR_GCALL_DATA_NACK	  0x98
#define I2C_SR_STOP		          0xA0
/* Misc */
#define I2C_NO_INFO		          0xF8
#define I2C_BUS_ERROR		      0x00


/*-------------------------
        PWMMCR位定义
--------------------------*/
#define PWMMCRI0 0
#define PWMMCRR0 1
#define PWMMCRS0 2

#define PWMMCRI1 3
#define PWMMCRR1 4
#define PWMMCRS1 5

#define PWMMCRI2 6
#define PWMMCRR2 7
#define PWMMCRS2 8

#define PWMMCRI3 9
#define PWMMCRR3 10
#define PWMMCRS3 11

#define PWMMCRI4 12
#define PWMMCRR4 13
#define PWMMCRS4 14

#define PWMMCRI5 15
#define PWMMCRR5 16
#define PWMMCRS5 17

#define PWMMCRI6 18
#define PWMMCRR6 19
#define PWMMCRS6 20

 

/*-------------------------
        PWMPCR位定义
--------------------------*/
#define PWMSEL1 1
#define PWMSEL2 2
#define PWMSEL3 3
#define PWMSEL4 4
#define PWMSEL5 5
#define PWMSEL6 6

#define PWMENA1 9
#define PWMENA2 10
#define PWMENA3 11
#define PWMENA4 12
#define PWMENA5 13
#define PWMENA6 14

/*--------------------------
        PWMLER位定义
---------------------------*/
#define PWMLER0 0
#define PWMLER1 1
#define PWMLER2 2
#define PWMLER3 3
#define PWMLER4 4
#define PWMLER5 5
#define PWMLER6 6

/*--------------------------
        ADCR位定义
---------------------------*/
#define BURST   16
#define PDN     21

#define START   24//26:24=000

#define EDGE    27

/*------------------------------------------------
        A/D 数据寄存器ADDR位定义
-------------------------------------------------*/
#define OVERUN      30
#define DONE        31//A/D转换结束时该位置位。该位在ADDR被读出和ADCR被写入时清零。
/*-----------------------------------------
        复位源识别寄存器RSID位定义
------------------------------------------*/
#define POR          0//RSID.0//POR信号有效时该位置位，并清除RSID寄存器的其它位
#define EXTR         1//RSID.1//RESET信号有效时该位置位
#define WDTR         2//RSID.2//当看门狗定时器溢出和看门狗方式寄存器的WDTRESET位为1时，该位置位。
                              //该位可被其它任何一个复位源清除。
#define BODR         3//RSID.3//当3.3V的电源降到低于2.6V时该位置位

/*-----------------------------------------
        SSP状态寄存器SSPSR位定义
------------------------------------------*/
#define TFE          0//发送FIFO 空。发送FIFO 为空时该位为1，反之为0。
#define TNF          1//发送FIFO 未满。Tx FIFO 满时该位为0，反之为1。
#define RNE          2//接收FIFO 不为空。接收FIFO 为空时该位为0，反之为1。
#define RFF          3//接收FIFO 满。接收FIFO 满时该位为1，反之为0。
#define BSY          4//忙。SSP 控制器空闲、

/*-----------------------------------------
        S0SPCR位定义
------------------------------------------*/
#define CPHA         3//时钟相位控制
#define CPOL         4//时钟极性控制
#define MSTR         5//主模式选择。为1时，SPI处于主模式。为0时，SPI处于从模式。
#define LSBF         6//传输的每个字节的移动方向.为0 时，SPI数据传输MSB(位7)在先
#define SPIE         7//中断使能。为1时，每次SPIF或MODF置位时都会产生硬件中断
/*-----------------------------------------
        SPI 状态寄存器S0SPSR位定义
------------------------------------------*/
#define ABRT        3//从机中止。该位为1 时表示发生了从机中止。当读取该寄存器时，该位清零
#define MODF        4//模式错误。为1 时表示发生了模式错误。
#define ROVR        5//读溢出。为1 时表示发生了读溢出。当读取该寄存器时，该位清零。
#define WCOL        6//写冲突。为1 时表示发生了写冲突
#define SPIF        7//SPI 传输完成标志。为1 时表示一次SPI 数据传输完成。


/*-----------------------------------------
        功率控制寄存器PCON位定义
------------------------------------------*/
#define IDL         0//空闲模式
#define PD          1//掉电模式
#define PDBOD       2//空闲模式


/*-----------------------------------------
        外设功率控制寄存器PCONP位定义
------------------------------------------*/
#define PCTIM0      1//定时器0使能
#define PCTIM1      2//定时器1使能
#define PCURT0      3//UART0使能
#define PCURT1      4//UART1使能
#define PCPWM0      5//PWM0使能
#define PCI2C0      7//I2C0接口使能
#define PCSPI0      8//SPI接口使能
#define PCRTC       9//RTC使能
#define PCSPI1     10//SSP接口使能
#define PCAD0      12//A/D转换器0使能
#define PCI2C1     19//I2C1接口使能
#define PCAD1      20//A/D转换器1使能
/*-----------------------------------------
        WDMOD位定义
------------------------------------------*/
#define WDEN        0//
#define WDRESET     1//
#define WDTOF       2//
#define WDINT       3//

/*-----------------------------------------
        PLL 控制寄存器位定义
------------------------------------------*/
#define PLLEN       0//PLL 使能
#define PLLLK       1//PLL 连接
/*-----------------------------------------
        PLL 状态寄存器位定义
------------------------------------------*/
#define PLLE        8//PLL 使能位
#define PLLC        9//PLL 连接位
#define PLOCK      10//PLL 锁定状态

/*--------------------------------------------------
        外部中断标志寄存器EXTINT位定义
---------------------------------------------------*/
#define EINT0  0//EXTINT.0//写'1'清除EINT0中断标志
#define EINT1  1//EXTINT.1//写'1'清除EINT1中断标志
#define EINT2  2//EXTINT.2//写'1'清除EINT2中断标志
#define EINT3  3//EXTINT.3//写'1'清除EINT3中断标志

/*--------------------------------------------------
        外部中断方式寄存器EXTMODE位定义
---------------------------------------------------*/
#define EXTMODE0 0//EXTMODE.0//该位为0时，EINT0使用电平激活；该位为1时，EINT0使用边沿激活。
#define EXTMODE1 1//EXTMODE.1//该位为0时，EINT1使用电平激活；该位为1时，EINT1使用边沿激活。
#define EXTMODE2 2//EXTMODE.2//该位为0时，EINT2使用电平激活；该位为1时，EINT2使用边沿激活。
#define EXTMODE3 3//EXTMODE.3//该位为0时，EINT3使用电平激活；该位为1时，EINT3使用边沿激活。

/*--------------------------------------------------
        外部中断极性寄存器EXTPOLAR位定义  
---------------------------------------------------*/
#define EXTPOLAR0 0//EXTPOLAR.0//该位为0时，EINT0低电平或下降沿有效（由EXTMODE0决定）。
                   //该位为1时，EINT0高电平或上升沿有效（由EXTMODE0决定）。
#define EXTPOLAR1 1//EXTPOLAR.1//该位为0时，EINT1低电平或下降沿有效（由EXTMODE1决定）。
                   //该位为1时，EINT1高电平或上升沿有效（由EXTMODE1决定）。
#define EXTPOLAR2 2//EXTPOLAR.2//该位为0时，EINT2低电平或下降沿有效（由EXTMODE2决定）。
                   //该位为1时，EINT2高电平或上升沿有效（由EXTMODE2决定）。
#define EXTPOLAR3 3//EXTPOLAR.3//该位为0时，EINT3低电平或下降沿有效（由EXTMODE3决定）。
                   //该位为1时，EINT3高电平或上升沿有效（由EXTMODE3决定）。

/*--------------------------------------------------
        外部中断唤醒寄存器EXTWAKE位定义  
---------------------------------------------------*/
#define EXTWAKE0  0//EXTWAKE.0//该位为1时，使能EINT0将处理器从掉电模式唤醒。
#define EXTWAKE1  1//EXTWAKE.1//该位为1时，使能EINT1将处理器从掉电模式唤醒。
#define EXTWAKE2  2//EXTWAKE.2//该位为1时，使能EINT2将处理器从掉电模式唤醒。
#define EXTWAKE3  3//EXTWAKE.3//该位为1时，使能EINT3将处理器从掉电模式唤醒。
#define BODWAKE  14//EXTWAKE.14//该位为1时，BOD中断产生时可将处理器从掉电模式唤醒。
#define RTCWAKE  15//EXTWAKE.15//该位为1时，RTC中断产生时可将处理器从掉电模式唤醒。

/*---------------------------------------------------------------------------------------
  GPIO管脚功能配置
应用示例：
  PINSEL->PIN_SEL0  |= (P0_0_TXD0 << P0_0_PINSEL) | (P0_1_RXD0 << P0_1_PINSEL);
                   //选择P0.0和P0.1为UART0的输出输入引脚

  PINSEL->PIN_SEL0  |= (P0_3_EINT1 << P0_3_PINSEL); //选择P0.3为INT1外部中断引脚
  PINSEL->PIN_SEL0  |= (P0_14_EINT1 << P0_14_PINSEL); //选择P0.14也可为INT1外部中断引脚

  PINSEL->PIN_SEL0  |= (P0_1_EINT0 << P0_1_PINSEL)   //选择P0.1为INT0外部中断引脚
  PINSEL->PIN_SEL1  |= (P0_16_EINT0 << P0_16_PINSEL); //选择P0.16也可为INT0外部中断引脚
------------------------------------------------------------------------------------------*/

#define P0_0_GPIO      __0//通用数字输入输出管脚
  #define P0_0_TXD0    __1//UART0的发送器输出
  #define P0_0_PWM1    __2//脉宽调制器输出1
#define P0_0_PINSEL    2 * P0_0

#define P0_1_GPIO      __0//通用数字输入输出管脚
  #define P0_1_RXD0    __1//UART0的接收器输入
  #define P0_1_PWM3    __2//脉宽调制器输出3
  #define P0_1_EINT0   __3//**外部中断0输入
#define P0_1_PINSEL    2 * P0_1

#define P0_2_GPIO      __0//通用数字输入输出管脚
  #define P0_2_SCL0    __1//I2C0时钟输入/输出。开漏输出(符合I2C规范)
  #define P0_2_CAP0_0  __2//***定时器0的捕获输入通道0
#define P0_2_PINSEL    2 * P0_2

#define P0_3_GPIO      __0//通用数字输入输出管脚
  #define P0_3_SDA0    __1//I2C0数据输入/输出。开漏输出(符合I2C规范)
  #define P0_3_MAT0_0  __2//**定时器0的匹配输出通道0
  #define P0_3_EINT1   __3//**外部中断1输入
#define P0_3_PINSEL    2 * P0_3

#define P0_4_GPIO      __0//通用数字输入输出管脚
  #define P0_4_SCK0    __1//SPI0的串行时钟。SPI时钟从主机输出，从机输入
  #define P0_4_CAP0_1  __2//**定时器0的捕获输入通道1
  #define P0_4_AD0_6   __3//A/D转换器0输入6。该模拟输入总是连接到相应的管脚
#define P0_4_PINSEL  2 * P0_4

#define P0_5_GPIO      __0//通用数字输入输出管脚
  #define P0_5_MISO0   __1//SPI0主机输入从机输出端。从机到主机的数据传输
  #define P0_5_MAT0_1  __2//**定时器0的匹配输出通道1
  #define P0_5_AD0_7   __3//A/D转换器0输入7。该模拟输入总是连接到相应的管脚
#define P0_5_PINSEL    2 * P0_5

#define P0_6_GPIO      __0//通用数字输入输出管脚
  #define P0_6_MOSI0   __1//SPI0主机输出从机输入端。主机到从机的数据传输
  #define P0_6_CAP0_2  __2//***定时器0的捕获输入通道2
  #define P0_6_AD1_0   __3//A/D转换器1输入0。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_6_PINSEL    2 * P0_6

#define P0_7_GPIO      __0//通用数字输入输出管脚
  #define P0_7_SSEL0   __1//SPI0从机选择。选择SPI接口用作从机
  #define P0_7_PWM2    __2//脉宽调制器输出2
  #define P0_7_EINT2   __3//**外部中断2输入
#define P0_7_PINSEL    2 * P0_7

#define P0_8_GPIO      __0//通用数字输入输出管脚
  #define P0_8_TXD1    __1//UART1的发送器输出
  #define P0_8_PWM4    __2//脉宽调制器输出4
  #define P0_8_AD1_1   __3//A/D转换器1输入1。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_8_PINSEL    2 * P0_8

#define P0_9_GPIO      __0//通用数字输入输出管脚
  #define P0_9_RXD1    __1//UART1的接收器输入
  #define P0_9_PWM6    __2//脉宽调制器输出6
  #define P0_9_EINT3   __3//***外部中断3输入
#define P0_9_PINSEL    2 * P0_9

#define P0_10_GPIO     __0//通用数字输入输出管脚
  #define P0_10_RTS1   __1//UART1请求发送出端（仅用于LP138）
  #define P0_10_CAP1_0 __2//定时器1的捕获输入通道0
  #define P0_10_AD1_2  __3//A/D转换器1输入2。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_10_PINSEL   2 * P0_10

#define P0_11_GPIO     __0//通用数字输入输出管脚
  #define P0_11_CTS1   __1//UART1清除发送入端（仅用于LP138）
  #define P0_11_CAP1_1 __2//定时器1的捕获输入通道1
  #define P0_11_SCL1   __3//I2C1时钟输入/输。开漏输出(符合I2C规范）
#define P0_11_PINSEL   2 * P0_11

#define P0_12_GPIO     __0//通用数字输入输出管脚
  #define P0_12_DSR1   __1//UART1数据设置就绪端（仅用于 LPC2138）
  #define P0_12_MAT1_0 __2//定时器1的匹配输出通道0
  #define P0_12_AD1_3  __3//A/D转换器1输入3。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_12_PINSEL   2 * P0_12

#define P0_13_GPIO     __0//通用数字输入输出管脚
  #define P0_13_DTR1   __1//UART1数据终端就绪
  #define P0_13_MAT1_1 __2//定时器1的匹配输出通道1
  #define P0_13_AD1_4  __3//A/D转换器1输入4。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_13_PINSEL   2 * P0_13

#define P0_14_GPIO     __0//通用数字输入输出管脚
  #define P0_14_DCD1   __1//UART1数据载波检测输入（仅用于 LPC2138）
  #define P0_14_EINT1  __2//**外部中断1输入
  #define P0_14_SDA1   __3//I2C1数据输入/输出。开漏输出(符合I2C规范）
#define P0_14_PINSEL   2 * P0_14

#define P0_15_GPIO     __0//通用数字输入输出管脚
  #define P0_15_RI1    __1//UART1铃响指示输入（仅用于 LPC2138）
  #define P0_15_EINT2  __2//**外部中断2输入
  #define P0_15_AD1_5  __3//A/D转换器1输入5。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
#define P0_15_PINSEL   2 * P0_15

#define P0_16_GPIO     __0//通用数字输入输出管脚
  #define P0_16_EINT0  __1//**外部中断0输入
  #define P0_16_MAT0_2 __2//**定时器0的匹配输出通道2
  #define P0_16_CAP0_2 __3//***定时器0的捕获输入通道2
#define P0_16_PINSEL   2 * P0_0


#define P0_17_GPIO     __0//通用数字输入输出管脚
  #define P0_17_CAP1_2 __1//**定时器1的捕获输入通道2
  #define P0_17_SCK1   __2//SPI1的串行时钟。SPI时钟从主机输出，从机输入
  #define P0_17_MAT1_2 __3//**定时器1的匹配输出通道2
#define P0_17_PINSEL   2 * P0_1

#define P0_18_GPIO     __0//通用数字输入输出管脚
  #define P0_18_CAP1_3 __1//**定时器1的捕获输入通道3
  #define P0_18_MISO1  __2//SPI1主机输入从机输出端。从机到主机的数据传输
  #define P0_18_MAT1_3 __3//**定时器1的匹配输出通道3
#define P0_18_PINSEL   2 * P0_2


#define P0_19_GPIO     __0//通用数字输入输出管脚
  #define P0_19_MAT1_2 __1//**定时器1的匹配输出通道2
  #define P0_19_MOSI1  __2//SPI1主机输出从机输入端。主机到从机的数据传输
  #define P0_19_CAP1_2 __3//**定时器1的捕获输入通道2
#define P0_19_PINSEL   2 * P0_3


#define P0_20_GPIO     __0//通用数字输入输出管脚
  #define P0_20_MAT1_3 __1//**定时器1的匹配输出通道3
  #define P0_20_SSEL1  __2//SPI1从机选择。选择SPI接口用作从机
  #define P0_20_EINT3  __3//***外部中断3输入
#define P0_20_PINSEL   2 * P0_4


#define P0_21_GPIO     __0//通用数字输入输出管脚
  #define P0_21_PWM5   __1//脉宽调制器输出5
  #define P0_21_AD1_6  __2//A/D转换器1输入6。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
  #define P0_21_CAP1_3 __3//**定时器1的捕获输入通道3
#define P0_21_PINSEL   2 * P0_5


#define P0_22_GPIO     __0//通用数字输入输出管脚
  #define P0_22_AD1_7  __1//A/D转换器1输入7。该模拟输入总是连接到相应的管脚（仅用于 LPC2138）
  #define P0_22_CAP0_0 __2//***定时器0的捕获输入通道0
  #define P0_22_MAT0_0 __3//**定时器0的匹配输出通道0
#define P0_22_PINSEL   2 * P0_6


#define P0_23_GPIO     __0//通用数字输入输出管脚
#define P0_23_PINSEL   2 * P0_7

/*-----------------------------------------------------------------------
#define P0_24_GPIO     0//P0.24 脚未用
#define P0_24_PINSEL 2 * P0_8
------------------------------------------------------------------------*/


#define P0_25_GPIO     __0//通用数字输入输出管脚
  #define P0_25_AD0_4  __1//A/D转换器0输入4。该模拟输入总是连接到相应的管脚.
  #define P0_25_DAC    __2//D/A 转换器输出（仅用于 LPC2138）
#define P0_25_PINSEL   2 * P0_9


#define P0_26_GPIO     __0//通用数字输入输出管脚
  #define P0_26_AD0_5  __1//A/D转换器0输入5。该模拟输入总是连接到相应的管脚
#define P0_26_PINSEL   2 * P0_10


#define P0_27_GPIO     __0//通用数字输入输出管脚
  #define P0_27_AD0_0  __1//A/D转换器0输入0。该模拟输入总是连接到相应的管脚
  #define P0_27_CAP0_1 __2//**定时器0的捕获输入通道1
  #define P0_27_MAT0_1 __3//**定时器0的捕获输入通道1
#define P0_27_PINSEL   2 * P0_11


#define P0_28_GPIO     __0//通用数字输入输出管脚
  #define P0_28_AD0_1  __1//A/D转换器0输入1。该模拟输入总是连接到相应的管脚
  #define P0_28_CAP0_2 __2//***定时器0的捕获输入通道2
  #define P0_28_MAT0_2 __3//**定时器0的匹配输出通道2
#define P0_28_PINSEL   2 * P0_12


#define P0_29_GPIO     __0//通用数字输入输出管脚
  #define P0_29_AD0_2  __1//A/D转换器0输入2。该模拟输入总是连接到相应的管脚
  #define P0_29_CAP0_3 __2//定时器0的捕获输入通道3
  #define P0_29_MAT0_3 __3//定时器0的匹配输出通道3
#define P0_29_PINSEL   2 * P0_13


#define P0_30_GPIO     __0//通用数字输入输出管脚
  #define P0_30_AD0_3  __1//A/D转换器0输入3。该模拟输入总是连接到相应的管脚
  #define P0_30_EINT3  __2//***外部中断3输入
  #define P0_30_CAP0_0 __3//***定时器0的捕获输入通道0
#define P0_30_PINSEL   2 * P0_14


#define P0_31_GPO      __0//通用数字输出管脚（注意：此管脚仅为输出）
#define P0_31_PINSEL   2 * P0_15




  
/*------------------------------------------------------------------------
        结构指针在ARM之应用(愚人节版)
------------------------------------------------------------------------*/


typedef struct _LPCS_VIC {
  LPC_REG IRQStatus;//IRQ 状态寄存器
  LPC_REG FIQStatus;//FIQ 状态请求
  LPC_REG RawIntr;//所有中断的状态寄存器
  LPC_REG IntSelect;//中断选择寄存器
  LPC_REG IntEnable;//中断使能寄存器
  LPC_REG IntEnClr;//中断使能清零寄存器
  LPC_REG SoftInt;//软件中断寄存器
  LPC_REG SoftIntClr;//软件中断清零寄存器
  LPC_REG Protection;//保护使能寄存器
  LPC_REG Reserved1[3]; //保留3个空位
  LPC_REG VectAddr;//向量地址寄存器
  LPC_REG DefVectAddr;//默认向量地址寄存器
  LPC_REG Reserved2[2]; //保留2个空位
  LPC_REG Reserved3[48];//保留48个空位
  LPC_REG VectAddrs[16];//向量地址寄存器，VICVectAddr0~VICVectAddr15
  LPC_REG Reserved4[48];//保留48个空位
  LPC_REG VectCntls[16];//向量控制寄存器，VICVectCntl0~VICVectCntl15
}LPCS_VIC, *LPCPS_VIC;

#define LPC_BASE_VIC  ((LPCPS_VIC)  0xFFFFF000)//定义硬件结构指针（硬件地址）
const LPCPS_VIC VIC = LPC_BASE_VIC;//定义全局结构指针变量

typedef struct _LPCS_PINSEL {
  LPC_REG PIN_SEL0;//管脚功能选择寄存器0
  LPC_REG PIN_SEL1;//管脚功能选择寄存器1
  LPC_REG Reserved[4]; //保留4个空位
  LPC_REG PIN_SEL2;//管脚功能选择寄存器2
}LPCS_PINSEL, *LPCPS_PINSEL;

#define LPC_BASE_PINSEL  ((LPCPS_PINSEL)  0xE002C000)//定义硬件结构指针（硬件地址）
const LPCPS_PINSEL PINSEL = LPC_BASE_PINSEL;//定义全局结构指针变量PINSEL

typedef struct _LPCS_MAM {
  LPC_REG MAM_CR;//存储器加速器模块控制寄存器
  LPC_REG MAM_TIM;//存储器加速器定时控制
}LPCS_MAM, *LPCPS_MAM;

#define LPC_BASE_MAM  ((LPCPS_MAM)  0xE01FC000)//定义硬件结构指针（硬件地址）
const LPCPS_MAM MAM = LPC_BASE_MAM;//定义全局结构指针变量MAM

typedef struct _LPCS_PLL {//锁相环
  LPC_REG PLL_CON;//PLL 控制寄存器
  LPC_REG PLL_CFG;//PLL 配置寄存器
  LPC_REG PLL_STAT;//PLL 状态寄存器
  LPC_REG PLL_FEED;//PLL 愦送寄存器
}LPCS_PLL, *LPCPS_PLL;

#define LPC_BASE_PLL  ((LPCPS_PLL)  0xE01FC080)//定义硬件结构指针（硬件地址）
const LPCPS_PLL PLL = LPC_BASE_PLL;//定义全局结构指针变量PLL


typedef struct _LPCS_GPIO {//通用I/O口
  LPC_REG IOPIN;//GPIO管脚值寄存器
  LPC_REG IOSET;//GPIO输出置位寄存器
  LPC_REG IODIR;//GPIO方向寄存器
  LPC_REG IOCLR;//GPIO输出清零寄存器
}LPCS_GPIO, *LPCPS_GPIO;


#define LPC_BASE_GPIO0  ((LPCPS_GPIO)  0xE0028000)//定义硬件结构指针（硬件地址）
#define LPC_BASE_GPIO1  ((LPCPS_GPIO)  0xE0028010)//定义硬件结构指针（硬件地址）
const LPCPS_GPIO P0 = LPC_BASE_GPIO0;//定义全局结构指针变量P0
const LPCPS_GPIO P1 = LPC_BASE_GPIO1;//定义全局结构指针变量P1
/*--------------------------------------------------------------------
应用示例
  P0->IODIR |= (1 << P0_8);//设置P0.8为输出
  P0->IOSET  = (1 << P0_8);//P0.8输出高电平
  P0->IOCLR  = (1 << P0_8);//P0.8输出低电平
  P0->IOPIN ^= (1 << P0_8);//P0.8输出电平翻转

  P1->IODIR |= (1 << P1_8);//设置P1.8为输出
  P1->IOSET  = (1 << P1_8);//P1.8输出高电平
  P1->IOCLR  = (1 << P1_8);//P1.8输出低电平
  P1->IOPIN ^= (1 << P1_8);//P1.8输出电平翻转
----------------------------------------------------------------------*/

 

typedef struct _LPCS_UART {
  union {//地址冲突处理
    LPC_REG _RBR;//接收缓冲
    LPC_REG _THR;//发送保持
    LPC_REG _DLL;//除数锁存低位
  }RBR_THR_DLL;//收发数据
  union {//地址冲突处理
    LPC_REG _IER;//中断使能
    LPC_REG _DLM;//除数锁存高位
  }IER_DLM;
  union {//地址冲突处理
    LPC_REG _IIR;//中断ID
    LPC_REG _FCR;//FIFO控制
  }IIR_FCR;//(8)
  LPC_REG LCR;//线控制
  LPC_REG MCR;//Modem控制（只有UART1）
  LPC_REG LSR;//线状态)
  LPC_REG MSR;//Modem状态（只有UART1）
  LPC_REG SCR;//高速缓存
  LPC_REG Reserved[4]; //保留4个空位
  LPC_REG TER;//发送使能
}LPCS_UART, *LPCPS_UART;

#define RBR RBR_THR_DLL._RBR
#define THR RBR_THR_DLL._THR
#define DLL RBR_THR_DLL._DLL

#define IER IER_DLM._IER 
#define DLM IER_DLM._DLM 

#define IIR IIR_FCR._IIR
#define FCR IIR_FCR._FCR


#define LPC_BASE_UART0  ((LPCPS_UART)  0xE000C000)//定义硬件结构指针（硬件地址）
const LPCPS_UART U0 = LPC_BASE_UART0;//定义全局结构指针变量U0
#define LPC_BASE_UART1  ((LPCPS_UART)  0xE0010000)//定义硬件结构指针（硬件地址）
const LPCPS_UART U1 = LPC_BASE_UART1;//定义全局结构指针变量U1


typedef struct _LPCS_TIMER {//定时器
  LPC_REG TIMER_IR;//中断寄存器
  LPC_REG TIMER_TCR;//定时器控制寄存器
  LPC_REG TIMER_TC;//定时器计数器
  LPC_REG TIMER_PR;//预分频寄存器
  LPC_REG TIMER_PC;//预分频计数器
  LPC_REG TIMER_MCR;
  LPC_REG TIMER_MR0;
  LPC_REG TIMER_MR1;
  LPC_REG TIMER_MR2;
  LPC_REG TIMER_MR3;
  LPC_REG TIMER_CCR;
  LPC_REG TIMER_CR0;
  LPC_REG TIMER_CR1;
  LPC_REG TIMER_CR2;
  LPC_REG TIMER_CR3;
  LPC_REG TIMER_EMR;
  LPC_REG Reserved[12]; //保留12个空位
  LPC_REG TIMER_CTCR;
}LPCS_TIMER, *LPCPS_TIMER;


#define LPC_BASE_TIMER0  ((LPCPS_TIMER)  0xE0004000)//定义硬件结构指针（硬件地址）
#define LPC_BASE_TIMER1  ((LPCPS_TIMER)  0xE0008000)//定义硬件结构指针（硬件地址）
const LPCPS_TIMER T0 = LPC_BASE_TIMER0;//定义全局结构指针变量T0
const LPCPS_TIMER T1 = LPC_BASE_TIMER1;//定义全局结构指针变量T1


typedef struct _LPCS_PWM {
  LPC_REG PWM_IR; //中断寄存器
  LPC_REG PWM_TCR;//PWM定时器控制寄存器
  LPC_REG PWM_TC; //PWM定时器计数器
  LPC_REG PWM_PR; //PWM预分频寄存器
  LPC_REG PWM_PC; //PWM预分频计数器寄存器
  LPC_REG PWM_MCR;//PWM匹配控制寄存器
  LPC_REG PWM_MR0;//PWM匹配寄存器0
  LPC_REG PWM_MR1;//PWM匹配寄存器1
  LPC_REG PWM_MR2;//PWM匹配寄存器2
  LPC_REG PWM_MR3;//PWM匹配寄存器3
  LPC_REG Reserved[6]; //保留6个空位
  LPC_REG PWM_MR4;//PWM匹配寄存器4
  LPC_REG PWM_MR5;//PWM匹配寄存器5
  LPC_REG PWM_MR6;//PWM匹配寄存器6
  LPC_REG PWM_PCR;//PWM控制寄存器
  LPC_REG PWM_LER;//PWM锁存使能寄存器
}LPCS_PWM, *LPCPS_PWM;

#define LPC_BASE_PWM  ((LPCPS_PWM)  0xE0014000)//定义硬件结构指针（硬件地址）
const LPCPS_PWM PWM = LPC_BASE_PWM;//定义全局结构指针变量PWM

typedef struct _LPCS_I2C {
  LPC_REG I2C_CONSET; //I2C控制置位寄存器
  LPC_REG I2C_STAT;   //I2C状态寄存器
  LPC_REG I2C_DAT;   //I2C数据寄存器
  LPC_REG I2C_ADR;   //I2C从地址寄存器
  LPC_REG I2C_SCLH;   //SCH占空比寄存器高半字
  LPC_REG I2C_SCLL;   //SCL占空比寄存器低半字
  LPC_REG I2C_CONCLR; //I2C控制清零寄存器
}LPCS_I2C, *LPCPS_I2C;//


#define LPC_BASE_I2C0  ((LPCPS_I2C)  0xE001C000)//定义硬件结构指针（硬件地址）
#define LPC_BASE_I2C1  ((LPCPS_I2C)  0xE005C000)//定义硬件结构指针（硬件地址）
const LPCPS_I2C I2C0 = LPC_BASE_I2C0;//定义全局结构指针变量I2C0
const LPCPS_I2C I2C1 = LPC_BASE_I2C1;//定义全局结构指针变量I2C1

typedef struct _LPCS_SPI {
  LPC_REG SPI_SPCR;
  LPC_REG SPI_SPSR;
  LPC_REG SPI_SPDR;
  LPC_REG SPI_SPCCR;
  LPC_REG Reserved[4]; //保留4个空位
  LPC_REG SPI_SPINT;
}LPCS_SPI, *LPCPS_SPI;

#define LPC_BASE_SPI  ((LPCPS_SPI)  0xE0020000)//定义硬件结构指针（硬件地址）
const LPCPS_SPI SPI = LPC_BASE_SPI;//定义全局结构指针变量SPI

typedef struct _LPCS_SSP {
  LPC_REG SSP_CR0;
  LPC_REG SSP_CR1;
  LPC_REG SSP_DR;
  LPC_REG SSP_SR;   //SSP状态寄存器
  LPC_REG SSP_CPSR;
  LPC_REG SSP_IMSC;
  LPC_REG SSP_RIS;
  LPC_REG SSP_MIS;
  LPC_REG SSP_ICR;
}LPCS_SSP, *LPCPS_SSP;

#define LPC_BASE_SSP  ((LPCPS_SSP)  0xE0068000)//定义硬件结构指针（硬件地址）
const LPCPS_SSP SSP = LPC_BASE_SSP;//定义全局结构指针变量SSP

typedef struct _LPCS_RTC {
  LPC_REG RTC_ILR;//中断位置寄存器
  LPC_REG RTC_CTC;//时钟节拍计数器
  LPC_REG RTC_CCR;//时钟控制寄存器
  LPC_REG RTC_CIIR;//计数器递增中断寄存器
  LPC_REG RTC_AMR;//报警屏蔽寄存器
  LPC_REG RTC_CTIME0;//完整时间寄存器0
  LPC_REG RTC_CTIME1;//完整时间寄存器1
  LPC_REG RTC_CTIME2;//完整时间寄存器2
  LPC_REG RTC_SEC;//秒寄存器
  LPC_REG RTC_MIN;//分寄存器
  LPC_REG RTC_HOUR;//小时寄存器
  LPC_REG RTC_DOM;//日期（月）寄存器
  LPC_REG RTC_DOW;//星期寄存器
  LPC_REG RTC_DOY;//日期（年）寄存器
  LPC_REG RTC_MONTH;//月寄存器
  LPC_REG RTC_YEAR;//年寄存器
  LPC_REG Reserved[8]; //保留8个空位
  LPC_REG RTC_ALSEC;//秒报警值
  LPC_REG RTC_ALMIN;//分报警值
  LPC_REG RTC_ALHOUR;//小时报警值
  LPC_REG RTC_ALDOM;//日期（月）报警值
  LPC_REG RTC_ALDOW;//星期报警值
  LPC_REG RTC_ALDOY;//日期（年）报警值
  LPC_REG RTC_ALMONTH;//月报警值
  LPC_REG RTC_ALYEAR;//年报警值
  LPC_REG RTC_PREINT;//预分频值，整数部分
  LPC_REG RTC_PREFRAC;//预分频值，小数部分
}LPCS_RTC, *LPCPS_RTC;

#define LPC_BASE_RTC  ((LPCPS_RTC)  0xE0024000)//定义硬件结构指针（硬件地址）
const LPCPS_RTC RTC = LPC_BASE_RTC;//定义全局结构指针变量RTC


typedef struct _LPCS_WDT {
  LPC_REG WDT_WDMOD;//狗模式寄
  LPC_REG WDT_WDTC;//看门狗定时器常数寄存器
  LPC_REG WDT_WDFEED;//看门狗喂狗寄存器
  LPC_REG WDT_WDTV;//看门狗定时器值寄存器
}LPCS_WDT, *LPCPS_WDT;

#define LPC_BASE_WDT  ((LPCPS_WDT)  0xE0000000)//定义硬件结构指针（硬件地址）
const LPCPS_WDT WDT = LPC_BASE_WDT;//定义全局结构指针变量WDT

typedef struct _LPCS_ADC {
  LPC_REG ADCR; //A/D 控制寄存器
  LPC_REG ADDR; //A/D 数据寄存器
  LPC_REG AD_GSR;//A/D 全局启动寄存器
}LPCS_ADC, *LPCPS_ADC;

#define LPC_BASE_ADC0  ((LPCPS_ADC)  0xE0034000)//定义硬件结构指针（硬件地址）
#define LPC_BASE_ADC1  ((LPCPS_ADC)  0xE0060000)//定义硬件结构指针（硬件地址）
const LPCPS_ADC ADC0 = LPC_BASE_ADC0;//定义全局结构指针变量ADC0
const LPCPS_ADC ADC1 = LPC_BASE_ADC1;//定义全局结构指针变量ADC1

typedef struct _LPCS_INTCON {
  LPC_REG EXT_INT;//外部中断标志寄存器
  LPC_REG INT_WAKE;//外部中断唤醒寄存器
  LPC_REG EXT_MODE;//外部中断方式寄存器
  LPC_REG EXT_POLAR;//外部中断极性寄存器
}LPCS_INTCON, *LPCPS_INTCON;

#define LPC_BASE_INTCON  ((LPCPS_INTCON)  0xE01FC140)//定义硬件结构指针（硬件地址）
const LPCPS_INTCON INTCON = LPC_BASE_INTCON;//定义全局结构指针变量INTCON

typedef struct _LPCS_POWER {
  LPC_REG P_CON;//功率控制寄存器
  LPC_REG P_CONP;//外部功率控制寄存器
}LPCS_POWER, *LPCPS_POWER;

#define LPC_BASE_POWER  ((LPCPS_POWER)  0xE01FC0C0)//定义硬件结构指针（硬件地址）
const LPCPS_POWER POWER = LPC_BASE_POWER;//定义全局结构指针变量INTCON

typedef struct _LPCS_SYSCON {
  LPC_REG MEM_MAP;//存储器映射控制     //0xE01FC040
  LPC_REG Reserved0[15]; //保留16个空位 //0xE01FC044
  LPC_REG PLL_CON;//PLL 控制寄存器  //0xE01FC080
  LPC_REG PLL_CFG;//PLL 配置寄存器  //0xE01FC084
  LPC_REG PLL_STAT;//PLL 状态寄存器  //0xE01FC088
  LPC_REG PLL_FEED;//PLL 愦送寄存器  //0xE01FC08C
  LPC_REG Reserved1[12]; //保留4个空位 //0xE01FC090
  LPC_REG P_CON;//功率控制寄存器  //0xE01FC0C0
  LPC_REG P_CONP;//外部功率控制寄存器 //0xE01FC0C4
  LPC_REG Reserved2[14]; //保留14个空位 //0xE01FC0C8
  LPC_REG VPB_DIV;//VPB 分频器控制寄存器//0xE01FC100
  LPC_REG Reserved3[15]; //保留15个空位 //0xE01FC104
  LPC_REG EXT_INT;//外部中断标志寄存器 //0xE01FC140
  LPC_REG INT_WAKE;//外部中断唤醒寄存器 //0xE01FC144
  LPC_REG EXT_MODE;//外部中断方式寄存器 //0xE01FC148
  LPC_REG EXT_POLAR;//外部中断极性寄存器//0xE01FC14C
  LPC_REG Reserved4[12]; //保留12个空位 //0xE01FC150
  LPC_REG RS_ID;//复位源识别寄存器  //0xE01FC180
  LPC_REG CS_PR;//代码安全保护寄存器 //0xE01FC184
}LPCS_SYSCON, *LPCPS_SYSCON;

#define LPC_BASE_SYSCON  ((LPCPS_SYSCON)  0xE01FC040)//定义硬件结构指针（硬件地址）
const LPCPS_SYSCON SYSCON = LPC_BASE_SYSCON;//定义全局结构指针变量SYSCON

#define IAP_FCCLK            11059

/* 定义IAP命令字 */
                                    //   命令           参数
#define     IAP_SELECTOR        50  // 选择扇区     【起始扇区号、结束扇区号】
#define     IAP_RAMTOFLASH      51  // 拷贝数据     【FLASH目标地址、RAM源地址、写入字节数、系统时钟频率】
#define     IAP_ERASESECTOR     52  // 擦除扇区     【起始扇区号、结束扇区号、系统时钟频率】
#define     IAP_BLANKCHK        53  // 查空扇区     【起始扇区号、结束扇区号】
#define     IAP_READPARTID      54  // 读器件ID     【无】
#define     IAP_BOOTCODEID      55  // 读Boot版本号 【无】
#define     IAP_COMPARE         56  // 比较命令     【Flash起始地址、RAM起始地址、需要比较的字节数】
#define     IAP_EXEC            57

/* 定义IAP返回状态字 */
#define     CMD_SUCCESS          __0
#define     INVALID_COMMAND      __1
#define     SRC_ADDR_ERROR       __2 
#define     DST_ADDR_ERROR       __3
#define     SRC_ADDR_NOT_MAPPED  __4
#define     DST_ADDR_NOT_MAPPED  __5
#define     COUNT_ERROR          __6
#define     INVALID_SECTOR       __7
#define     SECTOR_NOT_BLANK     __8
#define     SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION __9
#define     COMPARE_ERROR        __10
#define     BUSY                 __11

#define IAP_LOCATION 0x7ffffff1//IAP函数入口地址
typedef void(*IAP)(unsigned int[], unsigned int[]);//IAP函数指针类型

#define Device_LPC2131  0x0002ff01// 196353
#define Device_LPC2132  0x0002ff11// 196369
#define Device_LPC2134  0x0002ff12// 196370
#define Device_LPC2136  0x0002ff23// 196387
#define Device_LPC2138  0x0002ff25// 196389


#endif  // __LPC213xDEF_H

