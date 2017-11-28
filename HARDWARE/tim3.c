
#include "tim3.h"

void Tim3_Init(void)
{
	TIM3_TimeBaseInit(TIM3_PRESCALER_8, 19999);									//8·ÖÆµ£¨2MHz£©¡¢125´Î£¨62.5us£©
	TIM3_ARRPreloadConfig(ENABLE);
	TIM3_ITConfig(TIM3_IT_UPDATE , ENABLE);
	TIM3_Cmd(ENABLE);
}