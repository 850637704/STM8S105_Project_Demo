
#include "beep.h"
#include "tim2.h"
#include "tim4.h"

void Beep_Init(void)
{
	GPIO_Init(GPIOD, GPIO_PIN_4,GPIO_MODE_OUT_PP_HIGH_FAST);//BEEP -> PD4
}