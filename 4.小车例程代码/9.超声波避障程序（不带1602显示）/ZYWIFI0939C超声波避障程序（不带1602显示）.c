#include <at89x51.h>	
#include <intrins.h>

#define  TX  P2_1
#define  RX  P2_0

#define Forward_L_DATA  180//当前进不能走直线的时候，请调节这两个参数，理想的时候是100,100，最大256，最小0。0的时候最慢，256的时候最快
#define Forward_R_DATA  180	//例如小车前进的时候有点向左拐，说明右边马达转速过快，那可以取一个值大一点，另外一个值小一点，例如 200  190
                            //直流电机因为制造上的误差，同一个脉宽下也不一定速度一致的，需要自己手动调节


/*****按照原图接线定义******/
sbit L293D_IN1=P1^2; 
sbit L293D_IN2=P1^3;
sbit L293D_IN3=P1^4;
sbit L293D_IN4=P1^5;
sbit L293D_EN1=P1^6;
sbit L293D_EN2=P1^7;

sbit BUZZ=P2^3;


void Delay400Ms(void);//延时400毫秒函数


unsigned char disbuff[4]={0,0,0,0};//用于分别存放距离的值0.1mm、mm、cm和m的值

void Count(void);//距离计算函数
			  
unsigned int  time=0;//用于存放定时器时间值
unsigned long S=0;//用于存放距离的值
bit  flag =0; //量程溢出标志位
bit  turn_right_flag;


//********************************************************** 
//函数名称:Delay1ms(unsigned int i) 
//函数功能:延时i*1ms的子程序(对应于22.1184Mhz晶振)   
//形式参数:unsigned int i 
//行参说明:无 
//返回参数:无 
//使用说明:i为要延时的时间长度，单位是MS，最大可以延时65536 ms 
//********************************************************** 
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
//********************************************************** 
//函数名称:Delay10us(unsigned char i) 
//函数功能:延时i*10us的子程序(对应于22.1184Mhz晶振)   
//形式参数:无 
//行参说明:无 
//返回参数:无 
//使用说明:i为要延时的时间长度，单位是US，最大可以延时250 ms 
//********************************************************** 
void Delay10us(unsigned char i) 
{ 
   unsigned char j; 
do{ 
  j = 10; 
  do{ 
   _nop_(); 
   }while(--j); 
}while(--i); 
}  

//=========================================================================================================================
void Forward()//	   前进
{

	 L293D_IN1=1; 
	 L293D_IN2=0;
	 L293D_IN3=1;
	 L293D_IN4=0;
//     PWM_Set(255-Speed_Right,255-Speed_Left);
}
void  backrun()//	   后退
{

	 L293D_IN1=0; 
	 L293D_IN2=1;
	 L293D_IN3=0;
	 L293D_IN4=1;
//     PWM_Set(255-Speed_Right,255-Speed_Left);
}
void Stop(void)	//刹车
{

     L293D_IN1=0; 
	 L293D_IN2=0;
	 L293D_IN3=0;
	 L293D_IN4=0;
//	 PWM_Set(0,0);
}
void Turn_Retreat()	 //左
{
    L293D_IN1=0; 
	L293D_IN2=0;
	L293D_IN3=0;
	L293D_IN4=1;
//	PWM_Set(255-Speed_Right,255-Speed_Left);
}

void Turn_left()	 //右
{
    L293D_IN1=1; 
	L293D_IN2=0;
	L293D_IN3=0;
	L293D_IN4=0;
//	PWM_Set(255-Speed_Right,255-Speed_Left);
}

//=========================================================================================================================
/********距离计算程序***************/
    void Conut(void)
	{
	 time=TH1*256+TL1;
	 TH1=0;
	 TL1=0;
	
	 //此时time的时间单位决定于晶振的速度，外接晶振为11.0592MHZ时，
	            //time的值为0.54us*time，单位为微秒
				//那么1us声波能走多远的距离呢？1s=1000ms=1000000us 
				// 340/1000000=0.00034米
				//0.00034米/1000=0.34毫米  也就是1us能走0.34毫米
				//但是，我们现在计算的是从超声波发射到反射接收的双路程，
				//所以我们将计算的结果除以2才是实际的路程

	S=time*2;//先算出一共的时间是多少微秒。
   	S=S*0.17;//此时计算到的结果为毫米，并且是精确到毫米的后两位了，有两个小数点 
	 if(S<=400)	 //
	 {	
	    if(turn_right_flag!=1)
		{
		    Stop();
		    Delay1ms(5);//发现小车自动复位的时候，可以稍微延长一点这个延时，减少电机反向电压对电路板的冲击。
		}
		turn_right_flag=1;
		
		P2_3=0;

		Delay1ms(50);
		
		P2_3=1;
	    backrun();
	   Delay1ms(300); 	// 关键点  延时5MS  
	   Turn_left();
	   Delay1ms(400); 	  //左转800MS

	 }
	 else
	 {
	    turn_right_flag=0;
	    //Forward(Forward_R_DATA,Forward_L_DATA);
		Forward();

	 }
	 //=======================================
	 if((S>=5000)||flag==1) //超出测量范围
	 {	
	  flag=0;
      //DisplayListChar(0, 1, table1);
	 }
	 else
	 {
      disbuff[0]=S%10;
	  disbuff[1]=S/10%10;
	  disbuff[2]=S/100%10;
	  disbuff[3]=S/1000;
	 }
	}

/********************************************************/
     void zd0() interrupt 3 		 //T0中断用来计数器溢出,超过测距范围
  {
    flag=1;			 //中断溢出标志
	RX=0;
  }

/********超声波高电平脉冲宽度计算程序***************/
void Timer_Count(void)
{
		 TR1=1;			    //开启计数
	     while(RX);			//当RX为1计数并等待
	     TR1=0;				//关闭计数
         Conut();			//计算

}
/********************************************************/
   void  StartModule() 		         //启动模块
  {
	  TX=1;			                     //启动一次模块
      Delay10us(2);
	  TX=0;
  }
/********************************************************/ 

/*************主程序********************/
void main(void)
{
    unsigned char i;
	unsigned int a;
	Delay1ms(5);//延时片刻
    TMOD=TMOD|0x10;//设T0为方式1，GATE=1；
    EA=1;
    TH1=0;
    TL1=0;          
    ET1=1;             //允许T0中断
				   //开启总中断

	turn_right_flag=0;
	//=================================
B:		for(i=0;i<50;i++) //判断K3是否按下
		{
		   Delay1ms(1);	//1ms内判断50次，如果其中有一次被判断到K3没按下，便重新检测
		   if(P3_2!=0 )//当S1按下时，启动小车
		   goto B; //跳转到标号B，重新检测
		}
	//蜂鸣器响一声
	BUZZ=0;	//50次检测K3确认是按下之后，蜂鸣器发出“滴”声响，然后启动小车。
	Delay1ms(50);
	BUZZ=1;//响50ms后关闭蜂鸣器
	//=======================================================================================================================			
 	while(1)
	  {
		RX=1;
	    StartModule();
        for(a=951;a>0;a--)
	    {
		   
	       if(RX==1)
		   {
           Timer_Count();
		   }
    	 }
   	}
} 



                