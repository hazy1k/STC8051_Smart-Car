#include<AT89X52.H>		      //包含51单片机头文件，内部有各种寄存器定义
#include <intrins.h>
#include <ZY-4WD_PWM.H>		  //包含ZY-1蓝牙智能小车驱动IO口定义等函数
#define uint    unsigned int                          //重定义无符号整数类型
#define uchar   unsigned char                         //重定义无符号字符类型

uchar code  LedShowData[]={0x03,0x9F,0x25,0x0D,0x99,  //定义数码管显示数据
                            0x49,0x41,0x1F,0x01,0x19};//0,1,2,3,4,5,6,7,8,9

uchar code  RecvData[]={0x19,0x46,0x15,0x44,0x43,0x40,0x0D,0x0E,0x00,0x0F};

uchar IRCOM[7];
unsigned char RunFlag=0;                              //定义运行标志位
bit EnableLight=0;                                    //定义指示灯使能位

/*************完成状态指示灯定义*************/
sbit S1=P3^2;                                         //定义S1按键端口
sbit S2=P3^4;                                         //定义S2按键端口
/*************完成按键端口的定义*************/       
sbit LeftLed=P2^0;                                    //定义前方左侧指示灯端口
sbit RightLed=P0^7;                                   //定义前方右侧指示灯端口

/*************完成红外探头端口定义***********/
sbit M1A=P1^2;                                        //定义电机1正向端口
sbit M1B=P1^3;                                        //定义电机1反向端口
sbit M2A=P1^6;                                        //定义电机2正向端口
sbit M2B=P1^7;                                        //定义电机2反向端口

sbit SB1=P2^3;                                        //定义蜂鸣端口
/*********完成话筒,光敏电阻,蜂鸣器.端口定义**/
sbit IRIN=P3^3;                                       //定义红外接收端口
/*********完成红外接收端口的定义*************/
#define ShowPort P0                                   //定义数码管显示端口

extern void ControlCar(uchar CarType);                //声明小车控制子程序

void delayms(unsigned char x)                         //0.14mS延时程序
{
  unsigned char i;                                    //定义临时变量
  while(x--)                                          //延时时间循环
  {
    for (i = 0; i<13; i++) {}                         //14mS延时
  }
}

void Delay1ms(unsigned int i) 
{ 
unsigned char j,k; 
do{ 
  j = 10; 
  do{ 
   k = 50; 
   do{ 
    _nop_(); 
   }while(--k);     
  }while(--j); 
}while(--i); 

} 
void Delay()                                          //定义延时子程序
{ uint DelayTime=30000;                               //定义延时时间变量
  while(DelayTime--);                                 //开始进行延时循环
  return;                                             //子程序返回
}


void ControlCar(unsigned char ConType)    //定义电机控制子程序
{
 
  stop(); //调用停止函数
  
 switch(ConType)                          //判断用户设定电机形式
 {
  case 1:  //前进                         //判断用户是否选择形式1
  { 
    
	 stop(); //调用停止函数						      //进入前进之前 先停止一段时间  防止电机反向电压冲击主板 导致系统复位
	 Delay1ms(240);
	LeftLed = 0 ;
	run();	 //调用前进函数
	ShowPort=LedShowData[1];
    break;
  }
  case 2: //后退                              //判断用户是否选择形式2
  { 
     stop(); //调用停止函数							      //进入后退之前 先停止一段时间  防止电机反向电压冲击主板 导致系统复位
	  Delay1ms(240);
	LeftLed = 1 ; 	 
	 backrun();
	ShowPort=LedShowData[2];                                //M2电机反转
    break;
  }
  case 3: //左转                         //判断用户是否选择形式3
  { 
     stop(); //调用停止函数				//进入左转之前 先停止一段时间  防止电机反向电压冲击主板 导致系统复位
	 Delay1ms(240); 
	 leftrun();
	ShowPort=LedShowData[3];                    
	break;
  }
  case 4: //右转                              //判断用户是否选择形式4
  { 
    stop(); //调用停止函数		//进入右转之前 先停止一段时间  防止电机反向电压冲击主板 导致系统复位
	  Delay1ms(240);
	 rightrun();	 //调用小车右转函数                                //M1电机正转
    ShowPort=LedShowData[4];                                      //M2电机反转
	break;
  }
  case 5: //停止                          //判断用户是否选择形式8
  {
    stop(); //调用停止函数	
	ShowPort=LedShowData[0]; 
	break; 
	                              //退出当前选择
  }
 }
}

void IR_IN() interrupt 2 using 0                      //定义INT2外部中断函数
{
  unsigned char j,k,N=0;                              //定义临时接收变量
   
  EX1 = 0;                                            //关闭外部中断,防止再有信号到达   
  delayms(15);                                        //延时时间，进行红外消抖
  if (IRIN==1)                                        //判断红外信号是否消失
  {  
     EX1 =1;                                          //外部中断开
	 return;                                          //返回
  } 
                           
  while (!IRIN)                                       //等IR变为高电平，跳过9ms的前导低电平信号。
  {
      delayms(1);                                     //延时等待
  }

  for (j=0;j<4;j++)                                   //采集红外遥控器数据
  { 
    for (k=0;k<8;k++)                                 //分次采集8位数据
    {
       while (IRIN)                                   //等 IR 变为低电平，跳过4.5ms的前导高电平信号。
       {
         delayms(1);                                  //延时等待
       }
       
       while (!IRIN)                                  //等 IR 变为高电平
       {
         delayms(1);                                  //延时等待
       }
   
       while (IRIN)                                   //计算IR高电平时长
       {
         delayms(1);                                  //延时等待
         N++;                                         //计数器加加
         if (N>=30)                                   //判断计数器累加值
	     { 
           EX1=1;                                     //打开外部中断功能
	       return;                                    //返回
         }                   
       }
                                       
      IRCOM[j]=IRCOM[j] >> 1;                         //进行数据位移操作并自动补零
     
      if (N>=8)                                       //判断数据长度 
      {
         IRCOM[j] = IRCOM[j] | 0x80;                  //数据最高位补1
      } 
      N=0;                                            //清零位数计录器
    }
  }
   
  if (IRCOM[2]!=~IRCOM[3])                            //判断地址码是否相同
  { 
     EX1=1;                                           //打开外部中断
     return;                                          //返回
  }

  for(j=0;j<10;j++)                                   //循环进行键码解析
   {
      if(IRCOM[2]==RecvData[j])                       //进行键位对应
      {
        ControlCar(j);                                          //数码管显示相应数码
      }
   }
   
   EX1 = 1;                                           //外部中断开 
} 

void main(void)                                       //主程序入口
{
 bit ExeFlag=0;                                       //定义可执行位变量
 EX1=1;                                               //同意开启外部中断1
 IT1=1;                                               //设定外部中断1为低边缘触发类型
 EA=1; 
 TMOD=0X01;
 TH0= 0XFc;		  //1ms定时
 TL0= 0X18;
 TR0= 1;
  ET0= 1;
 ShowPort=LedShowData[0];                             //数码管显示数字0
while(1)                                              //程序主循环
 {   
   Delay();                                           //延时  
 }
}

