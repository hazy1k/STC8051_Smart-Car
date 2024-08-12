#include<AT89X52.H>		  //包含51单片机头文件，内部有各种寄存器定义
#include<ZY-4WD_PWM.H>		  //包含HL-1蓝牙智能小车驱动IO口定义等函数
    
//主函数
	void main(void)
{	

	unsigned char i;
    P1=0X00;   //关电机	

		 	TMOD=0X01;
        	TH0= 0XFc;		  //1ms定时
         	TL0= 0X18;
           	TR0= 1;
        	ET0= 1;
	        EA = 1;			   //开总中断


	while(1)	//无限循环
	{ 
	 
			 //有信号为0  没有信号为1

              if(Left_1_led==0&&Right_1_led==0)

			  run();   //调用前进函数

			  else
			 {			  
				               if(Left_1_led==1&&Right_1_led==0)	    //左边检测到黑线
			 	 {
				 	  leftrun();		  //调用小车左转  函数

			     }
			   
				 			    if(Right_1_led==1&&Left_1_led==0)		//右边检测到黑线
				  {	  
				      rightrun();		   //调用小车右转	函数

				  }
						    if(Right_1_led==1&&Left_1_led==1)		//悬空状态  避悬崖
				  {	  
				      stop();		   //调用小车停止

				  }

			}	 
	 }
}