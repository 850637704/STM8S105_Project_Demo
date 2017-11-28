/*---------------------------------包含头文件---------------------------------*/
#include "adc.h"

#define	ADC	60  																// 滤波深度，不宜过高，防止越界 u16

/*---------------------------------全局标志位---------------------------------*/

/*----------------------------------函数定义----------------------------------*/

//*----------------ADC1端口初始化函数---------------*/
static void Adc_Gpio_Init(void)													// 使用第12通道
{
	GPIO_Init(GPIOB, GPIO_PIN_0, GPIO_MODE_IN_FL_NO_IT);
	GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_IN_FL_NO_IT);
	GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);					
}

/*------------------ADC1初始化函数-----------------*/
void Adc1_Init(void)
{    
	Adc_Gpio_Init();
	ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,  									// 连续转换
			 (ADC1_Channel_TypeDef)(ADC1_CHANNEL_0),  							// 开启0通道
			 ADC1_PRESSEL_FCPU_D2,  											// 2分频
			 ADC1_EXTTRIG_TIM, 
			 DISABLE,   														// 关闭外部触发
			 ADC1_ALIGN_RIGHT,  												// 右对齐
			 (ADC1_SchmittTrigg_TypeDef)(ADC1_SCHMITTTRIG_CHANNEL0), 			
			 DISABLE);  														// 关闭施密特触发器
	ADC1_Cmd(ENABLE);  															// 使能ADC1
	ADC1_DataBufferCmd(ENABLE);  												// 开启缓存
//	ADC1_ScanModeCmd(ENABLE);  													// 启用扫描模式
	ADC1_StartConversion();  													// 开始转换
}

/*-------------------ADC获取AD值------------------*/
uint16_t Get_Adc1_Value(ADC1_Channel_TypeDef channel)  
{
	uint8_t t;
	uint16_t data = 0;

	for(t=0;t<ADC;t++)
	{
		if(channel!=0x0c)
		{
			data+=ADC1_GetBufferValue(channel);									// AIN0 - AIN9
		}
		else
		{
			data+=ADC1_GetConversionValue();									// AIN12
		}
	}
  	return (uint16_t)(data/ADC); 												// 返回转换平均值 
}
/*--------------Write-by-xiao-kai-2017-09-20-22-37----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/