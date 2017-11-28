
#include "yx5p.h"
#include "delay.h"

// YX5P 極笥兜兵晒
void Yx5p_Init(void)
{
  	GPIO_Init(YX5P_PORT1,(GPIO_Pin_TypeDef)(YX5P_CLK),\
	  											GPIO_MODE_OUT_PP_HIGH_FAST);	// CLK PA4
	GPIO_Init(YX5P_PORT0,(GPIO_Pin_TypeDef)(YX5P_DATA),\
	  												GPIO_MODE_OUT_PP_LOW_FAST);	// DATA PC1
	GPIO_Init(YX5P_PORT2,(GPIO_Pin_TypeDef)(YX5P_BUSY),\
	  												GPIO_MODE_IN_PU_NO_IT);		// BUSY PE5
}
// YX5P 僉夲囂粁
void Yx5p_Speak(uint8_t addr)
{
    uint8_t i;
    GPIO_WriteHigh(YX5P_PORT1,YX5P_CLK);										// CLK = 1
	GPIO_WriteLow(YX5P_PORT0,YX5P_DATA);										// SDA = 0
    for(i=0;i<8;i++)
    {
        (addr&0x80)?GPIO_WriteHigh(YX5P_PORT0,YX5P_DATA):						// SDA = 1
		  									GPIO_WriteLow(YX5P_PORT0,YX5P_DATA);// SDA = 0
		delay_us(200);
		GPIO_WriteLow(YX5P_PORT1,YX5P_CLK);										// CLK = 0
		delay_us(400);
		GPIO_WriteHigh(YX5P_PORT1,YX5P_CLK);									// CLK = 1
		delay_us(200);
        addr<<=1; /*仇峽峙恣卞匯了*/
    }
    GPIO_WriteHigh(YX5P_PORT0,YX5P_DATA);										// SDA = 0
}
// YX5P 登脱
BitStatus Yx5p_Isbusy(void)
{
	return (BitStatus)GPIO_ReadInputPin(YX5P_PORT2, YX5P_BUSY);
}
// YX5P 距准咄楚
void Yx5p_Volume(uint8_t vol)														// 0x60 - 0x75
{
	Yx5p_Speak(vol);
}
// YX5P 唯峭殴慧
void Yx5p_Stop(void)																	// 0x76
{
    Yx5p_Speak(0x4C);
}
void Yx5p_V_Level(uint8_t lvl)
{
	switch(lvl)
	{
		case 0: Yx5p_Volume(0x3f);;break;										// 床咄,峪寞斤仇報庁塀
		case 1: Yx5p_Volume(0x43);break;										// 咄楚 詰
		case 2: Yx5p_Volume(0x47);break;										// 咄楚 嶄
		case 3: Yx5p_Volume(0x4B);break;										// 咄楚 互
		default:{}break;
	}
}
/*--------------Write-by-xiao-kai-2017-09-26-15-43----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/
/*
		  t2>300us					   t3>300us
			|<->|						|<->|

CLK ！！！！！！！！+	+！！！+	+！！！+	+！！！+	+！！！+	+！！！+	+！！！+	+！！！+	+！！！！！！！！！！！！！！！ 1
			|	|	| 	|	|	|	|	|	|	|	|	|	|	|	|	|
    		+！！！+	+！！！+ 	+！！！+ 	+！！！+	+！！！+	+！！！+	+！！！+	+！！！+ 				 0

DAT 	  +！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+				 1
		  |	  D7  |	  D6  |	  D5  |	  D4  |	  D3  |	  D2  |	  D1  |	  D0  |
    ！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！！！！！！！ 0

BUSY																	  +！！！！！！！！+	 1
																		  |		   |
	！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+		   +！！！！ 0

VOICE			
																		   /\/\/\/\
	！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！+！！！！！！！<		   >！！！！ 0
																		   \/\/\/\/					
*/