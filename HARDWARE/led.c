
#include "led.h"

void Led_Init(void)
{
  	GPIO_Init(LED_PORT, (GPIO_Pin_TypeDef)(Gam_Com_Led1|Gam_Com_Led2|\
	  Gam_Com_Led3|Gam_Com_Led4|Gam_Com_Led5|Gam_Com_Led6|Gam_Com_Led7),\
													 GPIO_MODE_OUT_OD_HIZ_SLOW);
}

