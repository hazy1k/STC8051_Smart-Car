//注意程序只做参考之用，要达到最理想的效果，还需要同学们细心调试。	
#include<AT89X52.H>		      //包含51单片机头文件，内部有各种寄存器定义
#include<ZY-4WD_PWM.H>		  //包含HL-1蓝牙智能小车驱动IO口定义等函数
    unsigned char temp = 1;
//主函数
void delay_nus(unsigned int i)  //延时:i>=12 ,i的最小延时单12 us
{ 
  i=i/10;
  while(--i);
} 
	void main(void)
{	
//	unsigned char i;
    P1=0X00; //关电车电机	
	    
		 	TMOD=0X01;
        	TH0= 0XFc;		  //1ms定时
         	TL0= 0X18;
           	TR0= 1;
        	ET0= 1;
	        EA = 1;		     //开总中断
	while(1)	//无限循环
	{ 
	   			
	 if(P2_7 == 0)
	  {
	   delay_nus(10);
	   if(P2_7 == 0)
	   {
		 
		  	  	      if(Left_1_led==1&&Right_1_led==1)	    //右边检测到红外信号
			 	 {
				 	   run();	  //调用小车前进函数
					   delay(40);

			     }
				      if(Left_1_led==1&&Right_1_led==0)	    //右边检测到红外信号
			 	 {
				 	   leftrun();	  //调用小车左转函数
					   delay(40);

			     }
			   
				 	  if(Right_1_led==1&&Left_1_led==0)		//左边检测到红外信号
				  {	  
				      
					 
					   rightrun();	 //调用小车右转函数
					  delay(40);

				  }
				  	  if(Right_1_led==0&&Left_1_led==0)		//两边传感器同时检测到红外
				  {	  
				    backrun();		//调用电机后退函数
					delay(40);		//后退050毫秒
					rightrun();		//调用电机右转函数
					delay(90);
				  }
	// delay(70);

	   }
	  }

	  else
      stop();

 
	 }
}