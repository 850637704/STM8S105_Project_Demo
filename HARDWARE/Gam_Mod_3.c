
#include "Gam_Mod_3.h"
#include <stdlib.h>
#include "delay.h"
#include "yx5p.h"
#include "ht1621.h"

uint8_t Slot_Rand1;
uint8_t Gam_Mod_tmp1 = 0xfe;
extern uint8_t Gam_Vol_Val; 
extern uint8_t Slot_Time;
extern uint8_t Gam_Mod_Val;
extern uint8_t Slot_Rand;
extern int16_t Slot_Sco_Val;
extern BitStatus Slot_IsBegin;
extern uint8_t dijicizhongjiang;

uint16_t Slot_Sco_Val1 = 0;

BitStatus If_Slot_Sco_Val_X_0 = RESET;

const uint8_t Temp[7] = {3,2,1,0,4,5,6};
const uint8_t Temp1[7] = {4,3,2,1,7,6,5};
const uint8_t Slot_Num[7] = {0xee,0xf6,0xfa,0xfc,0xde,0xbe,0x7e};

uint8_t Win_Rate = 12;//表示Win_Rate局中必中一局
const uint8_t KouFen[7] = {4,3,2,1,7,6,5};
const uint8_t DeFen[7] =  {12,9,3,3,21,18,15};

void Gam_Mod_3(uint8_t Key_Val)
{
  	uint8_t i=0,t=0,j=0;
//	uint16_t temp = 0;
	uint8_t temp1 = 0;
	uint8_t temp2[7] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	
  	if(Slot_IsBegin == RESET)
	{
		GPIO_WriteLow(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
		switch(Key_Val)
		{
			case 0xfc:
				if((Gam_Mod_tmp1>>1)&0x01)
				{
					Gam_Mod_tmp1 &= 0xfc;
					if(Gam_Vol_Val) Yx5p_Speak(0x0b);
					Slot_Sco_Val = Slot_Sco_Val- KouFen[0x00];
					if(Slot_Sco_Val<0)
					{
		  				Slot_Sco_Val = 100;
						If_Slot_Sco_Val_X_0 = SET;
					}
					Slot_Sco_Val1 = Slot_Sco_Val1 + KouFen[0x00];
				}
			break;
			case 0xfa:
				if((Gam_Mod_tmp1>>2)&0x01)
				{
					Gam_Mod_tmp1 &= 0xfa;
					if(Gam_Vol_Val) Yx5p_Speak(0x0b);
					Slot_Sco_Val = Slot_Sco_Val- KouFen[0x01];
					if(Slot_Sco_Val<0)
					{
		  				Slot_Sco_Val = 100;
						If_Slot_Sco_Val_X_0 = SET;
					}
					Slot_Sco_Val1 = Slot_Sco_Val1 + KouFen[0x01];
				}
			break;
			case 0xf6://S3
				if((Gam_Mod_tmp1>>3)&0x01)
				{
					Gam_Mod_tmp1 &= 0xf6;
					if(Gam_Vol_Val) Yx5p_Speak(0x0b);
					Slot_Sco_Val = Slot_Sco_Val- KouFen[0x02];
					if(Slot_Sco_Val<0)
					{
		  				Slot_Sco_Val = 100;
						If_Slot_Sco_Val_X_0 = SET;
					}
					Slot_Sco_Val1 = Slot_Sco_Val1 + KouFen[0x02];
				}
			break;
			case 0xee:
				if((Gam_Mod_tmp1>>4)&0x01)
				{
					Gam_Mod_tmp1 &= 0xee;
					if(Gam_Vol_Val) Yx5p_Speak(0x0b);
					Slot_Sco_Val = Slot_Sco_Val- KouFen[0x03];
					if(Slot_Sco_Val<0)
					{
		  				Slot_Sco_Val = 100;
						If_Slot_Sco_Val_X_0 = SET;
					}
					Slot_Sco_Val1 = Slot_Sco_Val1 + KouFen[0x03];
				}
			break;
			case 0xde:
				if((Gam_Mod_tmp1>>5)&0x01)
				{
					Gam_Mod_tmp1 &= 0xde;
					if(Gam_Vol_Val) Yx5p_Speak(0x0b);
					Slot_Sco_Val = Slot_Sco_Val- KouFen[0x04];
					if(Slot_Sco_Val<0)
					{
		  				Slot_Sco_Val = 100;
						If_Slot_Sco_Val_X_0 = SET;
					}
					Slot_Sco_Val1 = Slot_Sco_Val1 + KouFen[0x04];
				}
			break;
			case 0xbe:
				if((Gam_Mod_tmp1>>6)&0x01)
				{
					Gam_Mod_tmp1 &= 0xbe;
					if(Gam_Vol_Val) Yx5p_Speak(0x0b);
					Slot_Sco_Val = Slot_Sco_Val- KouFen[0x05];
					if(Slot_Sco_Val<0)
					{
		  				Slot_Sco_Val = 100;
						If_Slot_Sco_Val_X_0 = SET;
					}
					Slot_Sco_Val1 = Slot_Sco_Val1 + KouFen[0x05];
				}
			break;
			case 0x7e:
				if((Gam_Mod_tmp1>>7)&0x01)
				{
					Gam_Mod_tmp1 &= 0x7e;
					if(Gam_Vol_Val) Yx5p_Speak(0x0b);
					Slot_Sco_Val = Slot_Sco_Val- KouFen[0x06];
					if(Slot_Sco_Val<0)
					{
		  				Slot_Sco_Val = 100;
						If_Slot_Sco_Val_X_0 = SET;
					}
					Slot_Sco_Val1 = Slot_Sco_Val1 + KouFen[0x06];
				}
			break;
			default:{}break;
		}
	}
	else
	{
	  	if(Gam_Vol_Val) Yx5p_Speak(0x0c);

/*----------------------------------------------------------------------------*/
		if(Slot_Time != dijicizhongjiang)
		{
			Slot_Rand = rand()%7;												// 产生随机数
		}
		else																	// 控制中奖
		{
		  	temp1 = 0;
			
			if(((Gam_Mod_tmp1>>1)&0x01)==0)//B1
				temp2[temp1++] = 0;
			if(((Gam_Mod_tmp1>>2)&0x01)==0)//B2
				temp2[temp1++] = 1;
			if(((Gam_Mod_tmp1>>3)&0x01)==0)//B3
				temp2[temp1++] = 2;
			if(((Gam_Mod_tmp1>>4)&0x01)==0)//B4
				temp2[temp1++] = 3;
			if(((Gam_Mod_tmp1>>5)&0x01)==0)//B5
				temp2[temp1++] = 4;
			if(((Gam_Mod_tmp1>>6)&0x01)==0)//B6
				temp2[temp1++] = 5;
			if(((Gam_Mod_tmp1>>7)&0x01)==0)//B7
				temp2[temp1++] = 6;
			
			Slot_Rand = temp2[rand()%temp1];
			temp1 = 0;
		}
		Slot_Rand1 = Slot_Rand;
/*----------------------------------------------------------------------------*/
		
		t = Temp[Slot_Rand]+7;
		
		j = rand()%5+1; //1-6
		
		for(i=t-j;j>0;j--)
		{
			GPIO_Write(GPIOB,Slot_Num[(i++)%7]);
			delay_ms(100); 
		}
		
		i = t;
		
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);									// 最后出奖的效果
		delay_ms(120);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);
		delay_ms(420); 
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);
		delay_ms(270);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);
		delay_ms(270);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);
		delay_ms(220);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);									// 最后出奖的效果
		delay_ms(270);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);									// 最后出奖的效果
		delay_ms(120);
		
		for(i=t;i<=(t+42);i++)													// 流水灯跑两圈
		{
			GPIO_Write(GPIOB,Slot_Num[(i)%7]);
			delay_ms(70);
		}
		
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);									// 最后出奖的效果
		delay_ms(250);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);
		delay_ms(400);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);
		delay_ms(300);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);									
		delay_ms(300);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);
		delay_ms(300);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);									// 最后出奖的效果
		delay_ms(300);
		GPIO_Write(GPIOB,Slot_Num[(i++)%7]);									// 最后出奖的效果
		delay_ms(300);
		
		for(t=0;t<4;t++)
		{
		  	GPIO_WriteReverse(GPIOB,(GPIO_Pin_TypeDef)(((~Slot_Num[(i-1)%7]))&0xfe));
			delay_ms(350);
		}
		
		while(Yx5p_Isbusy());
		
		Ht1621_Show_One_Num(5,Temp1[Slot_Rand1],1);
		Ht1621_Show_All(Gam_Mod_Val);
		
		if(Slot_Sco_Val<0)
		  	Slot_Sco_Val = 100;
		//比较中奖号码
		if(((((~Gam_Mod_tmp1)&0xfe)>>(Slot_Rand+1))&0x01))//中奖
		{
			if(Gam_Vol_Val) Yx5p_Speak(0x09);
			switch(Slot_Rand)
			{
				case 0: Slot_Sco_Val = Slot_Sco_Val + DeFen[0x00] + KouFen[0x00]; break;
				case 1: Slot_Sco_Val = Slot_Sco_Val + DeFen[0x01] + KouFen[0x01]; break;
				case 2: Slot_Sco_Val = Slot_Sco_Val + DeFen[0x02] + KouFen[0x02]; break;
				case 3: Slot_Sco_Val = Slot_Sco_Val + DeFen[0x03] + KouFen[0x03]; break;
				case 4: Slot_Sco_Val = Slot_Sco_Val + DeFen[0x04] + KouFen[0x04]; break;
				case 5: Slot_Sco_Val = Slot_Sco_Val + DeFen[0x05] + KouFen[0x05]; break;
				case 6: Slot_Sco_Val = Slot_Sco_Val + DeFen[0x06] + KouFen[0x06]; break;
				default:{}break;
			}
			if(Slot_Sco_Val>999)
			  	Slot_Sco_Val = 100;
		}
		else											  //没中奖
		{
		 	if(Gam_Vol_Val) Yx5p_Speak(0x0a);
			Slot_Sco_Val1 = 0;
		}
		
		If_Slot_Sco_Val_X_0 = RESET;
		GPIO_Write(GPIOB,0xfe);
		Slot_IsBegin = RESET;
		Gam_Mod_tmp1 = 0xfe;
		Slot_Sco_Val1 = 0;
	}
}
/*--------------Write-by-xiao-kai-2017-10-19-13-57----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/