#include<AT89X52.H>		// 包含51单片机头文件，内部有各种寄存器定义
#include<ZY-4WD_PWM.H>  // 包含HL-1蓝牙智能小车驱动IO口定义等函数
    
void main(void)
{	
unsigned char i;
P1 = 0X00; // 关电车电机	

B:for(i = 0; i < 50; i++) // 判断K4是否按下
	{
		delay(1);	  // 1ms内判断50次，如果其中有一次被判断到K0没按下，便重新检测
		if(P3_2 != 0) // 当S1按下时，启动小车前进
		   goto B;    // 跳转到标号B，重新检测  
	} 
	BUZZ = 0; // 50次检测K0确认是按下之后，蜂鸣器发出“滴”声响，然后启动小车。
	delay(50);
	BUZZ = 1; //响50ms后关闭蜂鸣器

// 定时器中断配置
	TMOD = 0X01;
    TH0 = 0XFc; //1ms定时
    TL0 = 0X18;
    TR0 = 1;
    ET0 = 1;
	EA = 1;		// 开总中断
while(1)
{ 
	//有信号为0  没有信号为1
	if(Left_1_led == 1 && Right_1_led == 1)
		stop();	// 调用停止函数	  前面没有光线
	else
	{			  
		if(Left_1_led == 1 && Right_1_led == 0)	// 右边检测到红外信号
		{
			rightrun();	// 调用小车右转函数
			delay(20);
		}
		if(Right_1_led == 1 && Left_1_led == 0)	// 左边检测到红外信号
		{	  
				      
			leftrun(); // 调用小车左转函数
			delay(20);
		}
		if(Right_1_led == 0 && Left_1_led == 0)	// 两边传感器同时检测到红外
		{	  
			run();		// 调用前进函数
			delay(20);  // 前进40毫秒
		}
	}	 
}
}