
#ifndef _LED_H_
#define _LED_H_


    //����С������ģ������IO�� 
	sbit IN1=P1^2;
	sbit IN2=P1^3;
	sbit IN3=P1^4;
	sbit IN4=P1^5;
	sbit EN1=P1^6;
	sbit EN2=P1^7;
	

	/***���������߶���*****/
    sbit BUZZ=P2^3;

    //#define Left_1_led        P3_3	 // �󴫸���       
	//#define Right_1_led       P3_2	 //�Ҵ�����    
   	 
	#define Left_moto_pwm	  P1_6	 //PWM�źŶ�
	#define Right_moto_pwm	  P1_7	  //PWM�źŶ�


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
	unsigned  int  time3=0;
   
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
//ǰ�ٺ���
     void  back(void)//����
{
     push_val_left=13;	 //�ٶȵ��ڱ��� 0-20������0��С��20���
	 push_val_right=13;
	 Left_moto_back ;   //������ǰ��
	 Right_moto_back ;  //�ҵ����ǰ��
} 


//��ת
     void  leftrun(void)
{	 
     push_val_left=6;
	 push_val_right=14;
	 Right_moto_go ;  //�ҵ����ǰ��
     Left_moto_back   ;  //��������
}

//��ת
     void  rightrun(void)
{ 
	 push_val_left=14;
	 push_val_right=6;
     Left_moto_go  ;   //������ǰ��
	 Right_moto_back    ;  //�ҵ��������	
}
//ֹͣ
     void  stop(void)
{ 
	 P1_2 = 0;
	 P1_3 = 0;
	 P1_4 = 0;
	 P1_5 = 0;
	 	
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

		   }
	else 
	       {
	         Left_moto_pwm=0;

		   }
	if(pwm_val_left>=20)
	       pwm_val_left=0;
   }
   else    
          {
           Left_moto_pwm=0;

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

		   }
	else 
	      {
		   Right_moto_pwm=0;

		  }
	if(pwm_val_right>=20)
	       pwm_val_right=0;
   }
   else    
          {
           Right_moto_pwm=0;

	      }
}
       
/***************************************************/
///*TIMER0�жϷ����Ӻ�������PWM�ź�*/
 	void timer0()interrupt 1   using 2
{
     TH0=0XFc;	  //1Ms��ʱ
	 TL0=0X18;
	 time3++;
	 pwm_val_left++;
	 pwm_val_right++;
	 pwm_out_left_moto();
	 pwm_out_right_moto();
 }	

/*********************************************************************/	

#endif