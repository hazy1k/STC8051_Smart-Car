#include<AT89X52.H>		  //����51��Ƭ��ͷ�ļ����ڲ��и��ּĴ�������
#include<ZY-4WD_PWM.H>		  //����HL-1��������С������IO�ڶ���Ⱥ���
    
//������
	void main(void)
{	

	unsigned char i;
    P1=0X00;   //�ص��	

		 	TMOD=0X01;
        	TH0= 0XFc;		  //1ms��ʱ
         	TL0= 0X18;
           	TR0= 1;
        	ET0= 1;
	        EA = 1;			   //�����ж�


	while(1)	//����ѭ��
	{ 
	 
			 //���ź�Ϊ0  û���ź�Ϊ1

              if(Left_1_led==0&&Right_1_led==0)

			  run();   //����ǰ������

			  else
			 {			  
				               if(Left_1_led==1&&Right_1_led==0)	    //��߼�⵽����
			 	 {
				 	  leftrun();		  //����С����ת  ����

			     }
			   
				 			    if(Right_1_led==1&&Left_1_led==0)		//�ұ߼�⵽����
				  {	  
				      rightrun();		   //����С����ת	����

				  }
						    if(Right_1_led==1&&Left_1_led==1)		//����״̬  ������
				  {	  
				      stop();		   //����С��ֹͣ

				  }

			}	 
	 }
}