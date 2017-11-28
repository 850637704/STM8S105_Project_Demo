
#include "delay.h"
//使用内部8M晶振
//--- 微秒级延时---------------------------  
void delay_us(unsigned int i)   
{      
	for(;i>0;i--)
		asm("nop");
}
  
//--- 毫秒级延时---------------------------
void delay_ms(unsigned int time)
{   
	unsigned int i;   
	while(time--)     
		for(i=999;i>0;i--)
			asm("nop");
}  
/*--------------Write-by-xiao-kai-2017-09-22-15-14----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/
