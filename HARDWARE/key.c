
#include "key.h"
#include "yx5p.h"
#include "flash.h"
#include "ht1621.h"
#include <stdlib.h>
#include "Gam_Mod_0.h"
#include "Gam_Mod_1.h"
#include "Gam_Mod_2.h"
#include "Gam_Mod_3.h"

uint8_t Slot_Time	= 0x00;
extern uint8_t Win_Rate;
extern uint8_t Slot_Time;
extern uint8_t Gam_Tim_Val;
extern uint8_t Gam_Mod_Val;
extern uint16_t Mod1_Sco_Val;
extern uint16_t Mod2_Sco_Val;
extern uint16_t Slot_Sco_Val;
extern uint16_t Slot_Sco_Val1;
extern BitStatus Slot_IsBegin;
extern BitStatus Mode_OfPiano;
extern uint8_t dijicizhongjiang;
extern BitStatus If_Slot_Sco_Val_X_0;

#define key_state_0        0   													// �����ĳ�ʼ״̬
#define key_state_1        1   													// �������µ�״̬
#define key_state_2        2   													// �����ͷŵ�״̬

/*******************************************************************************
 * �� �� ��: Key_Init
 * ����˵��: �����˿ڳ�ʼ��
 * ��    ��: void
 * �� �� ֵ: void
 ******************************************************************************/
void Key_Init(void)
{
	GPIO_Init(KEY_PORT_0,(GPIO_Pin_TypeDef)(Gam_Com_S1|Gam_Com_S2|Gam_Com_S3|\
	  		Gam_Com_S4|Gam_Com_S5|Gam_Com_S6|Gam_Com_S7),GPIO_MODE_IN_PU_NO_IT);// ����		����
	GPIO_Init(KEY_PORT_0,Gam_Spd_Key,GPIO_MODE_IN_PU_NO_IT);					// �ٶȵ��� ����
	GPIO_Init(KEY_PORT_1,Gam_Mod_Key,GPIO_MODE_IN_FL_NO_IT);					// ��Ϸģʽ ����
	
	GPIO_Init(POWER_PORT,POWER_PIN,GPIO_MODE_OUT_PP_HIGH_SLOW);					// ��Դ ����
}
/*******************************************************************************
 * �� �� ��: Com_Key_Scan
 * ����˵��: ��ⰴ��,�����ذ���ֵ,bit0 ������ʶ���̰���,��ͬ�뵥������,
													�����ȡ���Ƕ��IO�ڵĵ�ƽֵ
 * ��    ��: void
 * �� �� ֵ: ��ֵ
 ******************************************************************************/
uint8_t Com_Key_Scan(void)
{
	static uint8_t key_state0 = 0;     											// ������״̬
	static uint8_t key_count0 = 0;     											// ����������
	uint8_t key_press = 0xfe;       											// �����Ƿ񱻰���
	uint8_t key_return = 0xfe;  												// ��������ֵ
	
	key_press = (uint8_t)GPIO_ReadInputData(KEY_PORT_0)&0xfe;        			// ������I/O��?
	
	switch (key_state0)
	{
		case key_state_0:                 										// ������ʼ̬
			if (0xfe!=key_press)
			{
				key_state0 = key_state_1;										// �������£�״̬ת������ȷ��̬
			}
		break;
		case key_state_1:                   									// ����ȷ��̬
			if (0xfe!=key_press)
			{
				key_return = key_press;         								// �����԰��£�����ȷ�����Ϊ��1��
				key_state0 = key_state_2;										// ״̬ת�������ͷ�̬
			}
			else
			{
				key_state0 = key_state_0; 										// ������̧��ת����������ʼ̬
			}
		break;
		case key_state_2:
			if (0xfe==key_press) 												// �������ͷţ�ת����������ʼ̬
			{
				key_return = (key_count0>25)?key_press|0x01: key_press&0xfe;	// 500ms������
				
				key_state0 = key_state_0;
				key_count0 = 0;
			}
			else if(0xfe!=key_press)
			{
				key_count0++;
			}
		break;
	}
	return key_return;                            								// ���ذ���ֵ
}
/*******************************************************************************
 * �� �� ��: Mod_Key_Scan
 * ����˵��: ɨ��ģʽ���ܼ�
 * ��    ��: void
 * �� �� ֵ: ��ֵ
 ******************************************************************************/
uint8_t Mod_Key_Scan(void)
{
	static uint8_t key_state1 = 0;     											// ������״̬
	static uint8_t key_count1 = 0;     											// ����������
	BitStatus key_press = RESET;       											// �����Ƿ񱻰���
	uint8_t key_return = 0;  													// ��������ֵ
	
	key_press = (BitStatus)!GPIO_ReadInputPin(KEY_PORT_1,Gam_Mod_Key);        	// ������I/O��?
	
	switch (key_state1)
	{
		case key_state_0:                 										// ������ʼ̬
			if (RESET==key_press)
			{
				key_state1 = key_state_1;										// �������£�״̬ת������ȷ��̬
			}
		break;
		case key_state_1:                   									// ����ȷ��̬
			if (RESET==key_press)
			{
				key_state1 = key_state_2;										// ״̬ת�������ͷ�̬
			}
			else
			{
				key_state1 = key_state_0; 										// ������̧��ת����������ʼ̬
			}
		break;
		case key_state_2:
			if (SET==key_press) 												// �������ͷţ�ת����������ʼ̬
			{
				key_return = (key_count1>25)? 2 : 1;							// 500ms������
				
				key_state1 = key_state_0;
				key_count1 = 0;
			}
			else if(RESET==key_press)											// ����û���ͷ�
			{
				key_count1++;
			}
		break;
	}
	return key_return;
}
/*******************************************************************************
 * �� �� ��: Sud_Key_Scan
 * ����˵��: ɨ���ٶȹ��ܼ�,0,��ʾ δ��;1,��ʾ �̰�;2,��ʾ ����;//3,��ʾ ������;
 * ��    ��: void
 * �� �� ֵ: ��ֵ
 ******************************************************************************/
uint8_t Sud_Key_Scan(void)
{
	static uint8_t key_state2 = 0;     											// ������״̬
	static uint8_t key_count2 = 0;     											// ����������
	BitStatus key_press = SET;       											// �����Ƿ񱻰���
	uint8_t key_return = 0;  													// ��������ֵ
	
	key_press = (BitStatus)GPIO_ReadInputPin(KEY_PORT_0,Gam_Spd_Key);        	// ������I/O��?
	
	switch (key_state2)
	{
		case key_state_0:                 										// ������ʼ̬
			if (RESET==key_press)
			{
				key_state2 = key_state_1;										// �������£�״̬ת������ȷ��̬
			}
		break;
		case key_state_1:                   									// ����ȷ��̬
			if (RESET==key_press)
			{
				key_state2 = key_state_2;										// ״̬ת�������ͷ�̬
			}
			else
			{
				key_state2 = key_state_0; 										// ������̧��ת����������ʼ̬
			}
		break;
		case key_state_2:
			if (SET==key_press) 												// �������ͷţ�ת����������ʼ̬
			{			
				key_return = (key_count2>25)? 2 : 1;							// 500ms������
				
				key_state2 = key_state_0;
				key_count2 = 0;
			}
			else if(RESET==key_press)											// ����û���ͷ�
			{
				key_count2++;
			}
		break;
	}
	return key_return;
}
/*******************************************************************************
 * �� �� ��: Mod_Key_Processes
 * ����˵��: ģʽ����������
 * ��    ��: mod_key ��ֵ
 * �� �� ֵ: void
 ******************************************************************************/
void Mod_Key_Processes(uint8_t mod_key)
{
	switch(mod_key)
	{
		/*-----------------�̰���ʾģʽ�л�----------------*/
		case 0x01:
		{
			if(++Gam_Mod_Val>=4) Gam_Mod_Val = 0;								// Gam_Mod: 0 - 3
			/*����ģʽ�л�ǰ�ǵñ�����ص����ݣ�����÷�etc.*/
			Ht1621_Show_Mod(Gam_Mod_Val);
			switch(Gam_Mod_Val)													// ģʽ֮����л���Ҫ��ʼ��
			{
				case 0x00: // ģʽ 1  ����� ģʽ
				{
				  	if(Slot_Sco_Val1!=0)
					{
					  	if(If_Slot_Sco_Val_X_0 == RESET)
						{
							Slot_Sco_Val = Slot_Sco_Val + Slot_Sco_Val1;
							Slot_Sco_Val1 = 0;
						}
						else
						{
							If_Slot_Sco_Val_X_0 = RESET;
							Slot_Sco_Val1 = 0;
						}
					}
					Gam_IsBegin = RESET;										// ��Ϸ�л��������ģʽ	
					Gam_Tim_Val = 0;											// ��Ϸ ʱ�� ����	
					Gam_Sco_Val = 0;											// ��Ϸ �÷� ����
					Gam_Err_Val = 0;											// ���� ���� ����
				}break;
				case 0x01: // ģʽ 2  ������ ģʽ
				{
				  	Mod1_Sco_Val = 0;
					Gam_Mod_tmp0 = 0xfe;										// ��δ���µ�����
					GPIO_Write(GPIOB,0x00);										// LED ȫ�� 				
				}break;
				case 0x02: // ģʽ 3  ������ ģʽ
				{
				  	Mod2_Sco_Val = 0;
					GPIO_Write(GPIOB,0xfe);										// LED ȫ��
				}break;
				case 0x03: // ģʽ 4  �ϻ��� ģʽ
				{
					Gam_Mod_tmp1 = 0xfe;
					GPIO_Write(GPIOB,0xfe);										// LED ȫ��
				}break;
				default:{}break;
			}
			Flash_Write_Byte(Addr_Mod_Val,Gam_Mod_Val);							// �洢��ǰģʽ
		}break;
		/*-----------------������ʾ���ػ�------------------*/
		case 0x02:
		{
		  	
			if(Slot_Sco_Val1!=0)
			{
			  	if(If_Slot_Sco_Val_X_0 == RESET)
				{
					Slot_Sco_Val = Slot_Sco_Val + Slot_Sco_Val1;
					Slot_Sco_Val1 = 0;
				}
				else
				{
					If_Slot_Sco_Val_X_0 = RESET;
					Slot_Sco_Val1 = 0;
				}
			}
			Flash_Write_Word(Addr_Sco_Slot,Slot_Sco_Val);
			Yx5p_Speak(0x01);
			while(Yx5p_Isbusy());
			GPIO_WriteHigh(HT_PORT0,HT_LEDB);									// ����ϵ�
			GPIO_WriteLow(POWER_PORT,POWER_PIN);
		}break;
		default:{}break;
	}
}
/*******************************************************************************
 * �� �� ��: Sud_Key_Processes
 * ����˵��: ��������������
 * ��    ��: sud_key ��ֵ
 * �� �� ֵ: void
 ******************************************************************************/
void Sud_Key_Processes(uint8_t sud_key)
{
	switch(sud_key)
	{
		case 0x01:{																// �̰�	
			/* ��Ч�л� */
			switch(Gam_Mod_Val)
			{
				case 0x00:
				{
					if(Gam_IsBegin)
					  	Gam_IsBegin = (BitStatus)!Gam_IsBegin;
				}break;
				case 0x01:
				{
				  	if(++Gam_Sud_Val>=6) Gam_Sud_Val = 1;						// Gam_Sud: 1 - 5
					Talk(Gam_Sud_Val,0xf6);
					Flash_Write_Byte(Addr_Sud_Val,Gam_Sud_Val);					// �洢��ǰ��Ч
				}break;
				case 0x02:
				{
					Mode_OfPiano = (BitStatus)!Mode_OfPiano;
					Flash_Write_Word(Addr_Pio_Mod,Mode_OfPiano);				//
					GPIO_Write(GPIOB,0xfe);										// Ϩ������LED
					Yx5p_Speak(0xC4);											// ֹͣ����
				}break;
				case 0x03:
				{
				  	if(Gam_Mod_tmp1!=0xfe)
					{
				  		if(!Slot_IsBegin)
						{
							Slot_IsBegin = SET;
							Slot_Time += 1;
							//����Sud_Key���´�����Ҳ�������ϻ����Ĵ���������һ���Ƿ��н�
							if(Slot_Time == Win_Rate)//ÿWin_Rate�������н�һ��,���ж����עʱ�����Ѿ���ע�������ȡһ��Ϊ�н�����
							{
							  	Slot_Time = 0;
								dijicizhongjiang = rand()%Win_Rate;
							}
						}
					}
				}break;
				default:{}break;
			}
		}break;
		case 0x02:{																// ����������Ч��
			/* �����л� */
			if(++Gam_Vol_Val>=4) Gam_Vol_Val = 0;								// Gam_Vol: 0 - 3
			Yx5p_V_Level(Gam_Vol_Val);
			Yx5p_Speak(0x0b);													// ������ʾ
			Flash_Write_Byte(Addr_Vol_Val,Gam_Vol_Val);							// �洢��ǰ����
		}break;
		default:{}break;
	}
}
/*******************************************************************************
 * �� �� ��: Com_Key_Processes
 * ����˵��: ���󰴼�������
 * ��    ��: com_key ��ֵ
 * �� �� ֵ: void
 ******************************************************************************/
void Com_Key_Processes(uint8_t com_key)
{
	switch(Gam_Mod_Val)
	{
		case 0x00:Gam_Mod_0(com_key);break;
		case 0x01:Gam_Mod_1(com_key);break;
		case 0x02:Gam_Mod_2(com_key);break;
		case 0x03:Gam_Mod_3(com_key);break;
		default:break;
	}
}
/*--------------Write-by-xiao-kai-2017-09-19-09-47----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/
