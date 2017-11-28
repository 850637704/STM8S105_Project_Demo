
#include "iwdg.h"

void Iwdg_Init(void)
{
  	CLK_LSICmd(ENABLE);
	IWDG_Enable();																// ����IWDG
  	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);								// ����д
	IWDG_SetReload(0xff);														// ����IWDG����������ֵ	
	IWDG_SetPrescaler(IWDG_Prescaler_128);										// ���÷�Ƶϵ��128KHz/128
	IWDG_ReloadCounter();
}

void FeedDog(void)
{
	IWDG_ReloadCounter();														// ����IWDG������
}
/*--------------Write-by-xiao-kai-2017-07-15-15-37----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/
