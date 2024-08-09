		   #include <AT89X51.H>
   void delay (void)
      {  
	  #pragma asm
	   mov r3,#5
dl2:   mov r4,#255
dl1:   mov r5,#255
	   djnz r5,$
	   djnz r4,dl1
	   djnz r3,dl2
	  #pragma endasm 
	   }
   void main (void)
       {  unsigned char j=0x7f;
	       while(1)
		   {j=(j>>1)|0x80;
		   if(j==0xff)
		   j=0x7f;
		   P1=j;
		   delay();
		   }
        }
