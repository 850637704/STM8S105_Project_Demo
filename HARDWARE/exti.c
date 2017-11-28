
#include "exti.h"

#define key_state_0        0   //�����ĳ�ʼ״̬
#define key_state_1        1   //�������µ�״̬
#define key_state_2        2   //�����ͷŵ�״̬

void Exti_Init(void)
{
	EXTI_DeInit();
	GPIO_Init(GPIOE,(GPIO_Pin_TypeDef)(GPIO_PIN_5),GPIO_MODE_IN_PU_NO_IT);
	EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE, EXTI_SENSITIVITY_FALL_ONLY);		// �����ش���
} 

//uint8_t Exit_Key_Scan(void)
//{
//	static uint8_t key_state = 0;     											// ������״̬
//	static uint8_t key_count = 0;     											// ����������
//	BitStatus key_press = RESET;       											// �����Ƿ񱻰���
//	uint8_t key_return = 0;  													// ��������ֵ
//	
//	key_press = !(BitStatus)GPIO_ReadInputPin(GPIOE,GPIO_PIN_5);        		// ������I/O��?
//	
//	switch (key_state)
//	{
//		case key_state_0:                 										// ������ʼ̬
//			if (RESET!=key_press)
//			{
//				key_state = key_state_1;										// �������£�״̬ת������ȷ��̬
//			}
//		break;
//		case key_state_1:                   									// ����ȷ��̬
//			if (RESET!=key_press)
//			{	
//				key_state = key_state_2;										// ״̬ת�������ͷ�̬
//			}
//			else
//			{
//				key_state = key_state_0; 										// ������̧��ת����������ʼ̬
//			}
//		break;
//		case key_state_2:
//			if (RESET==key_press) 												// �������ͷţ�ת����������ʼ̬
//			{
//			  	if(key_count>50)												// 500ms������
//					key_return = 2; 
//				else
//				  	key_return = 1;
//				key_state = key_state_0;
//				key_count = 0;
//			}
//			else if(SET==key_press)												// ����û���ͷ�
//			{
//				key_count++;
//			}
//		break;
//	}
//	return key_return;
//}

/*--------------Write-by-xiao-kai\2017\05\06\17\14----QQ-850637704------------*/
/*-------------------------Always have a nice day-----------------------------*/