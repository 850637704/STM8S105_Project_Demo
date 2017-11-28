
#include "Create_Rand.h"
#include "yx5p.h"
#include "mymath.h"
#include <stdlib.h>

extern uint8_t Gam_Vol_Val;
extern uint8_t Gam_Spd_Val;														// 游戏 速度
extern uint8_t Gam_Err_Val;														// 游戏 错误次数
extern uint8_t Gam_Key_Tmp;														// 表示随机数的个数，也就是一个等待周期内出现的地鼠个数
extern uint8_t Gam_Key_Tmp1;
extern uint8_t Max_Rand_Tim[8];													// 每个关卡允许等待的时间，单位50ms

uint8_t Delay_50MS = 0x00;

uint8_t NUM[3] = {0x08,0x08,0x08};

BitStatus Rand_Done = RESET;

void Create_Rand(void) 
{	
	if(++Delay_50MS==Max_Rand_Tim[Gam_Spd_Val])									// 产生随机数间隔(40-Gam_Spd_Val*5)
	{
		if(Gam_Vol_Val) Yx5p_Speak(0x19);
		Gam_Err_Val++;															// 在地鼠更新的周期内都没有按对
		Gam_Key_Tmp1 = 0;
		Delay_50MS = 0; 
		Rand_Done = SET;
	}
	
	if(Rand_Done)																// 随机数产生时间到
	{
		Rand_Done = RESET;
		
		switch(Gam_Spd_Val)
		{
			case 1:{//1
				get_rand(NUM,0,6,1);
				NUM[0x01] = 0x08;
				NUM[0x02] = 0x08;
				GPIO_Write(GPIOB,~(1<<(NUM[0x00]+1))&0xfe);
				Gam_Key_Tmp = 1;
			} break;
			case 2:{//1
				get_rand(NUM,0,6,1);
				NUM[0x01] = 0x08;
				NUM[0x02] = 0x08;
				GPIO_Write(GPIOB,~(1<<(NUM[0x00]+1))&0xfe);
				Gam_Key_Tmp = 1;
			} break;
			case 3:{//12
				switch((rand()%2)){
					case 0:{
					  	get_rand(NUM,0,6,1);
						NUM[0x01] = 0x08;
						NUM[0x02] = 0x08;
						GPIO_Write(GPIOB,~(1<<(NUM[0x00]+1))&0xfe);
						Gam_Key_Tmp = 1;
				  	}break;
					case 1:{
					  	get_rand(NUM,0,6,2);
						NUM[0x02] = 0x08;
						GPIO_Write(GPIOB,~((1<<(NUM[0x00]+1))|(1<<(NUM[0x01]+1)))&0xfe);
						Gam_Key_Tmp = 3;
				  	}break;
					default:{} break;
				}
			}break;
			case 4:{//2
					get_rand(NUM,0,6,2);
					NUM[0x02] = 0x08;
					GPIO_Write(GPIOB,~((1<<(NUM[0x00]+1))|(1<<(NUM[0x01]+1)))&0xfe);
					Gam_Key_Tmp = 3;
			}break;
			case 5:{//2
			  		get_rand(NUM,0,6,2);
					NUM[0x02] = 0x08;
					GPIO_Write(GPIOB,~((1<<(NUM[0x00]+1))|(1<<(NUM[0x01]+1)))&0xfe);
					Gam_Key_Tmp = 3;
			  	}break;
			case 6:{//23
				switch((rand()%2)){
					case 0:{	
					  	get_rand(NUM,0,6,2);
						NUM[0x02] = 0x08;
						GPIO_Write(GPIOB,~((1<<(NUM[0x00]+1))|(1<<(NUM[0x01]+1)))&0xfe);
						Gam_Key_Tmp = 3;
				  	}break;
					case 1:{
					  	get_rand(NUM,0,6,3);
						GPIO_Write(GPIOB,~((1<<(NUM[0x00]+1))|(1<<(NUM[0x01]+1))|(1<<(NUM[0x02]+1)))&0xfe);
						Gam_Key_Tmp = 7;
				  	}break;
					default:{} break;
				}
			}break;
			case 7:{//3
				get_rand(NUM,0,6,3);
				GPIO_Write(GPIOB,~((1<<(NUM[0x00]+1))|(1<<(NUM[0x01]+1))|(1<<(NUM[0x02]+1)))&0xfe);
				Gam_Key_Tmp = 7;
			} break;
			default:{} break;
		}
	}
}
