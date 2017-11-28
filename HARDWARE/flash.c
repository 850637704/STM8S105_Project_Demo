
/*------------------------------包含所需的头文件------------------------------*/
#include "flash.h"
#include "yx5p.h"
#include "ht1621.h"
#include <stdlib.h>

extern uint8_t Gam_Err_Val;	
extern uint8_t Gam_Sco_Val;
extern uint8_t Gam_Tim_Val;
extern uint8_t Gam_Mod_Val;
//extern uint8_t Ht_BLig_Val;
extern uint8_t Gam_Vol_Val; 
extern uint8_t Gam_Sud_Val;
extern uint16_t Gam_Sco_[7];
extern uint8_t Gam_Mod_tmp0;
extern uint8_t Gam_Mod_tmp1;
extern uint16_t Battery_Val;
extern int16_t Slot_Sco_Val;
extern BitStatus Bat_IsCharg;
extern BitStatus Gam_IsBegin;
extern BitStatus Mode_OfPiano;

uint8_t Addr_temp[7] = {5,7,9,11,13,15,17};

/*----------------------------------变量引用----------------------------------*/
//extern uint8_t Buffer[FLASH_BLOCK_SIZE];  //开辟了一个 块 的内存（64Byte） 作为 数据存储区

/*------------------------------EEPROM初始化函数------------------------------*/
void Flash_Init(void)
{
    disableInterrupts();
    FLASH_DeInit();
    
    FLASH_ITConfig(DISABLE);
    /* Lock Data memory */ 
    FLASH_Unlock(FLASH_MEMTYPE_DATA);  											//FLASH 解锁 
    //FLASH_Lock(FLASH_MEMTYPE_DATA);
    /* Define flash programming Time*/
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);  						//设置标准编程时间FLASH_PROGRAMTIME_STANDARD
    //FLASH_EraseBlock(0x0000, FLASH_MEMTYPE_DATA);
    if(Flash_Read_Byte(0x00) != 0x55)											//如果eeprom未初始化，则初始化
    {
        Init_Flash_Data();
    }
	Flash_Down_Data();
    enableInterrupts();
}
/*------------------------------64Byte写入EEPROM------------------------------*/
//void Flash_Write_Block(void)
//{
//    disableInterrupts();
//    //FLASH_Unlock(FLASH_MEMTYPE_DATA);  //FLASH 解锁 
//    FLASH_ProgramBlock(0, FLASH_MEMTYPE_DATA, FLASH_PROGRAMMODE_STANDARD, Buffer);
//    //FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
//    //FLASH_Lock(FLASH_MEMTYPE_DATA);  //FLASH 解锁 
//    enableInterrupts();
//}

void Init_Flash_Data(void)
{	
  	Flash_Write_Byte(Addr_Check,0x55);
  	//上传各个变量初始值
	Flash_Write_Byte(Addr_Mod_Val,Gam_Mod_Val);
	Flash_Write_Byte(Addr_Vol_Val,Gam_Vol_Val);
	Flash_Write_Byte(Addr_Sud_Val,Gam_Sud_Val);
//	Flash_Write_Byte(Addr_Lcd_BLig,Ht_BLig_Val);
	//上传每个关卡的分数
	Flash_Write_Word(Addr_Sco_Spd1,Gam_Sco_[0]);
	Flash_Write_Word(Addr_Sco_Spd2,Gam_Sco_[1]);
	Flash_Write_Word(Addr_Sco_Spd3,Gam_Sco_[2]);
	Flash_Write_Word(Addr_Sco_Spd4,Gam_Sco_[3]);
	Flash_Write_Word(Addr_Sco_Spd5,Gam_Sco_[4]);
	Flash_Write_Word(Addr_Sco_Spd6,Gam_Sco_[5]);
	Flash_Write_Word(Addr_Sco_Spd7,Gam_Sco_[6]);
	//上传老虎机金币
	Flash_Write_Word(Addr_Sco_Slot,Slot_Sco_Val);
	//上传电池电量
	Flash_Write_Word(Addr_Bat_Val,Battery_Val);
	//钢琴模式
	Flash_Write_Word(Addr_Pio_Mod,Mode_OfPiano);
}

void Flash_Down_Data(void)
{	
  	//下载关键变量数据
	Gam_Mod_Val = Flash_Read_Byte(Addr_Mod_Val);
	Gam_Vol_Val = Flash_Read_Byte(Addr_Vol_Val);
	Gam_Sud_Val = Flash_Read_Byte(Addr_Sud_Val);
//	Ht_BLig_Val = Flash_Read_Byte(Addr_Lcd_BLig);
	//下载每个关卡的分数
	Gam_Sco_[0] = Flash_Read_Word(Addr_Sco_Spd1);
	Gam_Sco_[1] = Flash_Read_Word(Addr_Sco_Spd2);
	Gam_Sco_[2] = Flash_Read_Word(Addr_Sco_Spd3);
	Gam_Sco_[3] = Flash_Read_Word(Addr_Sco_Spd4);
	Gam_Sco_[4] = Flash_Read_Word(Addr_Sco_Spd5);
	Gam_Sco_[5] = Flash_Read_Word(Addr_Sco_Spd6);
	Gam_Sco_[6] = Flash_Read_Word(Addr_Sco_Spd7);
	//下载老虎机金币
	Slot_Sco_Val = Flash_Read_Word(Addr_Sco_Slot);
	//下载电池电量
	Battery_Val = Flash_Read_Word(Addr_Bat_Val);
	//下载钢琴模式
	Mode_OfPiano = (BitStatus)Flash_Read_Word(Addr_Pio_Mod);
	//设置音量
	Yx5p_V_Level(Gam_Vol_Val);
	//显示模式
	Ht1621_Show_Mod(Gam_Mod_Val);
	//显示音量
	Ht1621_Show_Sud(Gam_Vol_Val);
	//显示电量
	if(!Bat_IsCharg)															// 没有充电时 显示电量
		Ht1621_Show_BAT(Battery_Val);
	//对应模式初始化
	
	switch(Gam_Mod_Val)															// 模式之间的切换需要初始化
	{
		case 0x00: // 模式 1  打地鼠 模式
		{
			Gam_IsBegin = RESET;												// 游戏切换到打地鼠模式	
			Gam_Tim_Val = 0;													// 游戏 时长 清零	
			Gam_Sco_Val = 0;													// 游戏 得分 清零
			Gam_Err_Val = 0;													// 错误 次数 清零
		}break;
		case 0x01: // 模式 2  按泡泡 模式
		{
			Gam_Mod_tmp0 = 0xfe;												// 还未按下的泡泡
			GPIO_Write(GPIOB,0x00);												// LED 全亮 				
		}break;
		case 0x02: // 模式 3  弹钢琴 模式
		{
			GPIO_Write(GPIOB,0xfe);												// LED 全灭
		}break;
		case 0x03: // 模式 4  老虎机 模式
		{
			Gam_Mod_tmp1 = 0xfe;
			GPIO_Write(GPIOB,0xfe);												// LED 全灭
		}break;
		default:{}break;
	}
}

/*-------------------------------1Byte写入EEPROM------------------------------*/
void Flash_Write_Byte(uint8_t addr,uint8_t data)
{
    disableInterrupts();
    //FLASH_Unlock(FLASH_MEMTYPE_DATA);  //FLASH 解锁 
    FLASH_ProgramByte((FLASH_DATA_START_PHYSICAL_ADDRESS+(uint32_t)addr),data);
    //FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
    //FLASH_Lock(FLASH_MEMTYPE_DATA);  //FLASH 解锁 
    enableInterrupts();
}

/*-------------------------------从EEPROM读1Byte------------------------------*/
uint8_t Flash_Read_Byte(uint8_t addr)
{
    u8 data;
    disableInterrupts();
    //FLASH_Unlock(FLASH_MEMTYPE_DATA);  //FLASH 解锁 
    data = FLASH_ReadByte(FLASH_DATA_START_PHYSICAL_ADDRESS+(uint32_t)addr);
    //FLASH_Lock(FLASH_MEMTYPE_DATA);  //FLASH 解锁 
    //FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
    enableInterrupts();
    return data;
}

void Flash_Write_Word(uint8_t addr,uint16_t Data)
{
   disableInterrupts();
   FLASH_ProgramByte(FLASH_DATA_START_PHYSICAL_ADDRESS+(uint32_t)addr, (uint8_t)Data);
   FLASH_ProgramByte(FLASH_DATA_START_PHYSICAL_ADDRESS+(uint32_t)(addr+1), (uint8_t)(Data>>8));
   enableInterrupts();
}

u16 Flash_Read_Word(uint8_t addr)
{
   uint8_t Temp1_Data,Temp2_Data;
   uint16_t Data;
   disableInterrupts();
   Temp1_Data = FLASH_ReadByte(FLASH_DATA_START_PHYSICAL_ADDRESS+(uint32_t)addr);
   Temp2_Data= FLASH_ReadByte(FLASH_DATA_START_PHYSICAL_ADDRESS+(uint32_t)(addr+1));
   Data=Temp2_Data<<8|Temp1_Data;
   enableInterrupts();
   return Data;
}
/*--------------Write-by-xiao-kai\2017\05\17\12\08----QQ-850637704------------*/
/*-------------------------Always have a nice day-----------------------------*/

