
#include "includes.h"

uint8_t Slot_Rand = 0xff;														// �ϻ��������
uint8_t Gam_Sco_Val = 0x00;														// ��Ϸ ����
uint8_t Gam_Err_Val = 0x00;														// ��Ϸ �������
uint8_t Gam_Mod_Val = 0x00;														// ��Ϸ ģʽ
uint8_t Gam_Sud_Val = 0x01;		 												// ��Ϸ ��Ч
uint8_t Gam_Vol_Val = 0x01;														// ��Ϸ ����
uint8_t Gam_Tim_Val = 0x00;														// ��Ϸ ģʽ
uint8_t Gam_Spd_Val = 0x01;														// ��Ϸ ʱ��
uint8_t Mod_Key_Val = 0x00;														// ģʽ ��ֵ
uint8_t Sud_Key_Val = 0x00;														// �ٶ� ��ֵ
uint8_t Com_Key_Val = 0x00;														// ��ͨ ��ֵ
uint16_t Power_Down = 0x00;														// �Զ� �ػ�
uint16_t Battery_Val = 0x00;													// ��� ����
uint16_t Mod1_Sco_Val = 0x00;													// ���� ���´���
uint16_t Mod2_Sco_Val = 0x00;													// ���� ���´���
int16_t Slot_Sco_Val = 100;														// �ϻ�����ʼ����
uint8_t dijicizhongjiang = 0xff;
BitStatus Gam_IsBegin = RESET;													// ����� ��ʼ?
BitStatus Bat_IsCharg = RESET;													// ���� ���?
BitStatus Slot_IsBegin = RESET;													// �ϻ��� ��ʼ?
BitStatus Mode_OfPiano = RESET;													// ���� ģʽ?
BitStatus Piano_IsBegin = RESET;												// ���� ģʽ?
uint8_t Mod0_Led_Flash = 0x00;
uint16_t Gam_Sco_[7] = {0};														// �洢�ؿ�����
const uint8_t Max_Err_Tim[8] = {6,6,7,7,8,8,9};									// ÿ���ؿ��������Ĵ���
const uint8_t Max_Rand_Tim[8] = {40,35,30,25,20,15,15,20};						// ÿ���ؿ�����ȴ���ʱ�䣬��λ50ms

void main(void)
{
	Clk_Init();																	// ��ʼ�� CLK
	Led_Init();																	// ��ʼ�� LED
	Key_Init();																	// ��ʼ�� KEY
	Iwdg_Init();																// ��ʼ�� IWDG
	Tim2_Init();																// ��ʼ�� TIM2
//	Tim3_Init();																// ��ʼ�� TIM3
	Tim4_Init();																// ��ʼ�� TIM4
	Adc1_Init();																// ��ʼ�� ADC1
	Yx5p_Init();																// ��ʼ�� VOICE
	Flash_Init();																// ��ʼ�� FLASH
	Ht1621_Init();																// ��ʼ�� HT1621
	delay_ms(350);																
	__enable_interrupt();														// ���ж�
	Yx5p_Speak(0x00);															// ������Ч
	while(Yx5p_Isbusy());
	
	while(1)
	{
		/*-----------------------20ms-----------------------*/
		if(loop50HzFlag)//��ʾ����
		{
		  	loop50HzFlag = 0;
			/*---------------ģʽ��������---------------*/
/*Mod_Key*/	Mod_Key_Val = Mod_Key_Scan();
			Mod_Key_Processes(Mod_Key_Val);
			/*---------------��Ч��������---------------*/
/*Sud_Key*/	Sud_Key_Val = Sud_Key_Scan();
			Sud_Key_Processes(Sud_Key_Val);
			/*---------------���󰴼�����---------------*/
/*Com_Key*/	Com_Key_Val = Com_Key_Scan();
			Com_Key_Processes(Com_Key_Val);
			
			if(Com_Key_Val!=0xfe|Sud_Key_Val!=0|Mod_Key_Val!=0)					// �ػ�����������
			  	Power_Down = 0;
		} 
		/*-----------------------25ms-----------------------*/
		if(loop40HzFlag)//��ʾ����
		{
			loop40HzFlag = 0;										
			Ht1621_Show_All(Gam_Mod_Val);										// ģʽ��ͬ,LCD��ʾ�����ݲ�ͬ
		} 
		/*-----------------------50ms-----------------------*/
		if(loop20HzFlag)//���������
		{
			loop20HzFlag = 0;
			if(!Gam_Mod_Val)													// �����ģʽ
			{
			  	if(Gam_IsBegin)
				{
					Create_Rand();												// ���������

					if(Gam_Err_Val >= Max_Err_Tim[Gam_Spd_Val-1])
					{
					  	Gam_IsBegin = RESET;
						Gam_Tim_Val = 0;
					  	if(Gam_Vol_Val)
						{
							if(Gam_Sco_Val>Gam_Sco_[Gam_Spd_Val-1])				// ����������ʷ��߷�
							{
								Yx5p_Speak(0x1a);								// New High Score
								Gam_Sco_[Gam_Spd_Val-1] = Gam_Sco_Val;
								Flash_Write_Word(Addr_temp[Gam_Spd_Val-1],Gam_Sco_[Gam_Spd_Val-1]);// �洢����
							}
							else
							{
								if(Gam_Sco_Val>80)
									Yx5p_Speak(0x14);							// Amazing
								else if(Gam_Sco_Val>50)
									Yx5p_Speak(0x15);							// cool
								else if(Gam_Sco_Val>20)
									Yx5p_Speak(0x17);							// good
								else if(Gam_Sco_Val<20)
									Yx5p_Speak(0x16);							// Game Over
							}
						}
					}
				}
				else//�������Ϸû�п�ʼʱ
				{
				  	GPIO_Write(GPIOB,0xfe);
				}
			}
			if(Mod_Key_Val!=0x03)												// �����ϻ����������Ԥ���BUG
			  	(void)rand();//Slot_Rand = 
		}
		/*-----------------------500ms----------------------*/
		if(loop2HzFlag)//��紦��
		{
		  	loop2HzFlag = 0;
			
			Battery_Val = Get_Adc1_Value(ADC1_CHANNEL_0);						// ��ѹ���
			
			if((BitStatus)GPIO_ReadInputPin(GPIOA,GPIO_PIN_1))
				  	Power_Down = 0;
			if(((BitStatus)GPIO_ReadInputPin(GPIOA,GPIO_PIN_1))&&				// ��� USB�Ƿ����
			   ((BitStatus)!GPIO_ReadInputPin(GPIOA,GPIO_PIN_3)))				// ���6011�Ƿ���
			{
				Bat_IsCharg = SET;
				Bat_Charging();
			}
			else
				Bat_IsCharg = RESET;
			
			Mod0_Led_Flash = (BitStatus)!Mod0_Led_Flash;
			//if(++Mod0_Led_Flash>=7) Mod0_Led_Flash = 0;
		}
		/*-----------------------1000ms---------------------*/
		if(loop1HzFlag)
		{
			loop1HzFlag = 0;
			
			if(++Power_Down>=214)
			{
			  	Flash_Write_Word(Addr_Sco_Slot,Slot_Sco_Val);
				Yx5p_Speak(0x01);												// �ػ���Ч
				while(Yx5p_Isbusy());
				GPIO_WriteHigh(HT_PORT0,HT_LEDB);								// ����ϵ�
			  	GPIO_WriteLow(POWER_PORT,POWER_PIN);							// ��ʱ��û�а�������,�ϵ�����
			}
			
			if(!Gam_Mod_Val)
			{
			  	if(Gam_IsBegin)
				{
					if(++Gam_Tim_Val>=60) 										// ��Ϸʱ��
					{
					  	Gam_Tim_Val = 0;											
						Gam_IsBegin = RESET;									// ��Ϸ����
					  	if(Gam_Vol_Val)
						{
							if(Gam_Sco_Val>Gam_Sco_[Gam_Spd_Val-1])				// ����������ʷ��߷�
							{
								Yx5p_Speak(0x1a);								// New High Score
								Gam_Sco_[Gam_Spd_Val-1] = Gam_Sco_Val;
								Flash_Write_Word(Addr_temp[Gam_Spd_Val-1],Gam_Sco_Val);		// �洢����
							}
							else 
							{
								if(Gam_Sco_Val>80)
									Yx5p_Speak(0x14);							// Amazing
								else if(Gam_Sco_Val>50)
									Yx5p_Speak(0x15);							// cool
								else if(Gam_Sco_Val>20)
									Yx5p_Speak(0x17);							// good
								else
									Yx5p_Speak(0x1c);							// Time is over 
							}
						}
					}
				}
			}
		}
	}
}
/*--------------Write-by-xiao-kai-2017-08-18-14-18----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/
#ifdef USE_FULL_ASSERT 
void assert_failed(u8* file, u32 line)
{ 
  while (1)
  {
      
  }
}
#endif