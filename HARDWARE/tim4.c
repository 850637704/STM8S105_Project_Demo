
#include "tim4.h"

void Tim4_Init(void)
{
  TIM4_TimeBaseInit(TIM4_PRESCALER_32, 249);									//64·ÖÆµ£¨0.25MHz£©¡¢250´Î£¨1ms£©¡¢
  TIM4_ARRPreloadConfig(ENABLE);
  TIM4_ITConfig(TIM4_IT_UPDATE , ENABLE);
  TIM4_Cmd(ENABLE);
}
/*--------------Write-by-xiao-kai-2017-09-12-13-53----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/