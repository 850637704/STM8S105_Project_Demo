
#include "exti.h"

#define key_state_0        0   //按键的初始状态
#define key_state_1        1   //按键按下的状态
#define key_state_2        2   //按键释放的状态

void Exti_Init(void)
{
	EXTI_DeInit();
	GPIO_Init(GPIOE,(GPIO_Pin_TypeDef)(GPIO_PIN_5),GPIO_MODE_IN_PU_NO_IT);
	EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE, EXTI_SENSITIVITY_FALL_ONLY);		// 上升沿触发
} 

//uint8_t Exit_Key_Scan(void)
//{
//	static uint8_t key_state = 0;     											// 按键的状态
//	static uint8_t key_count = 0;     											// 按键计数器
//	BitStatus key_press = RESET;       											// 按键是否被按下
//	uint8_t key_return = 0;  													// 按键返回值
//	
//	key_press = !(BitStatus)GPIO_ReadInputPin(GPIOE,GPIO_PIN_5);        		// 读按键I/O电?
//	
//	switch (key_state)
//	{
//		case key_state_0:                 										// 按键初始态
//			if (RESET!=key_press)
//			{
//				key_state = key_state_1;										// 键被按下，状态转换到键确认态
//			}
//		break;
//		case key_state_1:                   									// 按键确认态
//			if (RESET!=key_press)
//			{	
//				key_state = key_state_2;										// 状态转换到键释放态
//			}
//			else
//			{
//				key_state = key_state_0; 										// 按键已抬起，转换到按键初始态
//			}
//		break;
//		case key_state_2:
//			if (RESET==key_press) 												// 按键已释放，转换到按键初始态
//			{
//			  	if(key_count>50)												// 500ms长按键
//					key_return = 2; 
//				else
//				  	key_return = 1;
//				key_state = key_state_0;
//				key_count = 0;
//			}
//			else if(SET==key_press)												// 按键没有释放
//			{
//				key_count++;
//			}
//		break;
//	}
//	return key_return;
//}

/*--------------Write-by-xiao-kai\2017\05\06\17\14----QQ-850637704------------*/
/*-------------------------Always have a nice day-----------------------------*/