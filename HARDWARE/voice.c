
#include "voice.h"
#include "delay.h"

// NV020C 端口初始化
void NV20C_Init(void)
{
	GPIO_Init(GPIOC,(GPIO_Pin_TypeDef)(GPIO_PIN_1),GPIO_MODE_OUT_PP_HIGH_FAST);	// DATA
	GPIO_Init(GPIOC,(GPIO_Pin_TypeDef)(GPIO_PIN_2),GPIO_MODE_IN_PU_NO_IT);		// BUSY
}
// NV020C 选择语段
void Speak(uint8_t addr)
{
    uint8_t i;
    GPIO_WriteLow(GPIOC,GPIO_PIN_1);
    delay_ms(5);
    for(i=0;i<8;i++)
    {
        GPIO_WriteHigh(GPIOC,GPIO_PIN_1);
        if(addr&1)
        {
            delay_ms(2);delay_us(400);
            GPIO_WriteLow(GPIOC,GPIO_PIN_1);
            delay_us(800);
        }
        else
        {
            delay_us(800);
            GPIO_WriteLow(GPIOC,GPIO_PIN_1);
            delay_ms(2);delay_us(400);
        }
        addr>>=1; /*地址值右移一位*/
    }
    GPIO_WriteHigh(GPIOC,GPIO_PIN_1);
}
// NV020C 判忙
BitStatus Isbusy(void)
{
	return (BitStatus)GPIO_ReadInputPin(GPIOC, GPIO_PIN_2)?RESET:SET;
}
// NV020C 调节音量
void Volume(uint8_t vol)
{		
	Speak(0xe0|vol);
}
// NV020C 重复上次语音
void Repeat(void)
{
    Speak(0xF2);
}
// NV020C 静音
void Notone(void)
{
    Speak(0xFE);
}
/*--------------Write-by-xiao-kai-2017-09-22-10-46----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/