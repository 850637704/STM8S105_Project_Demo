
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
extern uint8_t Mod_Key_Val;														// ģʽ ��ֵ
extern uint8_t Sud_Key_Val;														// �ٶ� ��ֵ
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
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)   						//��ʱ��1������жϷ�����
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
				/*����ģʽ�л�ǰ�ǵñ�����ص����ݣ�����÷�etc.*/
				Ht1621_Show_Mod(Gam_Mod_Val);
				switch(Gam_Mod_Val)												// ģʽ֮����л���Ҫ��ʼ��
				{
					case 0x00: // ģʽ 1  ����� ģʽ
					{
						Gam_IsBegin = RESET;									// ��Ϸ�л��������ģʽ	
						Gam_Tim_Val = 0;										// ��Ϸ ʱ�� ����	
						Gam_Sco_Val = 0;										// ��Ϸ �÷� ����
						Gam_Err_Val = 0;										// ���� ���� ����
					}break;
					case 0x01: // ģʽ 2  ������ ģʽ
					{
						Mod1_Sco_Val = 0;
						Gam_Mod_tmp0 = 0xfe;									// ��δ���µ�����
						GPIO_Write(GPIOB,0x00);									// LED ȫ�� 				
					}break;
					case 0x02: // ģʽ 3  ������ ģʽ
					{
						GPIO_Write(GPIOB,0xfe);									// LED ȫ��
					}break;
					case 0x03: // ģʽ 4  �ϻ��� ģʽ
					{
						Gam_Mod_tmp1 = 0xfe;
						GPIO_Write(GPIOB,0xfe);									// LED ȫ��
					}break;
					default:{}break;
				}
				Flash_Write_Byte(Addr_Mod_Val,Gam_Mod_Val);						// �洢��ǰģʽ
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
//				GPIO_WriteHigh(HT_PORT0,HT_LEDB);								// ����ϵ�
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
				GPIO_Write(GPIOB,0xfe);											// Ϩ������LED
				Yx5p_Speak(0xC4);
			}
//			else if(Sud_Key_Val == 2)
//			{
//			  	/* �����л� */
//				if(++Gam_Vol_Val>=4) Gam_Vol_Val = 0;							// Gam_Vol: 0 - 3
//				Yx5p_V_Level(Gam_Vol_Val);
//				Yx5p_Speak(0x0b);												// ������ʾ
//				Flash_Write_Byte(Addr_Vol_Val,Gam_Vol_Val);						// �洢��ǰ����
//			}
		}
		(void)rand();
	}
	TIM2_ClearITPendingBit(TIM2_IT_UPDATE);  									//�����ʱ��3�������־λ
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
//	  	/*---------------ģʽ�������---------------*/
//		Mod_Key_Val = Mod_Key_Scan();
//		/*---------------��Ч�������---------------*/
//		Sud_Key_Val = Sud_Key_Scan();
//		/*---------------���󰴼����---------------*/
//		Com_Key_Val = Com_Key_Scan();
//		
//		(void)rand();
//	}
//	TIM3_ClearITPendingBit(TIM3_IT_UPDATE);  									//�����ʱ��3�������־λ
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
			IWDG_ReloadCounter();												//ι��
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
	TIM4_ClearITPendingBit(TIM4_IT_UPDATE);  									//�����ʱ��4�������־λ
}
#endif
#pragma vector=0x1A
__interrupt void EEPROM_EEC_IRQHandler(void)
{
  
}
