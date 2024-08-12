    #include<AT89x51.H>
    #include <intrins.h>
	#include<HJ-4WD_PWM.H>		  //包含HL-1蓝牙智能小车驱动IO口定义等函数
    #define Left_1_led        P3_7	 //左循迹传感器    
	
    #define Right_1_led       P3_6	 //右循迹传感器 
	
    #define LeftIRBZ          P3_5	 //左避障传感器	  
	
	#define RightIRBZ         P3_4	 //右避障传感器	    

sbit SB1=P2^3;                            //定义蜂鸣器端口
sbit IRIN=P3^3;                                       //定义红外接收端口

unsigned char code  LedShowData[]={0x03,0x9F,0x25,0x0D,0x99,  //定义数码管显示数据
                                   0x49,0x41,0x1F,0x01,0x19};//0,1,2,3,4,5,6,7,8,9
unsigned char code  RecvData[]={0x19,0x46,0x15,0x43,0x44,0x40,0x0D,0x0E,0x00,0x0F};
unsigned char IRCOM[7];

#define ShowPort P0                                   //定义数码管显示端口
unsigned char temp = 1;

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

void delay_nus(unsigned int i)  //延时:i>=12 ,i的最小延时单12 us
{ 
  i=i/10;
  while(--i);
}   
void delay_nms(unsigned int n)  //延时n ms
{ 
  n=n+1;
  while(--n)  
  delay_nus(900);         //延时 1ms,同时进行补偿
  
}  

void delayms(unsigned char x)                         //0.14mS延时程序
{
  unsigned char i;                                    //定义临时变量
  while(x--)                                          //延时时间循环
  {
    for (i = 0; i<13; i++) {}                         //14mS延时
  }
}

void Delay()                                          //定义延时子程序
{ 
  unsigned int DelayTime=30000;                       //定义延时时间变量
  while(DelayTime--);                                 //开始进行延时循环
  return;                                             //子程序返回
}

void ControlCar_yaokong(unsigned char ConType)    //定义电机控制子程序	(红外遥控单独设置一个 switch  case  语句  )
{
 
  stop();
 switch(ConType)                          //判断用户设定电机形式
 {
  case 1:  //前进                         //判断用户是否选择形式1
  { 
    stop();						      //进入前进之前 先停止一段时间  防止电机反向电压冲击主板 导致系统复位
	Delay1ms(150);
//	LeftLed = 0 ;
	run();
    break;
  }
  case 2: //后退                          //判断用户是否选择形式2
  { 
    stop();								      //进入后退之前 先停止一段时间  防止电机反向电压冲击主板 导致系统复位
    Delay1ms(150);
  //  LeftLed = 1 ; 	 
	back();                                 //M2电机反转
    break;
  }
  case 3: //右转                          //判断用户是否选择形式3
  { 
     stop();								  //进入左转之前 先停止一段时间  防止电机反向电压冲击主板 导致系统复位
	 Delay1ms(150); 
	 rightrun();                                //M2电机正转
	 break;
  }
  case 4: //左转                          //判断用户是否选择形式4
  { 
     stop();								  //进入右转之前 先停止一段时间  防止电机反向电压冲击主板 导致系统复位
	 Delay1ms(150);
     leftrun();                                  //M1电机正转  //M2电机反转
 	 break;
  }
  case 8: //停止                          //判断用户是否选择形式8
  {
    stop();
	break;                                //退出当前选择
  }
 }
}
void Robot_Avoidance()                   //机器人避障子程序
{
  	  
	      if(LeftIRBZ==1&&RightIRBZ ==1)	  //LeftIRBZ RightIRBZ 

		    {	 
		      run();
              delay_nms (10);
			   SB1=1;
			  }
			  else
			 {			  
				      if(LeftIRBZ==1&&RightIRBZ ==0)	    //右边检测到红外信号
			 	 {
				 	 rightrun();                            //右转
                     delay_nms (300);					   //停止300MS   防止电机反相电压冲击  导致系统复位

			     }
			   
				 	  if(RightIRBZ ==1&&LeftIRBZ==0)		//左边检测到红外信号
				  {	  
				      
					  leftrun();                        //左转
                     delay_nms (300);					   //停止300MS   防止电机反相电压冲击  导致系统复位

				  }
				  if(RightIRBZ==0&&LeftIRBZ==0)		//两边传感器同时检测到红外
				  {	  
				     SB1=0;
					 stop();                     //停止
                     delay_nms (300);			//停止300MS   防止电机反相电压冲击  导致系统复位
					 back(); 		        //调用电机后退函数
					 delay_nms (300);		//后退50毫秒
					 rightrun();  		   //调用电机右转函数
					delay_nms (400);
				  }
			}
	
			run();
		  
}
//机器人循迹子程序
void Robot_Traction()                     //机器人循迹子程序
{
  
   //SB1=1;
   if(Left_1_led  == 0 && Right_1_led == 0)    //三个红外检测到黑线，就前进	 Left_1_led 	  Right_1_led
   {
      run();                     //左侧没有信号时，开始向右转一定的角度
      delay_nms (10);
	  SB1=0;
   }
   
   else if(Left_1_led  == 0 && Right_1_led == 1)
   {
      rightrun();                       //右侧检测到黑线,开始向右转一定的角度
      delay_nms (10);
   }

   else if(Left_1_led  == 1 &&  Right_1_led == 0)
   {
      leftrun();                         //左侧检测到黑线,开始向左转一定的角度
	  
      delay_nms (10);
   }
   else if(Left_1_led  == 1 &&  Right_1_led == 1)
   {
      SB1=1;
	  stop();                         //左侧检测到黑线,开始向左转一定的角度
	  
      delay_nms (10);
   }
     
}

//----------红外遥控-------------------------------------------------------------
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
       // ControlCar(j);
		ControlCar_yaokong(j);                               //数码管显示相应数码
      }
   } 
   EX1 = 1;                                           //外部中断开 
} 
//------------------------------------------------------------------------------------------------------- 
void main()                               //主程序入口
{
  TMOD=0X01;
  TH0= 0XFc;		  //1ms定时
  TL0= 0X18;
  TR0= 1;
  ET0= 1;
  EA = 1;			   //开总中断
  //EX1=1;                                               //同意开启外部中断1
  IT1=1;                                               //设定外部中断1为低边缘触发类型

  while(1)                                //程序主循环
  {
	  if(P3_2 == 0)
	  {
	   delay_nms(10);
	   if(P3_2 == 0)
	   {
	   	  temp++;
		  while(!P3_2);
	   }
	  }
	  if(temp > 3)
	  {
	  temp = 1;
	  }
	  switch(temp)
	  {
	   	case 1:	ShowPort = LedShowData[1];Robot_Traction();EX1 = 0;break;
		case 2: ShowPort = LedShowData[2];Robot_Avoidance();EX1 = 0;break;
		case 3: ShowPort = LedShowData[3];SB1 = 1; EX1 = 1;break;
	  }

	  
  }
}
