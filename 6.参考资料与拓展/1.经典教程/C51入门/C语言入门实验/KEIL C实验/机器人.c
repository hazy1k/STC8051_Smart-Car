   #include <AT89X51.H>
   #include <STDIO.H>
   #include <math.h>
void  main(void)
  {
	unsigned char i;
    float x,y, z;
    SCON=0x50;
    TMOD=0x20;
    TH1=0xFD;
    TL1=0xFD;
    TI=1;
    TR1=1;

 
			   
 while(1)
    {  
	//printf("��ã����ǵ�Ƭ��STC89C516RC+���һ��������⣡\n");
	   printf("������������X��Y\n");
	   scanf("%f,%f",&x,&y);

	   for(i=0;i<255;i++)
	   {
	   z=512*sin(i*3.1415926/128)+512;	 
	   printf("z=%f\n",z);  
	   }
	   

    }
}



