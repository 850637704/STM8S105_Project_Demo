

#ifndef __FLASH_H
#define __FLASH_H
/*------------------------------包含所需的头文件------------------------------*/
#include "stm8s_flash.h"
#include "delay.h"

/*-----------------------------------宏定义-----------------------------------*/
#define Addr_Check			0x00		// 模式
#define Addr_Mod_Val		0x01		// 模式
#define Addr_Vol_Val		0x02		// 音量
#define Addr_Sud_Val		0x03		// 音效
//#define Addr_Lcd_Lig		0x04		// 背光

#define Addr_Sco_Spd1		0x05		// 第1关最高分
#define Addr_Sco_Spd2		0x07		// 第2关最高分
#define Addr_Sco_Spd3		0x09		// 第3关最高分
#define Addr_Sco_Spd4		0x0B		// 第4关最高分
#define Addr_Sco_Spd5		0x0D		// 第5关最高分
#define Addr_Sco_Spd6		0x0F		// 第6关最高分
#define Addr_Sco_Spd7		0x11		// 第7关最高分

#define Addr_Sco_Slot		0x13		// 老虎机金币

#define Addr_Bat_Val        0x15		// 电池电压

#define Addr_Pio_Mod		0x17		// 钢琴模式

extern uint8_t Addr_temp[7];
/*----------------------------------变量引用----------------------------------*/

/*----------------------------------函数申明----------------------------------*/
void Flash_Init(void); //eeprom 初始化函数

void Flash_Write_Block(void); //eeprom 块写函数

void Flash_Write_Byte(uint8_t addr,uint8_t data); //epprom 字节写函数

uint8_t Flash_Read_Byte(uint8_t addr); //eeprom 字节读函数

void Flash_Write_Word(uint8_t addr,uint16_t Data);//eeprom 字写函数

uint16_t Flash_Read_Word(uint8_t addr);//eeprom 字读函数

void Init_Flash_Data(void);

void Flash_Down_Data(void);

#endif
/*--------------Write-by-xiao-kai\2017\05\17\12\08----QQ-850637704------------*/
/*-------------------------Always have a nice day-----------------------------*/


