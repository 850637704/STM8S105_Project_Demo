
#include "clock.h"

void Clk_Init(void)
{
	CLK_DeInit();																// �ָ���Ĭ��ֵ
	CLK_HSICmd(ENABLE);															// �����ڲ�����ʱ�ӣ�16M
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV2);								// �ڲ�ʱ��һ��Ƶ
	
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);						// �ر�I2Cʱ��
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);						// �ر�SPIʱ��
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);						// �ر�AWUʱ��
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_CAN, DISABLE);						// �ر�CANʱ��
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, DISABLE);					// �ر�UART1ʱ��
//	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE);					// �ر�TIMER1ʱ��
	//CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);					// �ر�TIMER2ʱ��
}

//void Clk_Init(CLK_Source_TypeDef clk_source)
//{
//  	if( CLK_SOURCE_HSI == clk_source)											// �ⲿ����ʱ��
//	{
//		CLK_DeInit();															// �ָ���Ĭ��ֵ
//		CLK_HSICmd(ENABLE);														// �����ڲ�����ʱ�ӣ�16M
//		CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);							// �ڲ�ʱ��һ��Ƶ
//	}
//	else if( CLK_SOURCE_HSE == clk_source)										// �ڲ�����ʱ��
//	{
//		CLK_HSECmd(ENABLE);                                   					// �ⲿʱ�ӿ�  
//		CLK_LSICmd(ENABLE);                                   					// �ڲ���ƵRC��  
//		CLK_HSICmd(ENABLE);                                   					// �ڲ���ƵRC�� 
//		while(SET != CLK_GetFlagStatus(CLK_FLAG_HSERDY));     					// �ȴ��ⲿ��������  
//		CLK_ClockSwitchCmd(ENABLE);                           					// �л�ʹ��  
//		CLK_ClockSwitchConfig(CLK_SWITCHMODE_MANUAL,CLK_SOURCE_HSE,DISABLE,\
//		  										CLK_CURRENTCLOCKSTATE_DISABLE);	// �л����ⲿ���� 
//		CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);              					// 1��Ƶ  
//	}
//}
/*--------------Write-by-xiao-kai-2017-05-17-12-08----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/