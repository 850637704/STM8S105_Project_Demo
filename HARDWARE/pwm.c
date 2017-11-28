
#include "pwm.h"

static void Pwm_Gpio_Init(void) 
{
	GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)(GPIO_PIN_2), GPIO_MODE_OUT_OD_HIZ_FAST);//　PWM　正端
	GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)(GPIO_PIN_3), GPIO_MODE_OUT_OD_HIZ_FAST);//　PWM　反端
}

void Pwm_Init(void)
{
	TIM1_DeInit();
	Pwm_Gpio_Init();
	//周期 200 us
	TIM1_TimeBaseInit(2, TIM1_COUNTERMODE_UP, 255, 0);							//　2分频（8MHz）、256次（32us）
	//PC2 通道 2
	TIM1_OC2Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
				 0x0000, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_LOW, 
				 TIM1_OCIDLESTATE_RESET, TIM1_OCNIDLESTATE_SET);
	//PC3 通道 3
	TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
				 0x0000, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_LOW, 
				 TIM1_OCIDLESTATE_RESET, TIM1_OCNIDLESTATE_SET);
	TIM1_CtrlPWMOutputs(ENABLE);
	TIM1_Cmd(ENABLE);
}

/*--------------Write-by-xiao-kai\2017\06\06\11\06----QQ-850637704------------*/
/*-------------------------Always have a nice day-----------------------------*/

