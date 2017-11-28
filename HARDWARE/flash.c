
/*------------------------------���������ͷ�ļ�------------------------------*/
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

/*----------------------------------��������----------------------------------*/
//extern uint8_t Buffer[FLASH_BLOCK_SIZE];  //������һ�� �� ���ڴ棨64Byte�� ��Ϊ ���ݴ洢��

/*------------------------------EEPROM��ʼ������------------------------------*/
void Flash_Init(void)
{
    disableInterrupts();
    FLASH_DeInit();
    
    FLASH_ITConfig(DISABLE);
    /* Lock Data memory */ 
    FLASH_Unlock(FLASH_MEMTYPE_DATA);  											//FLASH ���� 
    //FLASH_Lock(FLASH_MEMTYPE_DATA);
    /* Define flash programming Time*/
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);  						//���ñ�׼���ʱ��FLASH_PROGRAMTIME_STANDARD
    //FLASH_EraseBlock(0x0000, FLASH_MEMTYPE_DATA);
    if(Flash_Read_Byte(0x00) != 0x55)											//���eepromδ��ʼ�������ʼ��
    {
        Init_Flash_Data();
    }
	Flash_Down_Data();
    enableInterrupts();
}
/*------------------------------64Byteд��EEPROM------------------------------*/
//void Flash_Write_Block(void)
//{
//    disableInterrupts();
//    //FLASH_Unlock(FLASH_MEMTYPE_DATA);  //FLASH ���� 
//    FLASH_ProgramBlock(0, FLASH_MEMTYPE_DATA, FLASH_PROGRAMMODE_STANDARD, Buffer);
//    //FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
//    //FLASH_Lock(FLASH_MEMTYPE_DATA);  //FLASH ���� 
//    enableInterrupts();
//}

void Init_Flash_Data(void)
{	
  	Flash_Write_Byte(Addr_Check,0x55);
  	//�ϴ�����������ʼֵ
	Flash_Write_Byte(Addr_Mod_Val,Gam_Mod_Val);
	Flash_Write_Byte(Addr_Vol_Val,Gam_Vol_Val);
	Flash_Write_Byte(Addr_Sud_Val,Gam_Sud_Val);
//	Flash_Write_Byte(Addr_Lcd_BLig,Ht_BLig_Val);
	//�ϴ�ÿ���ؿ��ķ���
	Flash_Write_Word(Addr_Sco_Spd1,Gam_Sco_[0]);
	Flash_Write_Word(Addr_Sco_Spd2,Gam_Sco_[1]);
	Flash_Write_Word(Addr_Sco_Spd3,Gam_Sco_[2]);
	Flash_Write_Word(Addr_Sco_Spd4,Gam_Sco_[3]);
	Flash_Write_Word(Addr_Sco_Spd5,Gam_Sco_[4]);
	Flash_Write_Word(Addr_Sco_Spd6,Gam_Sco_[5]);
	Flash_Write_Word(Addr_Sco_Spd7,Gam_Sco_[6]);
	//�ϴ��ϻ������
	Flash_Write_Word(Addr_Sco_Slot,Slot_Sco_Val);
	//�ϴ���ص���
	Flash_Write_Word(Addr_Bat_Val,Battery_Val);
	//����ģʽ
	Flash_Write_Word(Addr_Pio_Mod,Mode_OfPiano);
}

void Flash_Down_Data(void)
{	
  	//���عؼ���������
	Gam_Mod_Val = Flash_Read_Byte(Addr_Mod_Val);
	Gam_Vol_Val = Flash_Read_Byte(Addr_Vol_Val);
	Gam_Sud_Val = Flash_Read_Byte(Addr_Sud_Val);
//	Ht_BLig_Val = Flash_Read_Byte(Addr_Lcd_BLig);
	//����ÿ���ؿ��ķ���
	Gam_Sco_[0] = Flash_Read_Word(Addr_Sco_Spd1);
	Gam_Sco_[1] = Flash_Read_Word(Addr_Sco_Spd2);
	Gam_Sco_[2] = Flash_Read_Word(Addr_Sco_Spd3);
	Gam_Sco_[3] = Flash_Read_Word(Addr_Sco_Spd4);
	Gam_Sco_[4] = Flash_Read_Word(Addr_Sco_Spd5);
	Gam_Sco_[5] = Flash_Read_Word(Addr_Sco_Spd6);
	Gam_Sco_[6] = Flash_Read_Word(Addr_Sco_Spd7);
	//�����ϻ������
	Slot_Sco_Val = Flash_Read_Word(Addr_Sco_Slot);
	//���ص�ص���
	Battery_Val = Flash_Read_Word(Addr_Bat_Val);
	//���ظ���ģʽ
	Mode_OfPiano = (BitStatus)Flash_Read_Word(Addr_Pio_Mod);
	//��������
	Yx5p_V_Level(Gam_Vol_Val);
	//��ʾģʽ
	Ht1621_Show_Mod(Gam_Mod_Val);
	//��ʾ����
	Ht1621_Show_Sud(Gam_Vol_Val);
	//��ʾ����
	if(!Bat_IsCharg)															// û�г��ʱ ��ʾ����
		Ht1621_Show_BAT(Battery_Val);
	//��Ӧģʽ��ʼ��
	
	switch(Gam_Mod_Val)															// ģʽ֮����л���Ҫ��ʼ��
	{
		case 0x00: // ģʽ 1  ����� ģʽ
		{
			Gam_IsBegin = RESET;												// ��Ϸ�л��������ģʽ	
			Gam_Tim_Val = 0;													// ��Ϸ ʱ�� ����	
			Gam_Sco_Val = 0;													// ��Ϸ �÷� ����
			Gam_Err_Val = 0;													// ���� ���� ����
		}break;
		case 0x01: // ģʽ 2  ������ ģʽ
		{
			Gam_Mod_tmp0 = 0xfe;												// ��δ���µ�����
			GPIO_Write(GPIOB,0x00);												// LED ȫ�� 				
		}break;
		case 0x02: // ģʽ 3  ������ ģʽ
		{
			GPIO_Write(GPIOB,0xfe);												// LED ȫ��
		}break;
		case 0x03: // ģʽ 4  �ϻ��� ģʽ
		{
			Gam_Mod_tmp1 = 0xfe;
			GPIO_Write(GPIOB,0xfe);												// LED ȫ��
		}break;
		default:{}break;
	}
}

/*-------------------------------1Byteд��EEPROM------------------------------*/
void Flash_Write_Byte(uint8_t addr,uint8_t data)
{
    disableInterrupts();
    //FLASH_Unlock(FLASH_MEMTYPE_DATA);  //FLASH ���� 
    FLASH_ProgramByte((FLASH_DATA_START_PHYSICAL_ADDRESS+(uint32_t)addr),data);
    //FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
    //FLASH_Lock(FLASH_MEMTYPE_DATA);  //FLASH ���� 
    enableInterrupts();
}

/*-------------------------------��EEPROM��1Byte------------------------------*/
uint8_t Flash_Read_Byte(uint8_t addr)
{
    u8 data;
    disableInterrupts();
    //FLASH_Unlock(FLASH_MEMTYPE_DATA);  //FLASH ���� 
    data = FLASH_ReadByte(FLASH_DATA_START_PHYSICAL_ADDRESS+(uint32_t)addr);
    //FLASH_Lock(FLASH_MEMTYPE_DATA);  //FLASH ���� 
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

