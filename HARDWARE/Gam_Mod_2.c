
#include "Gam_Mod_2.h"
#include "yx5p.h"
#include "delay.h"
#include "tim2.h"

uint8_t Which_Song = 0x00;
extern uint8_t Gam_Mod_Val;
extern uint16_t Mod2_Sco_Val;
extern BitStatus Mode_OfPiano;
extern BitStatus Piano_IsBegin;

#define Song0	48
#define Song1	42
#define Song2	32
#define Song3	62
#define Song4	42
#define Song5	42
#define Song6	42

const uint8_t tone0[Song0] = //粉刷匠
{
	5,3,5,3,
	5,3,1,
	2,4,3,2,
	5,
	5,3,5,3,
	5,3,1,
	2,4,3,2,
	1,
	2,2,4,4,
	3,1,5,
	2,4,3,2,
	5,
	5,3,5,3,
	5,3,1,
	2,4,3,2,
	1
};
const uint8_t duration0[Song0] =
{
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	4,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	4,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	4,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	4
};
const uint8_t tone1[Song1] = //小星星
{
	1,1,5,5,
	6,6,5,
	4,4,3,3,
	2,2,1,
	5,5,4,4,
	3,3,2,
	5,5,4,4,
	3,3,2,
	1,1,5,5,
	6,6,5,
	4,4,3,3,
	2,2,1
};
const uint8_t duration1[Song1] =
{
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2
};
const uint8_t tone2[Song2] = //两只老虎
{
	1,2,3,1,
	1,2,3,1,
	3,4,5,
	3,4,5,
	5,6,5,4,3,1,
	5,6,5,4,3,1,
	2,5,1,
	2,5,1
};
const uint8_t duration2[Song2] =
{
	1,1,1,1,
	1,1,1,1,
	1,1,2,
	1,1,2,
	0,0,0,0,1,1,
	0,0,0,0,1,1,
	1,1,2,
	1,1,2
};
const uint8_t tone3[Song3] = //欢乐颂
{
	3,3,4,5,
	5,4,3,2,
	1,1,2,3,
	3,2,2,
	3,3,4,5,
	5,4,3,2,
	1,1,2,3,
	2,1,1,
	2,2,3,1,
	2,3,4,3,1,
	2,3,4,3,1,
	1,2,5,
	3,3,4,5,
	5,4,3,2,
	1,1,2,3,
	2,1,1
};
const uint8_t duration3[Song3] =
{
	1,1,1,1,
	1,1,1,1,
	1,1,1,1,
	2,0,2,
	1,1,1,1,
	1,1,1,1,
	1,1,1,1,
	2,0,2,
	1,1,1,1,
	1,0,0,1,1,
	1,0,0,1,1,
	1,1,2,
	1,1,1,1,
	1,1,1,1,
	1,1,1,1,
	2,0,2,
};
const uint8_t tone4[Song4] =
{
	1,1,5,5,
	6,6,5,
	4,4,3,3,
	2,2,1,
	5,5,4,4,
	3,3,2,
	5,5,4,4,
	3,3,2,
	1,1,5,5,
	6,6,5,
	4,4,3,3,
	2,2,1
};
const uint8_t tone5[Song5] =
{
	1,1,5,5,
	6,6,5,
	4,4,3,3,
	2,2,1,
	5,5,4,4,
	3,3,2,
	5,5,4,4,
	3,3,2,
	1,1,5,5,
	6,6,5,
	4,4,3,3,
	2,2,1
};
const uint8_t tone6[Song6] =
{
	1,1,5,5,
	6,6,5,
	4,4,3,3,
	2,2,1,
	5,5,4,4,
	3,3,2,
	5,5,4,4,
	3,3,2,
	1,1,5,5,
	6,6,5,
	4,4,3,3,
	2,2,1
};
const uint8_t duration4[Song4] =
{
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2
};
const uint8_t duration5[Song5] =
{
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2
};
const uint8_t duration6[Song6] =
{
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2,
	1,1,1,1,
	1,1,2
};

const uint8_t Key[7] = {Song0,Song1,Song2,Song3,Song4,Song5,Song6};
const uint8_t * Tone[7] = { tone0, tone1, tone2, tone3, tone4, tone5, tone6 };
const uint8_t * Duration[7] = { duration0, duration1, duration2, duration3, duration4, duration5, duration6 };

void Gam_Mod_2(uint8_t Key_Val)
{
  	uint8_t time = 0;
  	if(Mode_OfPiano == SET)
	{
		if(Piano_IsBegin == RESET)															// 等待按下任意键开始游戏
		{
			if((Key_Val!=0xfe))														
			{
				switch(Key_Val)
				{
					case 0xee: Which_Song = 0x01;break;// S4
					case 0xf6: Which_Song = 0x02;break;// S3
					case 0xfa: Which_Song = 0x03;break;// S2
					case 0xfc: Which_Song = 0x04;break;// S1
					case 0x7e: Which_Song = 0x05;break;// S7
					case 0xbe: Which_Song = 0x06;break;// S6
					case 0xde: Which_Song = 0x07;break;// S5 
					default:{}break;
				}
				if(Key_Val&0x01)													// Com_Key为长按键时开始游戏
				{
					//长按Con_Key选择曲目
				  	Piano_IsBegin = SET;
				  	GPIO_Write(GPIOB,0xfe);
				}
			}
		}
		else if(Piano_IsBegin == SET)
		{
			//游戏开始
			for(time = 0;time<Key[Which_Song-1];time++)
			{
			  	switch(Tone[Which_Song-1][time]-1)
				{
					case 0: GPIO_Write(GPIOB,0xee);break;
					case 1: GPIO_Write(GPIOB,0xf6);break;
					case 2: GPIO_Write(GPIOB,0xfa);break;
					case 3: GPIO_Write(GPIOB,0xfc);break;
					case 4: GPIO_Write(GPIOB,0x7e);break;
					case 5: GPIO_Write(GPIOB,0xbe);break;
					case 6: GPIO_Write(GPIOB,0xde);break;
					default:{}break;
				}
				
			  	Yx5p_Speak(Tone[Which_Song-1][time]+1);
				
				switch(Duration[Which_Song-1][time])
				{
				  	case 0: Delay_ms(25);break;
					case 1: Delay_ms(50);break;
					case 2: Delay_ms(100);break;
					case 3: Delay_ms(150);break;
					case 4: Delay_ms(200);break;
					default:{}break;
				}
				if(Gam_Mod_Val!=2||Mode_OfPiano!=1)								// 这一句保证了在钢琴跟随模式下，当Sud_Kye(音效按键) Or Mod_Key(模式按键)按下时,可以中断当前播放的曲子,做到延时不阻塞
				  	break;
			}
			GPIO_Write(GPIOB,0xfe);
			Piano_IsBegin = RESET;
		}
	}
	else if(Mode_OfPiano == RESET)
	{
		if(Key_Val!=0xfe) GPIO_Write(GPIOB,Key_Val);
		switch(Key_Val)
		{
			case 0xfc:															// Do Key_1
				Yx5p_Speak(0x05);
				Mod2_Sco_Val += 1;
				if(Mod2_Sco_Val==1000)
					  	Mod2_Sco_Val = 0;
			break;
			case 0xfa:															// Re Key_2
				Yx5p_Speak(0x04);
				Mod2_Sco_Val += 1;
				if(Mod2_Sco_Val==1000)
					  	Mod2_Sco_Val = 0;
			break;
			case 0xf6:															// Mi Key_3
				Yx5p_Speak(0x03);
				Mod2_Sco_Val += 1;
				if(Mod2_Sco_Val==1000)
					  	Mod2_Sco_Val = 0;
			break;
			case 0xee:															// Fa Key_4
				Yx5p_Speak(0x02);
				Mod2_Sco_Val += 1;
				if(Mod2_Sco_Val==1000)
					  	Mod2_Sco_Val = 0;
			break;
			case 0xde:															// So Key_5
				Yx5p_Speak(0x08);
				Mod2_Sco_Val += 1;
				if(Mod2_Sco_Val==1000)
					  	Mod2_Sco_Val = 0;
			break;
			case 0xbe:															// La Key_6
				Yx5p_Speak(0x07);
				Mod2_Sco_Val += 1;
				if(Mod2_Sco_Val==1000)
					  	Mod2_Sco_Val = 0;
			break;
			case 0x7e:															// Xi Key_7
				Yx5p_Speak(0x06);
				Mod2_Sco_Val += 1;
				if(Mod2_Sco_Val==1000)
					  	Mod2_Sco_Val = 0;
			break;
			default:{};break;
		}
		if(!Yx5p_Isbusy()) GPIO_Write(GPIOB,0xfe);
	}
}
/*--------------Write-by-xiao-kai-2017-09-27-09-27----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/