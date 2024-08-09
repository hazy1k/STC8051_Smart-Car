/**********************ZYWIFI0939C-WIFI机器人实验板例程************************
*  平台：ZYWIFI0939C-WIFI机器人 + Keil U4 + STC89C52
*  名称：ZY-1智能小车参考程序
*  公司：湖南智宇科教设备有限公司
*  淘宝：https://hnzyrobot1688.taobao.com/     
*  网站：www.hnzhiyu.cn	
*  编写：智宇公司研发一部
*  日期：2015-1-15
*  交流:智能车QQ:261339276
*  晶振:11.0592MHZ
*  说明：免费开源，不提供源代码分析
*  硬件设置：要有自己动手能力，才能完成实验
*  使用说明：根据下面IO口自己用杜邦线连接各种模块，可以自己修改各种模块IO口
*  视频教程：本小车配套学习C语言详细视频教程，资料统一网盘下载
   重点提示：本程序只做参考，不提供技术支持，请自己研究吸收。
  ZYWIFI0939WIFI控制智能机器人杜邦线接线方法，请一定照做，否则可能不工作，并烧毁小车。
  J3 接到实验板 P4		                           J4 接实验板 P7接口 
   IN1--接到--实验板上的P1.2	               IN5--接到--实验板上的P2.1
   IN2--接到--实验板上的P1.3	               IN6--接到--实验板上的P2.0
   EN1--接到--实验板上的P1.4
   EN2--接到--实验板上的P1.5
   IN3--接到--实验板上的P1.6
   IN4--接到--实验板上的P1.7
   
   J5 接实验班P3接口
   OUT1--接到--实验板上的P3.2	                  OUT3--接到--实验板上的P3.4
   OUT2--接到--实验板上的P3.3					  OUT4--接到--实验板上的P3.5
   VCC-- 接到--实验班上的VCC					  GND--接到--实验板上的GND
    
******************************************************************/
#ifndef _LED_H_
#define _LED_H_


    //定义小车驱动模块输入IO口 
   sbit L293D_IN1=P1^2; 
   sbit L293D_IN2=P1^3;
   sbit L293D_IN3=P1^4;
   sbit L293D_IN4=P1^5;
   sbit L293D_EN1=P1^6;
   sbit L293D_EN2=P1^7;
	

	/***蜂鸣器接线定义*****/
    sbit BUZZ=P2^3;
 
    #define Left_1_led        P3_7	 //左传感器  
	
    #define Right_1_led       P3_6	 //右传感器    
   
	#define Left_moto_pwm	  P1_6	 //PWM信号端

	#define Right_moto_pwm	  P1_7	 //PWM信号端
	
	#define Left_moto_go      {P1_2=1,P1_3=0;}  //左电机向前走
	#define Left_moto_back    {P1_2=0,P1_3=1;} 	//左边电机向后转
	#define Left_moto_Stop    {P1_2=0,P1_3=0;}         //左边电机停转                     
	#define Right_moto_go     {P1_4=1,P1_5=0;}	//右边电机向前走
	#define Right_moto_back   {P1_4=0,P1_5=1;}	//右边电机向后走
	#define Right_moto_Stop   {P1_4=0,P1_5=0;}      	//右边电机停转   

	unsigned char pwm_val_left  =0;//变量定义
	unsigned char push_val_left =0;// 左电机占空比N/20
	unsigned char pwm_val_right =0;
	unsigned char push_val_right=0;// 右电机占空比N/20
	bit Right_moto_stop=1;
	bit Left_moto_stop =1;
	unsigned  int  time=0;
   
/************************************************************************/	
//延时函数	
   void delay(unsigned int k)
{    
     unsigned int x,y;
	 for(x=0;x<k;x++) 
	   for(y=0;y<2000;y++);
}
/************************************************************************/
//前速前进
     void  run(void)
{
     push_val_left=12;	 //速度调节变量 0-20。。。0最小，20最大
	 push_val_right=12;
	 Left_moto_go ;   //左电机往前走
	 Right_moto_go ;  //右电机往前走
}

//后退函数 
     void  backrun(void)
{
     push_val_left=12;	 //速度调节变量 0-20。。。0最小，20最大
	 push_val_right=12;
	 Left_moto_back;   //左电机往后走
	 Right_moto_back;  //右电机往后走
}

//左转
     void  leftrun(void)
{	 
     push_val_left=5;
	 push_val_right=15;
	 Right_moto_go ;  //右电机往前走
     Left_moto_back   ;  //左电机后走
}

//右转
     void  rightrun(void)
{ 
	 push_val_left=16;
	 push_val_right=8;
     Left_moto_go  ;   //左电机往前走
	 Right_moto_back    ;  //右电机往后走	
}

//停止
     void  stop(void)
{	 
     
	 Right_moto_Stop ;  //右电机停止
     Left_moto_Stop  ;  //左电机停止
}

/************************************************************************/
/*                    PWM调制电机转速                                   */
/************************************************************************/
/*                    左电机调速                                        */
/*调节push_val_left的值改变电机转速,占空比            */
		void pwm_out_left_moto(void)
{  
   if(Left_moto_stop)
   {
    if(pwm_val_left<=push_val_left)
	       {
		     Left_moto_pwm=1; 
//		     Left_moto_pwm1=1; 
		   }
	else 
	       {
	         Left_moto_pwm=0;
//		     Left_moto_pwm1=0; 
		   }
	if(pwm_val_left>=20)
	       pwm_val_left=0;
   }
   else    
          {
           Left_moto_pwm=0;
//           Left_moto_pwm1=0; 
		  }
}
/******************************************************************/
/*                    右电机调速                                  */  
   void pwm_out_right_moto(void)
{ 
  if(Right_moto_stop)
   { 
    if(pwm_val_right<=push_val_right)
	      {
	       Right_moto_pwm=1; 
//		   Right_moto_pwm1=1; 
		   }
	else 
	      {
		   Right_moto_pwm=0;
//		   Right_moto_pwm1=0; 
		  }
	if(pwm_val_right>=20)
	       pwm_val_right=0;
   }
   else    
          {
           Right_moto_pwm=0;
//           Right_moto_pwm1=0; 
	      }
}
       
/***************************************************/
///*TIMER0中断服务子函数产生PWM信号*/
 	void timer0()interrupt 1   using 2
{
     TH0=0XFc;	  //1Ms定时
	 TL0=0X18;
	 time++;
	 pwm_val_left++;
	 pwm_val_right++;
	 pwm_out_left_moto();
	 pwm_out_right_moto();
 }	

/*********************************************************************/	

#endif