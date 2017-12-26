
#include "Gam_Mod_1.h"
#include "yx5p.h"

uint8_t Gam_Mod_tmp0 = 0xfe;													//
extern uint16_t Mod1_Sco_Val;

void Talk(uint8_t Sud,uint8_t Key_Val)
{
	switch(Sud)
	{
		case 0x01:Yx5p_Speak(0x0d);break;
		case 0x02:Yx5p_Speak(0x0e);break;
		case 0x03:
		{
			switch (Key_Val)
			{
				case 0xfc:
				case 0xf6:
				case 0xde:
				case 0x7e:
					Yx5p_Speak(0x0f);break;
				case 0xbe:
				case 0xee:
				case 0xfa:
					Yx5p_Speak(0x10);break;
				default:Yx5p_Speak(0x10);break;
			}
		}break;
		case 0x04:Yx5p_Speak(0x11);break;
		case 0x05:
		{
			switch (Key_Val)
			{
				case 0xfc:
				case 0xf6:
				case 0xde:
				case 0x7e:
					Yx5p_Speak(0x12);break;
				case 0xbe:
				case 0xee:
				case 0xfa:
					Yx5p_Speak(0x13);break;
				default:Yx5p_Speak(0x13);break;
			}
		}break;
		default:{};break;
	}
}

void Gam_Mod_1(uint8_t Key_Val)
{
	if(Gam_Mod_tmp0!=0x00)														// 表示还有按键没有按下
	{
		if(((Key_Val>>1)&0x01) == 0) // Do Key_1
		{
			if((Gam_Mod_tmp0>>1)&0x01)
			{	
				Mod1_Sco_Val ++;
				if(Mod1_Sco_Val==1000)
					Mod1_Sco_Val = 0;
//				Talk(Gam_Sud_Val,Key_Val);
				Gam_Mod_tmp0 &= 0xfc;
				GPIO_WriteHigh(GPIOB,GPIO_PIN_1);
			}
		}
		if(((Key_Val>>2)&0x01) == 0) // Re Key_2
		{
			if((Gam_Mod_tmp0>>2)&0x01)
			{	
				Mod1_Sco_Val ++;
				if(Mod1_Sco_Val==1000)
					Mod1_Sco_Val = 0;
//				Talk(Gam_Sud_Val,Key_Val);
				Gam_Mod_tmp0 &= 0xfa;
				GPIO_WriteHigh(GPIOB,GPIO_PIN_2);
			}
		}
		if(((Key_Val>>3)&0x01) == 0) // Mi Key_3
		{
			if((Gam_Mod_tmp0>>3)&0x01)
			{	
				Mod1_Sco_Val ++;
				if(Mod1_Sco_Val==1000)
					Mod1_Sco_Val = 0;
//				Talk(Gam_Sud_Val,Key_Val);
				Gam_Mod_tmp0 &= 0xf6;
				GPIO_WriteHigh(GPIOB,GPIO_PIN_3);
			}
		}
		if(((Key_Val>>4)&0x01) == 0) // Fa Key_4 
		{
			if((Gam_Mod_tmp0>>4)&0x01)
			{	
				Mod1_Sco_Val ++;
				if(Mod1_Sco_Val==1000)
					Mod1_Sco_Val = 0;
//				Talk(Gam_Sud_Val,Key_Val);
				Gam_Mod_tmp0 &= 0xee;
				GPIO_WriteHigh(GPIOB,GPIO_PIN_4);
			}
		}
		if(((Key_Val>>5)&0x01) == 0) // So Key_5
		{
			if((Gam_Mod_tmp0>>5)&0x01)
			{	
				Mod1_Sco_Val ++;
				if(Mod1_Sco_Val==1000)
					Mod1_Sco_Val = 0;
//				Talk(Gam_Sud_Val,Key_Val);
				Gam_Mod_tmp0 &= 0xde;
				GPIO_WriteHigh(GPIOB,GPIO_PIN_5);
			}
		}
		if(((Key_Val>>6)&0x01) == 0) // La Key_6
		{
			if((Gam_Mod_tmp0>>6)&0x01)
			{	
				Mod1_Sco_Val ++;
				if(Mod1_Sco_Val==1000)
					Mod1_Sco_Val = 0;
//				Talk(Gam_Sud_Val,Key_Val);
				Gam_Mod_tmp0 &= 0xbe;
				GPIO_WriteHigh(GPIOB,GPIO_PIN_6);
			}
		}
		if(((Key_Val>>7)&0x01) == 0) // Xi Key_7
		{
			if((Gam_Mod_tmp0>>7)&0x01)
			{	
				Mod1_Sco_Val ++;
				if(Mod1_Sco_Val==1000)
					Mod1_Sco_Val = 0;
//				Talk(Gam_Sud_Val,Key_Val);
				Gam_Mod_tmp0 &= 0x7e;
				GPIO_WriteHigh(GPIOB,GPIO_PIN_7);
			}
		}
		if(Key_Val != 0xfe)														// 响应音效
		{
			Talk(Gam_Sud_Val,Key_Val);
		}
//		switch(Key_Val)
//		{
//			case 0xfc: // Do Key_1
//			{
//				if((Gam_Mod_tmp0>>1)&0x01)
//				{	
//				  	Mod1_Sco_Val ++;
//					if(Mod1_Sco_Val==1000)
//					  	Mod1_Sco_Val = 0;
//				  	Talk(Gam_Sud_Val,Key_Val);
//					Gam_Mod_tmp0 &= 0xfc;
//					GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
//				}
//			}break;
//			case 0xfa: // Re Key_2
//			{
//				if((Gam_Mod_tmp0>>2)&0x01)
//				{	
//	  				Mod1_Sco_Val ++;
//					if(Mod1_Sco_Val==1000)
//					  	Mod1_Sco_Val = 0;
//				  	Talk(Gam_Sud_Val,Key_Val);
//					Gam_Mod_tmp0 &= 0xfa;
//					GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
//				}
//			}break;
//			case 0xf6: // Mi Key_3
//			{
//				if((Gam_Mod_tmp0>>3)&0x01)
//				{	
//		  			Mod1_Sco_Val ++;
//					if(Mod1_Sco_Val==1000)
//					  	Mod1_Sco_Val = 0;
//				  	Talk(Gam_Sud_Val,Key_Val);
//					Gam_Mod_tmp0 &= 0xf6;
//					GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
//				}
//			}break;
//			case 0xee: // Fa Key_4 
//			{
//				if((Gam_Mod_tmp0>>4)&0x01)
//				{	
//		  			Mod1_Sco_Val ++;
//					if(Mod1_Sco_Val==1000)
//					  	Mod1_Sco_Val = 0;
//				  	Talk(Gam_Sud_Val,Key_Val);
//					Gam_Mod_tmp0 &= 0xee;
//					GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
//				}
//			}break;
//			case 0xde: // So Key_5
//			{
//				if((Gam_Mod_tmp0>>5)&0x01)
//				{	
//			  		Mod1_Sco_Val ++;
//					if(Mod1_Sco_Val==1000)
//					  	Mod1_Sco_Val = 0;
//				  	Talk(Gam_Sud_Val,Key_Val);
//					Gam_Mod_tmp0 &= 0xde;
//					GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
//				}
//			}break;
//			case 0xbe: // La Key_6
//			{
//				if((Gam_Mod_tmp0>>6)&0x01)
//				{	
//			  		Mod1_Sco_Val ++;
//					if(Mod1_Sco_Val==1000)
//					  	Mod1_Sco_Val = 0;
//				  	Talk(Gam_Sud_Val,Key_Val);
//					Gam_Mod_tmp0 &= 0xbe;
//					GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
//				}
//			}break;
//			case 0x7e: // Xi Key_7
//			{
//				if((Gam_Mod_tmp0>>7)&0x01)
//				{	
//				  	Mod1_Sco_Val ++;
//					if(Mod1_Sco_Val==1000)
//					  	Mod1_Sco_Val = 0;
//				  	Talk(Gam_Sud_Val,Key_Val);
//					Gam_Mod_tmp0 &= 0x7e;
//					GPIO_WriteHigh(GPIOB,(GPIO_Pin_TypeDef)~Key_Val);
//				}
//			}break;
//			default:{};break;
//		}
	}
	else
	{
		Gam_Mod_tmp0 = 0xfe;													// 还未按下的泡泡
		GPIO_Write(GPIOB,0x00);													// LED 全亮 			
	}
}