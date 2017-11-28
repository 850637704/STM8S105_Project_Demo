
#ifndef __LED_H_
#define __LED_H_

#include "stm8s_gpio.h"		

#define LED_PORT		GPIOB

#define Gam_Com_Led1	GPIO_PIN_1
#define Gam_Com_Led2	GPIO_PIN_2
#define Gam_Com_Led3	GPIO_PIN_3
#define Gam_Com_Led4	GPIO_PIN_4
#define Gam_Com_Led5	GPIO_PIN_5
#define Gam_Com_Led6	GPIO_PIN_6
#define Gam_Com_Led7	GPIO_PIN_7

void Led_Init(void);

#endif /* __LED_H_ */