
#include "clock.h"

void Clk_Init(void)
{
	CLK_DeInit();																// 恢复到默认值
	CLK_HSICmd(ENABLE);															// 开启内部高速时钟：16M
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV2);								// 内部时钟一分频
	
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);						// 关闭I2C时钟
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);						// 关闭SPI时钟
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);						// 关闭AWU时钟
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_CAN, DISABLE);						// 关闭CAN时钟
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, DISABLE);					// 关闭UART1时钟
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE);					// 关闭TIMER1时钟
	//CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);					// 关闭TIMER2时钟
}

//void Clk_Init(CLK_Source_TypeDef clk_source)
//{
//  	if( CLK_SOURCE_HSI == clk_source)											// 外部高速时钟
//	{
//		CLK_DeInit();															// 恢复到默认值
//		CLK_HSICmd(ENABLE);														// 开启内部高速时钟：16M
//		CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);							// 内部时钟一分频
//	}
//	else if( CLK_SOURCE_HSE == clk_source)										// 内部高速时钟
//	{
//		CLK_HSECmd(ENABLE);                                   					// 外部时钟开  
//		CLK_LSICmd(ENABLE);                                   					// 内部低频RC开  
//		CLK_HSICmd(ENABLE);                                   					// 内部高频RC开 
//		while(SET != CLK_GetFlagStatus(CLK_FLAG_HSERDY));     					// 等待外部晶振起振  
//		CLK_ClockSwitchCmd(ENABLE);                           					// 切换使能  
//		CLK_ClockSwitchConfig(CLK_SWITCHMODE_MANUAL,CLK_SOURCE_HSE,DISABLE,\
//		  										CLK_CURRENTCLOCKSTATE_DISABLE);	// 切换到外部晶振 
//		CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);              					// 1分频  
//	}
//}
/*--------------Write-by-xiao-kai-2017-05-17-12-08----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/