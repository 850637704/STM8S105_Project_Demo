/*---------------------------------����ͷ�ļ�---------------------------------*/
#include "adc.h"

#define	ADC	60  																// �˲���ȣ����˹��ߣ���ֹԽ�� u16

/*---------------------------------ȫ�ֱ�־λ---------------------------------*/

/*----------------------------------��������----------------------------------*/

//*----------------ADC1�˿ڳ�ʼ������---------------*/
static void Adc_Gpio_Init(void)													// ʹ�õ�12ͨ��
{
	GPIO_Init(GPIOB, GPIO_PIN_0, GPIO_MODE_IN_FL_NO_IT);
	GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_IN_FL_NO_IT);
	GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);					
}

/*------------------ADC1��ʼ������-----------------*/
void Adc1_Init(void)
{    
	Adc_Gpio_Init();
	ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,  									// ����ת��
			 (ADC1_Channel_TypeDef)(ADC1_CHANNEL_0),  							// ����0ͨ��
			 ADC1_PRESSEL_FCPU_D2,  											// 2��Ƶ
			 ADC1_EXTTRIG_TIM, 
			 DISABLE,   														// �ر��ⲿ����
			 ADC1_ALIGN_RIGHT,  												// �Ҷ���
			 (ADC1_SchmittTrigg_TypeDef)(ADC1_SCHMITTTRIG_CHANNEL0), 			
			 DISABLE);  														// �ر�ʩ���ش�����
	ADC1_Cmd(ENABLE);  															// ʹ��ADC1
	ADC1_DataBufferCmd(ENABLE);  												// ��������
//	ADC1_ScanModeCmd(ENABLE);  													// ����ɨ��ģʽ
	ADC1_StartConversion();  													// ��ʼת��
}

/*-------------------ADC��ȡADֵ------------------*/
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
  	return (uint16_t)(data/ADC); 												// ����ת��ƽ��ֵ 
}
/*--------------Write-by-xiao-kai-2017-09-20-22-37----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/