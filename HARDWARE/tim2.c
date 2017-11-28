
#include "tim2.h"

volatile uint32_t TimingDelay; 

void Tim2_Init(void)
{
 	TIM2_TimeBaseInit(TIM2_PRESCALER_8, 9999);									// 16·ÖÆµ£¨1MHz£©¡¢1000´Î£¨1ms£©¡¢
	TIM2_ARRPreloadConfig(ENABLE);
	TIM2_ITConfig(TIM2_IT_UPDATE , ENABLE);
	TIM2_Cmd(ENABLE);
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}

void Delay_ms(uint32_t nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);
}
/*--------------Write-by-xiao-kai-2017-09-15-15-37----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/