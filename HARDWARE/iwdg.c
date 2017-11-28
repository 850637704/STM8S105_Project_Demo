
#include "iwdg.h"

void Iwdg_Init(void)
{
  	CLK_LSICmd(ENABLE);
	IWDG_Enable();																// 启动IWDG
  	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);								// 允许写
	IWDG_SetReload(0xff);														// 设置IWDG计数器重载值	
	IWDG_SetPrescaler(IWDG_Prescaler_128);										// 设置分频系数128KHz/128
	IWDG_ReloadCounter();
}

void FeedDog(void)
{
	IWDG_ReloadCounter();														// 重载IWDG计数器
}
/*--------------Write-by-xiao-kai-2017-07-15-15-37----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/
