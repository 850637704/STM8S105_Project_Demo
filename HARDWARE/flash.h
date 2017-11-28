

#ifndef __FLASH_H
#define __FLASH_H
/*------------------------------���������ͷ�ļ�------------------------------*/
#include "stm8s_flash.h"
#include "delay.h"

/*-----------------------------------�궨��-----------------------------------*/
#define Addr_Check			0x00		// ģʽ
#define Addr_Mod_Val		0x01		// ģʽ
#define Addr_Vol_Val		0x02		// ����
#define Addr_Sud_Val		0x03		// ��Ч
//#define Addr_Lcd_Lig		0x04		// ����

#define Addr_Sco_Spd1		0x05		// ��1����߷�
#define Addr_Sco_Spd2		0x07		// ��2����߷�
#define Addr_Sco_Spd3		0x09		// ��3����߷�
#define Addr_Sco_Spd4		0x0B		// ��4����߷�
#define Addr_Sco_Spd5		0x0D		// ��5����߷�
#define Addr_Sco_Spd6		0x0F		// ��6����߷�
#define Addr_Sco_Spd7		0x11		// ��7����߷�

#define Addr_Sco_Slot		0x13		// �ϻ������

#define Addr_Bat_Val        0x15		// ��ص�ѹ

#define Addr_Pio_Mod		0x17		// ����ģʽ

extern uint8_t Addr_temp[7];
/*----------------------------------��������----------------------------------*/

/*----------------------------------��������----------------------------------*/
void Flash_Init(void); //eeprom ��ʼ������

void Flash_Write_Block(void); //eeprom ��д����

void Flash_Write_Byte(uint8_t addr,uint8_t data); //epprom �ֽ�д����

uint8_t Flash_Read_Byte(uint8_t addr); //eeprom �ֽڶ�����

void Flash_Write_Word(uint8_t addr,uint16_t Data);//eeprom ��д����

uint16_t Flash_Read_Word(uint8_t addr);//eeprom �ֶ�����

void Init_Flash_Data(void);

void Flash_Down_Data(void);

#endif
/*--------------Write-by-xiao-kai\2017\05\17\12\08----QQ-850637704------------*/
/*-------------------------Always have a nice day-----------------------------*/


