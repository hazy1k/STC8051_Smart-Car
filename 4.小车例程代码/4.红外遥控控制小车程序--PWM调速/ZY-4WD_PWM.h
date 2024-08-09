/**********************ZYWIFI0939C-WIFI������ʵ�������************************
*  ƽ̨��ZYWIFI0939C-WIFI������ + Keil U4 + STC89C52
*  ���ƣ�ZY-1����С���ο�����
*  ��˾����������ƽ��豸���޹�˾
*  �Ա���https://hnzyrobot1688.taobao.com/     
*  ��վ��www.hnzhiyu.cn	
*  ��д�����˾�з�һ��
*  ���ڣ�2015-1-15
*  ����:���ܳ�QQ:261339276
*  ����:11.0592MHZ
*  ˵������ѿ�Դ�����ṩԴ�������
*  Ӳ�����ã�Ҫ���Լ������������������ʵ��
*  ʹ��˵������������IO���Լ��öŰ������Ӹ���ģ�飬�����Լ��޸ĸ���ģ��IO��
*  ��Ƶ�̳̣���С������ѧϰC������ϸ��Ƶ�̳̣�����ͳһ��������
   �ص���ʾ��������ֻ���ο������ṩ����֧�֣����Լ��о����ա�

******************************************************************/
#ifndef _LED_H_
#define _LED_H_


    //����С������ģ������IO�� 
   sbit L293D_IN1=P1^2; 
   sbit L293D_IN2=P1^3;
   sbit L293D_IN3=P1^4;
   sbit L293D_IN4=P1^5;
   sbit L293D_EN1=P1^6;
   sbit L293D_EN2=P1^7;
	

	/***���������߶���*****/
    sbit BUZZ=P2^3;

    #define Left_1_led        P3_5	 //�󴫸���  
	
    #define Right_1_led       P3_4	 //�Ҵ�����    
   
	#define Left_moto_pwm	  P1_6	 //PWM�źŶ�

	#define Right_moto_pwm	  P1_7	 //PWM�źŶ�
	
	#define Left_moto_go      {P1_2=1,P1_3=0;}  //������ǰ��
	#define Left_moto_back    {P1_2=0,P1_3=1;} 	//��ߵ�����ת
	#define Left_moto_Stop    {P1_2=0,P1_3=0;}         //��ߵ��ͣת                     
	#define Right_moto_go     {P1_4=1,P1_5=0;}	//�ұߵ����ǰ��
	#define Right_moto_back   {P1_4=0,P1_5=1;}	//�ұߵ�������
	#define Right_moto_Stop   {P1_4=0,P1_5=0;}      	//�ұߵ��ͣת   

	unsigned char pwm_val_left  =0;//��������
	unsigned char push_val_left =0;// ����ռ�ձ�N/20
	unsigned char pwm_val_right =0;
	unsigned char push_val_right=0;// �ҵ��ռ�ձ�N/20
	bit Right_moto_stop=1;
	bit Left_moto_stop =1;
	unsigned  int  time=0;
   
/************************************************************************/	
//��ʱ����	
   void delay(unsigned int k)
{    
     unsigned int x,y;
	 for(x=0;x<k;x++) 
	   for(y=0;y<2000;y++);
}
/************************************************************************/
//ǰ��ǰ��
     void  run(void)
{
     push_val_left=12;	 //�ٶȵ��ڱ��� 0-20������0��С��20���
	 push_val_right=12;
	 Left_moto_go ;   //������ǰ��
	 Right_moto_go ;  //�ҵ����ǰ��
}
   //ֹͣ����
     void  stop(void)
{
     
	 Left_moto_Stop ;   //������ǰ��
	 Right_moto_Stop ;  //�ҵ����ǰ��
}
//���˺��� 
     void  backrun(void)
{
     push_val_left=12;	 //�ٶȵ��ڱ��� 0-20������0��С��20���
	 push_val_right=12;
	 Left_moto_back;   //����������
	 Right_moto_back;  //�ҵ��������
}

//��ת
     void  leftrun(void)
{	 
     push_val_left=12;
	 push_val_right=12;
	 Left_moto_back  ;  //����������
     Right_moto_go  ;  //�ҵ����ǰ
}

//��ת
     void  rightrun(void)
{ 
	 push_val_left=12;
	 push_val_right=12;
     Right_moto_back  ;   //������ǰ��
	 Left_moto_go   ;  //�ҵ������	
}


/************************************************************************/
/*                    PWM���Ƶ��ת��                                   */
/************************************************************************/
/*                    ��������                                        */
/*����push_val_left��ֵ�ı���ת��,ռ�ձ�            */
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
/*                    �ҵ������                                  */  
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
///*TIMER0�жϷ����Ӻ�������PWM�ź�*/
 	void timer0()interrupt 1   using 2
{
     TH0=0XFc;	  //1Ms��ʱ
	 TL0=0X18;
	 time++;
	 pwm_val_left++;
	 pwm_val_right++;
	 pwm_out_left_moto();
	 pwm_out_right_moto();
 }	

/*********************************************************************/	

#endif