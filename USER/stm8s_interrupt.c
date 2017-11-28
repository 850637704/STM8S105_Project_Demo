
#include "stm8s_interrupt.h"
#include "tim2.h"
#include "tim4.h"
#include "iwdg.h"
#include "key.h"
#include "flash.h"
#include "yx5p.h"
#include "ht1621.h"
#include <stdlib.h>

extern uint8_t Gam_Vol_Val; 
extern uint8_t Gam_Err_Val;	
extern uint8_t Gam_Sco_Val;
extern uint8_t Gam_Tim_Val;
extern uint8_t Gam_Mod_Val;
extern uint8_t Mod_Key_Val;														// 模式 键值
extern uint8_t Sud_Key_Val;														// 速度 键值
extern uint8_t Com_Key_Val;
extern uint8_t Gam_Mod_tmp0;
extern uint8_t Gam_Mod_tmp1;
extern uint16_t Mod1_Sco_Val;
extern uint16_t Slot_Sco_Val;
extern BitStatus Gam_IsBegin;
extern BitStatus Mode_OfPiano;
extern BitStatus Piano_IsBegin;
extern volatile uint32_t anyCnt=0;
extern volatile uint32_t TimingDelay; 

uint8_t  loop50HzFlag,loop40HzFlag,loop20HzFlag,\
  							  loop4HzFlag,loop2HzFlag,loop1HzFlag;//loop600HzFlag,loop500HzFlag,loop200HzFlag,loop100HzFlag,loop10HzFlag,
         
volatile uint16_t loop50HzCnt=0,loop40HzCnt,\
  			 loop20HzCnt=0,loop4HzCnt=0,loop2HzCnt=0,loop1HzCnt=0;//loop600HzCnt=0,loop500Hzcnt=0,loop200HzCnt=0,loop100HzCnt=0,loop10HzCnt=0,
	               

#pragma vector=1
__interrupt void TRAP_IRQHandler(void)
{
  
}
#pragma vector=2
__interrupt void TLI_IRQHandler(void)
{
  
}
#pragma vector=3
__interrupt void AWU_IRQHandler(void)
{
  
}
#pragma vector=4
__interrupt void CLK_IRQHandler(void)
{
  
}
#pragma vector=5
__interrupt void EXTI_PORTA_IRQHandler(void)
{
  
}
#pragma vector=6
__interrupt void EXTI_PORTB_IRQHandler(void)
{
  
}
#pragma vector=7
__interrupt void EXTI_PORTC_IRQHandler(void)
{

}
#pragma vector=8
__interrupt void EXTI_PORTD_IRQHandler(void)
{
  
}
BitStatus Exit_Flag = RESET;
#pragma vector=9
__interrupt void EXTI_PORTE_IRQHandler(void)
{

}
#ifdef STM8S903
#pragma vector=0xA
__interrupt void EXTI_PORTF_IRQHandler(void)
{
  
}
#endif
#ifdef STM8S208
#pragma vector=0xA
__interrupt void CAN_RX_IRQHandler(void)
{
  
}
#pragma vector=0xB
__interrupt void CAN_TX_IRQHandler(void)
{
  
}
#endif
#pragma vector=0xC
__interrupt void SPI_IRQHandler(void)
{
  
}
#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)   						//定时器1的溢出中断服务函数
{
	
}
#pragma vector=0xE
__interrupt void TIM1_CAP_COM_IRQHandler(void)
{
  
}
#ifdef STM8S903
#pragma vector=0xF
__interrupt void TIM5_UPD_OVF_BRK_TRG_IRQHandler(void)
{
  
}
#pragma vector=0x10
__interrupt void TIM5_CAP_COM_IRQHandler(void)
{
  
}
#else
#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
    if( TIM2_GetITStatus(TIM2_IT_UPDATE) != RESET ) 
    {
	  	TimingDelay_Decrement();
		
		if(Gam_Mod_Val==0x02&&Piano_IsBegin==SET)
		{
			Mod_Key_Val = Mod_Key_Scan();
			if(Mod_Key_Val == 1)
			{
				Piano_IsBegin = RESET;
				TimingDelay = 0;
				Yx5p_Stop();
				
				if(++Gam_Mod_Val>=4) Gam_Mod_Val = 0;							// Gam_Mod: 0 - 3
				/*进行模式切换前记得保存相关的数据，比如得分etc.*/
				Ht1621_Show_Mod(Gam_Mod_Val);
				switch(Gam_Mod_Val)												// 模式之间的切换需要初始化
				{
					case 0x00: // 模式 1  打地鼠 模式
					{
						Gam_IsBegin = RESET;									// 游戏切换到打地鼠模式	
						Gam_Tim_Val = 0;										// 游戏 时长 清零	
						Gam_Sco_Val = 0;										// 游戏 得分 清零
						Gam_Err_Val = 0;										// 错误 次数 清零
					}break;
					case 0x01: // 模式 2  按泡泡 模式
					{
						Mod1_Sco_Val = 0;
						Gam_Mod_tmp0 = 0xfe;									// 还未按下的泡泡
						GPIO_Write(GPIOB,0x00);									// LED 全亮 				
					}break;
					case 0x02: // 模式 3  弹钢琴 模式
					{
						GPIO_Write(GPIOB,0xfe);									// LED 全灭
					}break;
					case 0x03: // 模式 4  老虎机 模式
					{
						Gam_Mod_tmp1 = 0xfe;
						GPIO_Write(GPIOB,0xfe);									// LED 全灭
					}break;
					default:{}break;
				}
				Flash_Write_Byte(Addr_Mod_Val,Gam_Mod_Val);						// 存储当前模式
			}
//			else if(Mod_Key_Val == 2)
//			{
//				Piano_IsBegin = RESET;
//				TimingDelay = 0;
//				Yx5p_Stop();
//				
//				Flash_Write_Word(Addr_Sco_Slot,Slot_Sco_Val);
//				Yx5p_Speak(0x01);
//				while(Yx5p_Isbusy());
//				GPIO_WriteHigh(HT_PORT0,HT_LEDB);								// 背光断电
//				GPIO_WriteLow(POWER_PORT,POWER_PIN);
//			}
			
			Sud_Key_Val = Sud_Key_Scan();
			if(Sud_Key_Val == 1)
			{
				Piano_IsBegin = RESET;
				TimingDelay = 0;
				Yx5p_Stop();
				
				Mode_OfPiano = (BitStatus)!Mode_OfPiano;
				Flash_Write_Word(Addr_Pio_Mod,Mode_OfPiano);
				GPIO_Write(GPIOB,0xfe);											// 熄灭所有LED
				Yx5p_Speak(0xC4);
			}
//			else if(Sud_Key_Val == 2)
//			{
//			  	/* 音量切换 */
//				if(++Gam_Vol_Val>=4) Gam_Vol_Val = 0;							// Gam_Vol: 0 - 3
//				Yx5p_V_Level(Gam_Vol_Val);
//				Yx5p_Speak(0x0b);												// 音量提示
//				Flash_Write_Byte(Addr_Vol_Val,Gam_Vol_Val);						// 存储当前音量
//			}
		}
		(void)rand();
	}
	TIM2_ClearITPendingBit(TIM2_IT_UPDATE);  									//清除定时器3的溢出标志位
}
#pragma vector=0x10
__interrupt void TIM2_CAP_COM_IRQHandler(void)
{
  
}
#endif
#if defined (STM8S208) || defined(STM8S207) || defined(STM8S105)
#pragma vector=0x11
__interrupt void TIM3_UPD_OVF_BRK_IRQHandler(void)
{
//  	if( TIM3_GetITStatus(TIM3_IT_UPDATE) != RESET ) 
//    {
//	  	/*---------------模式按键检测---------------*/
//		Mod_Key_Val = Mod_Key_Scan();
//		/*---------------音效按键检测---------------*/
//		Sud_Key_Val = Sud_Key_Scan();
//		/*---------------地鼠按键检测---------------*/
//		Com_Key_Val = Com_Key_Scan();
//		
//		(void)rand();
//	}
//	TIM3_ClearITPendingBit(TIM3_IT_UPDATE);  									//清除定时器3的溢出标志位
}
#pragma vector=0x12
__interrupt void TIM3_CAP_COM_IRQHandler(void)
{
  
}
#endif
//#ifndef STM8S105
#if defined (STM8S208) || defined(STM8S207) || defined(STM8S105)
#pragma vector=0x13
__interrupt void UART1_TX_IRQHandler(void)
{
//	UART1_ClearITPendingBit(UART1_IT_RXNE);
}
#pragma vector=0x14
__interrupt void UART1_RX_IRQHandler(void)
{ 
//	UART1_ClearITPendingBit(UART1_IT_RXNE);
}
#endif
#pragma vector=0x15
__interrupt void I2C_IRQHandler(void)
{
  
}
#ifdef STM8S105
#pragma vector=0x16
__interrupt void UART2_TX_IRQHandler(void)
{
//   UART2_ClearITPendingBit(UART2_IT_RXNE);
}
#pragma vector=0x17
__interrupt void UART2_RX_IRQHandler(void)
{
//   UART2_ClearITPendingBit(UART2_IT_RXNE);
}
#endif
#if defined(STM8S207) || defined(STM8S208)
#pragma vector=0x16
__interrupt void UART3_TX_IRQHandler(void)
{
  
}
#pragma vector=0x17
__interrupt void UART3_RX_IRQHandler(void)
{
  
}
#endif
#if defined(STM8S207) || defined(STM8S208)
#pragma vector=0x18
__interrupt void ADC2_IRQHandler(void)
{
   
}
#else
#pragma vector=0x18
__interrupt void ADC1_IRQHandler(void)
{
   
}
#endif
#ifdef STM8S903
#pragma vector=0x19
__interrupt void TIM6_UPD_OVF_TRG_IRQHandler(void)
{
  
}
#else
#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
	if( TIM4_GetITStatus(TIM4_IT_UPDATE) != RESET ) 
    {
		anyCnt++;
//        if(++loop200HzCnt * 200 >=1000 )//5ms
//        {
//            loop200HzCnt=0;
//            loop200HzFlag=1;
//        }
//        if(++loop100HzCnt * 100 >=1000 )//10ms
//        {
//            loop100HzCnt=0;
//            loop100HzFlag=1;
//        }
        if(++loop50HzCnt * 50 >= 1000 )//20ms
        {
            loop50HzCnt=0;
            loop50HzFlag=1;
        }
		if(++loop40HzCnt * 40 >= 1000 )//25ms
        {
            loop40HzCnt=0;
            loop40HzFlag=1;
        }
        if(++loop20HzCnt * 20 >=1000 )//50ms
        {
            loop20HzCnt=0;
            loop20HzFlag=1;
        }
//        if(++loop10HzCnt * 10 >=1000 )//100ms
//        {
//            loop10HzCnt=0;
//            loop10HzFlag=1;
//        }
        if(++loop4HzCnt * 4 >=1000 )//250ms
        {
            loop4HzCnt=0;
            loop4HzFlag=1;
			IWDG_ReloadCounter();												//喂狗
        }
        if(++loop2HzCnt * 2 >=1000 )//500ms
        {
            loop2HzCnt=0;
            loop2HzFlag=1;
        }
        if(++loop1HzCnt * 1 >=1000 )//1s
        {
            loop1HzCnt=0;
            loop1HzFlag=1;
        }
	}
	TIM4_ClearITPendingBit(TIM4_IT_UPDATE);  									//清除定时器4的溢出标志位
}
#endif
#pragma vector=0x1A
__interrupt void EEPROM_EEC_IRQHandler(void)
{
  
}
