
#include "Gam_Mod_0.h"
#include "mymath.h"
#include "yx5p.h"
#include "delay.h"

uint8_t Gam_Key_Tmp = 0; 														// ��ʾ������ĸ�����Ҳ����һ���ȴ������ڳ��ֵĵ������
uint8_t Gam_Key_Tmp1 = 0;
extern uint8_t Max_Err_Tim;

void Gam_Mod_0(uint8_t Key_Val)
{
  	uint8_t temp = 0xff;
	if(!Gam_IsBegin)															// �ȴ������������ʼ��Ϸ
	{
		if((Key_Val!=0xfe))														
		{
			switch(Key_Val)
			{
				case 0xee: Gam_Spd_Val = 0x01;break;							// B4
				case 0xf6: Gam_Spd_Val = 0x02;break;							// B3
				case 0xfa: Gam_Spd_Val = 0x03;break;							// B2
				case 0xfc: Gam_Spd_Val = 0x04;break;							// B1
				case 0x7e: Gam_Spd_Val = 0x05;break;							// B7
				case 0xbe: Gam_Spd_Val = 0x06;break;							// B6
				case 0xde: Gam_Spd_Val = 0x07;break;							// B5  0x07���ٶ�̫�졣��
				default:{}break;
			}
			if(Key_Val&0x01)													// Com_KeyΪ������ʱ��ʼ��Ϸ
			{
				if(Gam_Vol_Val) 
				{
					Yx5p_Speak(0x1b);											// ������Ч��Ready go��
					while(Yx5p_Isbusy());
				}
				Gam_IsBegin = SET;												// ��ʾ��Ϸ�Ѿ���ʼ
				Rand_Done = SET;												// ��ʾ�������������
				Delay_50MS = 0;
				
				Gam_Sco_Val = 0;
				Gam_Err_Val = 0;
			}
		}
	}
	else // IsBegin == SET
	{																			// ���������ͬ & û�б����¹�
		temp = ((~Key_Val)&0xfe);
	  	if((( temp >>(NUM[0x00]+1))&0x01)||(( temp >>(NUM[0x01]+1))&0x01)||(( temp >>(NUM[0x02]+1))&0x01))// ���������ͬ & û�б����¹�
		{
		  	if(Gam_Vol_Val)  Yx5p_Speak(0x18);
			if((( temp >>(NUM[0x00]+1) )&0x01)&&((Gam_Key_Tmp1&0x01) == 0x00))
			{
				Gam_Key_Tmp1 |= 0x01;												// ��ס����
				Gam_Sco_Val++;
				GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
			}
			if((( temp >>(NUM[0x01]+1) )&0x01)&&((Gam_Key_Tmp1&0x02) == 0x00))
			{
				Gam_Key_Tmp1 |= 0x02;
				Gam_Sco_Val++;
				GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
			}
			if((( temp >>(NUM[0x02]+1) )&0x01)&&((Gam_Key_Tmp1&0x04) == 0x00))
			{
				Gam_Key_Tmp1 |= 0x04;
				Gam_Sco_Val++;
				GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
			}
		}
		else																	// ���������ͬ
		{
			if(Key_Val!=0xfe)													// ��ʾ�а������²��Ұ�����
			{
				if(Gam_Vol_Val) Yx5p_Speak(0x19);
				Gam_Err_Val ++;
			}
		}
		
		if(Gam_Key_Tmp1==Gam_Key_Tmp)
		{
			Delay_50MS = 0;														// ����������һ�������
			Rand_Done = SET;
			Gam_Key_Tmp1 = 0;
			temp = 0xff;
		}
	}
}

