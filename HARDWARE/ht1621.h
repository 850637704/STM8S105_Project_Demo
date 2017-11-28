
#ifndef _HT1621_H
#define _HT1621_H

#include "stm8s_gpio.h"

#define HT_BISA1_2_COM			0x50											// 1/2ƫѹ 4��������
#define HT_BISA1_3_COM			0x52											// 1/3ƫѹ 4��������
#define HT_WRITE_CMD			0x80											// д����
#define HT_WRITE_DATA			0xA0											// д����
#define HT_SYS_EN				0x02											// ��ϵͳ����
#define HT_RCOSC				0x30											// Ƭ��RC����
#define HT_LCD_OFF				0x04											// �ر�LCD���
#define HT_LCD_ON				0x06											// ����LCD���
#define HT_TONE_OFF				0x10											// �ر�TONE
#define HT_TONE_ON				0x12											// ����TONE
#define HT_TIMER_DIS        	0x08											// ʱ�����ʧЧ
#define HT_TIMER_EN        		0x0C											// ʱ�����ʹ��
#define HT_WDT_DIS				0x0A  											// WDT �����־���ʧЧ

#define HT_PORT0				GPIOA											// GPIOA
#define HT_PORT					GPIOC											// GPIOC
#define HT_CS					GPIO_PIN_6										// PD4  Ƭѡ
#define HT_DATA					GPIO_PIN_3										// PD5	������
#define HT_WR					GPIO_PIN_4										// PD6	дʱ��
#define HT_RD					GPIO_PIN_5										// PD7	��ʱ��
#define HT_LEDB					GPIO_PIN_5										// PD5  ����

typedef struct
{
	u8 DxB   : 1;
	u8 DxG   : 1;
	u8 DxC   : 1;
	u8 DxD   : 1;
	u8 DxA   : 1;
	u8 DxF   : 1;
	u8 DxE   : 1;
	u8 Lx    : 1;
} Htb_Seg;

typedef union
{
  	uint8_t HTB_Ram[7];

	struct
	{
		Htb_Seg Seg_1_2;
		Htb_Seg Seg_3_4;
		Htb_Seg Seg_5_6;
		Htb_Seg Seg_7_8;
		Htb_Seg Seg_9_10;
		Htb_Seg Seg_11_12;
		Htb_Seg Seg_13_14;
	} HTB_SEG;
}HTB_RAM;

static void Ht1621_send_high_bit(uint8_t data, uint8_t len);

static void Ht1621_send_low_bit(uint8_t data, uint8_t len);

static void Ht1621_send_cmd(uint8_t command);

//static void Ht1621_send_dat(uint8_t addr, uint8_t data);

//void Ht1621_write_all(uint8_t addr, uint8_t *p, uint8_t len);

//void Ht1621_clr_all_display();

static void Ht1621_Gpio_Init(void);

//void Ht1621_all_display(void);

void Ht1621_Init(void);

void Ht1621_Show_One_Num(uint8_t addr, uint8_t num, uint8_t add);

void Ht1621_Show_Bat(uint8_t bat);

void Ht1621_Show_Mod(uint8_t mod);

void Ht1621_Show_Sud(uint8_t sud);

//void Ht1621_BackL_On(void);

//void Ht1621_BackL_Off(void);

void Ht1621_Show_BAT(uint16_t bat);

void Bat_Charging(void);

void Ht1621_Show_All(uint8_t gam_mod);

void Ht1621_Show_Num(Htb_Seg *htb_ram1,Htb_Seg *htb_ram2,uint8_t num,uint8_t add);

void Ht1621_Show_Sco(uint16_t Sco_Val );

#endif
/*--------------Write-by-xiao-kai-2017-10-10-11-48----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/