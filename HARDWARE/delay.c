
#include "delay.h"
//ʹ���ڲ�8M����
//--- ΢�뼶��ʱ---------------------------  
void delay_us(unsigned int i)   
{      
	for(;i>0;i--)
		asm("nop");
}
  
//--- ���뼶��ʱ---------------------------
void delay_ms(unsigned int time)
{   
	unsigned int i;   
	while(time--)     
		for(i=999;i>0;i--)
			asm("nop");
}  
/*--------------Write-by-xiao-kai-2017-09-22-15-14----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/
