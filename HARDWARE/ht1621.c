
#include "ht1621.h"
#include "delay.h"

extern uint8_t Slot_Rand;
extern uint8_t Slot_Rand1;
extern uint8_t Which_Song;
extern uint8_t Gam_Err_Val;
extern uint8_t Gam_Sco_Val;
extern uint8_t Gam_Vol_Val; 
extern uint8_t Gam_Mod_Val;
extern uint8_t Gam_Sud_Val;
extern uint8_t Gam_Sud_Val;
extern uint8_t Gam_Spd_Val;
extern uint16_t Battery_Val;
extern uint16_t Mod1_Sco_Val;
extern uint16_t Mod2_Sco_Val;
extern uint16_t Slot_Sco_Val;
extern BitStatus Bat_IsCharg;
extern BitStatus Gam_IsBegin;
extern BitStatus Mode_OfPiano;
extern uint16_t Gam_Sco_[7];
extern uint8_t Max_Err_Tim[8];

extern uint8_t Slot_Time;
extern uint8_t dijicizhongjiang;

HTB_RAM Htb_Ram;

//extern const uint8_t Temp1[7];
/*******************************************************************************
 * 函 数 名: Ht1621_Gpio_Init
 * 功能说明: 初始化HT与MCU相连的管脚
 * 形    参: void
 * 返 回 值: void
 ******************************************************************************/
static void Ht1621_Gpio_Init(void)
{
	GPIO_Init(HT_PORT, (GPIO_Pin_TypeDef)(HT_WR|								// HT_WR
	  									  HT_RD|								// HT_RD
										  HT_DATA),GPIO_MODE_OUT_PP_LOW_FAST);	// HT_DATA						
	GPIO_Init(HT_PORT, HT_CS,GPIO_MODE_OUT_PP_HIGH_FAST);						// HT_CS
	GPIO_Init(HT_PORT0, HT_LEDB,GPIO_MODE_OUT_PP_LOW_SLOW);
}

/*******************************************************************************
 * 函 数 名: Ht1621_send_high_bit
 * 功能说明: 向HT发送数据，高位为命令or地址，从高到低写入
 * 形    参: data、命令或地址;len、长度;
 * 返 回 值: void
 ******************************************************************************/
static void Ht1621_send_high_bit(uint8_t data, uint8_t len)
{
	uint8_t i;
	for (i=0; i<len; i++)
	{
		(data&0x80)?GPIO_WriteHigh(HT_PORT,HT_DATA):							// HT_DATA = 1
		  			GPIO_WriteLow(HT_PORT,HT_DATA);								// HT_DATA = 0
		delay_us(2);
		GPIO_WriteHigh(HT_PORT,HT_WR);
		delay_us(2);
		GPIO_WriteLow(HT_PORT,HT_WR);
		data <<= 1;
	}
}
/*******************************************************************************
 * 函 数 名: Ht1621_send_low_bit
 * 功能说明: 向HT发送数据，低位为数据，从高到低写入or读出
 * 形    参: data、数据;len、长度;
 * 返 回 值: void
 ******************************************************************************/
static void Ht1621_send_low_bit(uint8_t data, uint8_t len)
{
	uint8_t i;
	for (i=0; i<len; i++)
	{
		(data&0x01)?GPIO_WriteHigh(HT_PORT,HT_DATA):							// HT_DATA = 1
		  			GPIO_WriteLow(HT_PORT,HT_DATA);								// HT_DATA = 0
		delay_us(2);
		GPIO_WriteHigh(HT_PORT,HT_WR);
		delay_us(2);
		GPIO_WriteLow(HT_PORT,HT_WR);
		data >>= 1;
	}
}
/*******************************************************************************
 * 函 数 名: Ht1621_send_cmd
 * 功能说明: 向HT发送命令
 * 形    参: command、命令;
 * 返 回 值: void
 ******************************************************************************/
static void Ht1621_send_cmd(uint8_t command)
{
  	__disable_interrupt();
	GPIO_WriteLow(HT_PORT,HT_CS);												// 片选
	Ht1621_send_high_bit(0x80, 4);												// 命令模式
	Ht1621_send_high_bit(command, 8);											// 具体命令
	GPIO_WriteHigh(HT_PORT,HT_CS);
	__enable_interrupt();
}
/*******************************************************************************
 * 函 数 名: Ht1621_send_dat
 * 功能说明: 向HT发送数据
 * 形    参: addr、地址;data、数据;
 * 返 回 值: void
 ******************************************************************************/
//static void Ht1621_send_dat(uint8_t addr, uint8_t data)							// addr 就是 0、1、2、3、4、5、、、31.
//{
//  	__disable_interrupt();
//	GPIO_WriteLow(HT_PORT,HT_CS);
//	Ht1621_send_high_bit(0xA0, 3);												// 数据模式
//	Ht1621_send_high_bit(addr<<2, 6);											// 地址
//	Ht1621_send_low_bit(data, 4);												// 写入的数据
//	GPIO_WriteHigh(HT_PORT,HT_CS);
//	__enable_interrupt();
//}
/*******************************************************************************
 * 函 数 名: Ht1621_write_all
 * 功能说明: 向HT发送数据,连续模式
 * 形    参: addr、地址;p、数据指针;len、长度;
 * 返 回 值: void
 ******************************************************************************/
void Ht1621_write_all(uint8_t addr, uint8_t *p, uint8_t len)
{
	uint8_t i;
	
	GPIO_WriteLow(HT_PORT,HT_CS);
	Ht1621_send_high_bit(0xA0, 3);
	Ht1621_send_high_bit(addr<<2, 6);
	
	for (i=0; i<len; i++, p++)
	{
		Ht1621_send_low_bit(*p, 8);
	}
	GPIO_WriteHigh(HT_PORT,HT_CS);
}
/*******************************************************************************
 * 函 数 名: Ht1621_clr_all_display
 * 功能说明: 向HT发送数据,连续模式
 * 形    参: addr、地址;p、数据指针;len、长度;
 * 返 回 值: void
 ******************************************************************************/
//void Ht1621_clr_all_display(void)
//{
//	uint8_t i;
//	uint8_t addr = 0;
//	
//	for (i=0; i<32; i++)
//	{
//		Ht1621_send_dat(addr, 0x00);
//		Ht1621_send_dat(addr+1, 0x00);
//		addr += 2;
//	}
//}
/*******************************************************************************
 * 函 数 名: Ht1621_all_display
 * 功能说明: 显示LCD上全部字段
 * 形    参: void
 * 返 回 值: void
 ******************************************************************************/
//void Ht1621_all_display(void)
//{
//	uint8_t i;
//	uint8_t addr = 0;
//	
//	for (i=0; i<32; i++)
//	{
//		Ht1621_send_dat(addr, 0x0F);
//		Ht1621_send_dat(addr+1, 0x0F);
//		addr += 2;
//	}	
//}
/*******************************************************************************
 * 函 数 名: Ht1621_Init
 * 功能说明: 初始化Ht1621
 * 形    参: void
 * 返 回 值: void
 ******************************************************************************/
void Ht1621_Init(void)
{
  	Ht1621_Gpio_Init();
	Ht1621_send_cmd(HT_SYS_EN);													// 打开系统振荡器
	Ht1621_send_cmd(HT_RCOSC);													// 片内RC振荡器
	Ht1621_send_cmd(HT_BISA1_3_COM);											// 1/3偏压 4个公共口
	Ht1621_send_cmd(HT_LCD_ON);													// 开启LCD输出
//	Ht1621_send_cmd(HT_TONE_OFF);												// 关闭TONE输出
//	Ht1621_send_cmd(HT_TIMER_DIS);												// 时基输出失效
//	Ht1621_send_cmd(HT_WDT_DIS);
//	Ht1621_clr_all_display();
}
/*******************************************************************************
 * 函 数 名: Ht1621_Show_One_Num
 * 功能说明: 在地址addr处显示数字data
 * 形    参: addr: 0-6,此款LCD可显示7个数字;
			 num: 0-f,数字包括0-f;
 * 返 回 值: void
 ******************************************************************************/
void Ht1621_Show_One_Num(uint8_t addr, uint8_t num, uint8_t add)
{
  	switch(addr)
	{
		case 1:
		{
		  	Ht1621_Show_Num(&Htb_Ram.HTB_SEG.Seg_3_4,&Htb_Ram.HTB_SEG.Seg_5_6,num,add);
		}break;
		case 2:
		{
		  	Ht1621_Show_Num(&Htb_Ram.HTB_SEG.Seg_5_6,&Htb_Ram.HTB_SEG.Seg_7_8,num,add);
		}break;
		case 3:
		{
		  	Ht1621_Show_Num(&Htb_Ram.HTB_SEG.Seg_7_8,&Htb_Ram.HTB_SEG.Seg_9_10,num,add);
		}break;
		case 4:
		{
		  	Ht1621_Show_Num(&Htb_Ram.HTB_SEG.Seg_9_10,&Htb_Ram.HTB_SEG.Seg_11_12,num,add);
		}break;
		case 5:
		{
		  	Ht1621_Show_Num(&Htb_Ram.HTB_SEG.Seg_11_12,&Htb_Ram.HTB_SEG.Seg_13_14,num,add);
		}break;
		default:break;
	}
}
/*******************************************************************************
 * 函 数 名: Ht1621_Show_Num
 * 功能说明: 在LCD的第addr个位置显示数字data
 * 形    参: htb_ram: HT1621内存结构体指针
			 num: 0-6,在LCD需要显示的位置;
			 dat: 0-f,数字0-9;
			 add: 0,不显示;1,正常显示;
 * 返 回 值: void
 ******************************************************************************/
void Ht1621_Show_Num(Htb_Seg *htb_ram1,Htb_Seg *htb_ram2,uint8_t num,uint8_t add)
{
	switch(num)
	{
		case 0x00:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = add;htb_ram1->DxE = add;
			htb_ram2->DxB = add;htb_ram2->DxG = 0;htb_ram2->DxC = add;htb_ram2->DxD =add;
		}break;
		case 0x01:
		{
			htb_ram1->DxA = 0;htb_ram1->DxF = 0;htb_ram1->DxE = 0;
			htb_ram2->DxB = add;htb_ram2->DxG = 0;htb_ram2->DxC = add;htb_ram2->DxD = 0;
		}break;
		case 0x02:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = 0;htb_ram1->DxE = add;
			htb_ram2->DxB = add;htb_ram2->DxG = add;htb_ram2->DxC = 0;htb_ram2->DxD = add;
		}break;
		case 0x03:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = 0;htb_ram1->DxE = 0;
			htb_ram2->DxB = add;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = add;
		}break;
		case 0x04:
		{
			htb_ram1->DxA = 0;htb_ram1->DxF = add;htb_ram1->DxE = 0;
			htb_ram2->DxB = add;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = 0;
		}break;
		case 0x05:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = add;htb_ram1->DxE = 0;
			htb_ram2->DxB = 0;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = add;
		}break;
		case 0x06:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = add;htb_ram1->DxE = add;
			htb_ram2->DxB = 0;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = add;
		}break;
		case 0x07:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = 0;htb_ram1->DxE = 0;
			htb_ram2->DxB = add;htb_ram2->DxG = 0;htb_ram2->DxC = add;htb_ram2->DxD = 0;
		}break;
		case 0x08:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = add;htb_ram1->DxE = add;
			htb_ram2->DxB = add;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = add;
		}break;
		case 0x09:
		{
			htb_ram1->DxA = add;htb_ram1->DxF = add;htb_ram1->DxE = 0;
			htb_ram2->DxB = add;htb_ram2->DxG = add;htb_ram2->DxC = add;htb_ram2->DxD = add;
		}break;
		default: break;
	}
}
/*******************************************************************************
 * 函 数 名: Ht1621_Show_Bat
 * 功能说明: 显示电量标志，电池外框常显示
 * 形    参: bat: 0-3;
 * 返 回 值: void
 ******************************************************************************/
void Ht1621_Show_Bat(uint8_t bat)
{
 	Htb_Ram.HTB_SEG.Seg_1_2.DxB = 1;
	switch(bat)
	{
		case 0:
		{
		  	Htb_Ram.HTB_SEG.Seg_1_2.DxD = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxG = 0;
			Htb_Ram.HTB_SEG.Seg_1_2.DxB = 0;
			Htb_Ram.HTB_SEG.Seg_1_2.DxC = 0;
		}break;
		case 1:
		{
		  	Htb_Ram.HTB_SEG.Seg_1_2.DxD = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxG = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxB = 0;
			Htb_Ram.HTB_SEG.Seg_1_2.DxC = 0;
		}break;
		case 2:
		{
		  	Htb_Ram.HTB_SEG.Seg_1_2.DxD = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxG = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxB = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxC = 0;
		}break;
		case 3:
		{
		  	Htb_Ram.HTB_SEG.Seg_1_2.DxD = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxG = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxB = 1;
			Htb_Ram.HTB_SEG.Seg_1_2.DxC = 1;
		}break;
		default: break;
	}
}
/*******************************************************************************
 * 函 数 名: Ht1621_Show_Mod
 * 功能说明: 显示模式
 * 形    参: mod: 0-3;
 * 返 回 值: void
 ******************************************************************************/
void Ht1621_Show_Mod(uint8_t mod)
{
	switch(mod)
	{
		case 0:
		{
		  	Htb_Ram.HTB_SEG.Seg_3_4.DxB = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxG = 1;
			Htb_Ram.HTB_SEG.Seg_3_4.DxC = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.Lx = 0;
		}break;
		case 1:
		{
		  	Htb_Ram.HTB_SEG.Seg_3_4.DxB = 1;
			Htb_Ram.HTB_SEG.Seg_3_4.DxG = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxC = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.Lx = 0;
		}break;
		case 2:
		{
		  	Htb_Ram.HTB_SEG.Seg_3_4.DxB = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxG = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxC = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.Lx = 1;
		}break;
		case 3:
		{
		  	Htb_Ram.HTB_SEG.Seg_3_4.DxB = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxG = 0;
			Htb_Ram.HTB_SEG.Seg_3_4.DxC = 1;
			Htb_Ram.HTB_SEG.Seg_3_4.Lx = 0;
		}break;
		default: break;
	}
}
/*******************************************************************************
 * 函 数 名: Ht1621_Show_Sud
 * 功能说明: 显示声音
 * 形    参: sud: 0-3;
 * 返 回 值: void
 ******************************************************************************/
void Ht1621_Show_Sud(uint8_t sud)
{
  	Htb_Ram.HTB_SEG.Seg_1_2.DxA = 1;
	if(Gam_Mod_Val==0||Gam_Mod_Val==3)
		Htb_Ram.HTB_SEG.Seg_1_2.Lx = ((sud)?0:1);
	else
	  	Htb_Ram.HTB_SEG.Seg_1_2.Lx = 0;
}
/*******************************************************************************
 * 函 数 名: Bat_Charging
 * 功能说明: 显示充电动作
 * 形    参: void
 * 返 回 值: void
 ******************************************************************************/
void Bat_Charging(void)
{
  	static uint8_t i = 0;
	if(++i>3) i = 0;
	Ht1621_Show_Bat(i);
}
/*******************************************************************************
 * 函 数 名: Ht1621_BackL_On
 * 功能说明: 开启LCD背光
 * 形    参: void
 * 返 回 值: void
 ******************************************************************************/
//void Ht1621_BackL_On(void)
//{
//	GPIO_WriteLow(HT_PORT0,HT_CTR1);
//}
/*******************************************************************************
 * 函 数 名: Ht1621_BackL_Off
 * 功能说明: 关闭LCD背光
 * 形    参: void
 * 返 回 值: void
 ******************************************************************************/
//void Ht1621_BackL_Off(void)
//{
//	GPIO_WriteHigh(HT_PORT0,HT_CTR1);
//}


/*----------------------------------------------------------------------------*/

/*******************************************************************************
 * 函 数 名: Ht1621_Show_BAT
 * 功能说明: 根据电池电量显示电量标志
 * 形    参: bat: AD值
 * 返 回 值: void
 ******************************************************************************/
void Ht1621_Show_BAT(uint16_t bat)
{
	if(bat>600) Ht1621_Show_Bat(0x03);											//大于4V
	else if(bat>580) Ht1621_Show_Bat(0x02);										//大于3.8V
	else if(bat>560) Ht1621_Show_Bat(0x01);										//大于3.6V
	else Ht1621_Show_Bat(0x00);													//小于3.6V
}
/*******************************************************************************
 * 函 数 名: Ht1621_Show_All
 * 功能说明: 根据模式显示需显示的内容
 * 形    参: gam_mod: 模式
 * 返 回 值: void
 ******************************************************************************/
void Ht1621_Show_All(uint8_t gam_mod)
{
	switch(gam_mod)																// 模式不同,LCD显示的内容不同
	{
		case 0x00:
		{
		  	Htb_Ram.HTB_SEG.Seg_7_8.Lx = 1;//L3
			Htb_Ram.HTB_SEG.Seg_9_10.Lx = 1;//L4
			Htb_Ram.HTB_SEG.Seg_11_12.Lx = 1;//L5
			
			if(Gam_IsBegin)	
			{
			  	Ht1621_Show_Sco(Gam_Sco_Val);
				Ht1621_Show_One_Num(4,Gam_Err_Val,1);							// 错误次数
			}
			else
			{
			  	Ht1621_Show_Sco(Gam_Sco_[Gam_Spd_Val-1]);
				Ht1621_Show_One_Num(4,Max_Err_Tim[Gam_Spd_Val-1],1);			// 允许错误的最大次数
			}
			
			Ht1621_Show_One_Num(5,Gam_Spd_Val,1);								//当前关卡
		}break;
		case 0x01:
		{
		  	Htb_Ram.HTB_SEG.Seg_7_8.Lx = 1;//L3
			Htb_Ram.HTB_SEG.Seg_9_10.Lx = 1;//L4
			Htb_Ram.HTB_SEG.Seg_11_12.Lx = 0;//L5
			
			Ht1621_Show_Sco(Mod1_Sco_Val);
			
			Ht1621_Show_One_Num(4,Gam_Sud_Val,1);								//显示音效
			
			Ht1621_Show_One_Num(5,0,0);
		}break;
		case 0x02:
		{
		  	Htb_Ram.HTB_SEG.Seg_7_8.Lx = 1;//L3
			Htb_Ram.HTB_SEG.Seg_9_10.Lx = 1;//L4
			
			Ht1621_Show_Sco(Mod2_Sco_Val);
			
			Ht1621_Show_One_Num(4,Mode_OfPiano,1);								//显示音效
			if(Mode_OfPiano)
			{
				Ht1621_Show_One_Num(5,Which_Song,1);
				Htb_Ram.HTB_SEG.Seg_11_12.Lx = 1;//L5
			}
			else
			{
			  	Ht1621_Show_One_Num(5,Which_Song,0);
				Htb_Ram.HTB_SEG.Seg_11_12.Lx = 0;//L5
			}
		}break;
		case 0x03:
		{	
		  	Htb_Ram.HTB_SEG.Seg_7_8.Lx = 1;//L3
			Htb_Ram.HTB_SEG.Seg_9_10.Lx = 0;//L4
			Htb_Ram.HTB_SEG.Seg_11_12.Lx = 0;//L5
			
			Ht1621_Show_Sco(Slot_Sco_Val);//dijicizhongjiang
//			Ht1621_Show_Sco();
//			
 			Ht1621_Show_One_Num(4,0,0);
//			
//			Ht1621_Show_One_Num(5,Slot_Time,1);
		}break;
		default:break;
	}

	Ht1621_Show_Sud(Gam_Vol_Val);												// 音量显示
	
	Ht1621_write_all(0x00, (uint8_t *)&Htb_Ram.HTB_Ram[0x00],0x07);
	  
	if(!Bat_IsCharg)															// 没有充电时 显示电量
		Ht1621_Show_BAT(Battery_Val);
}
/*******************************************************************************
 * 函 数 名: Ht1621_Show_Sco
 * 功能说明: 根据模式显示需显示的内容
 * 形    参: gam_mod: 分数
 * 返 回 值: void
 ******************************************************************************/
void Ht1621_Show_Sco(uint16_t Sco_Val )
{
  	uint8_t gewei=0,shiwei=0,baiwei=0;
	
	baiwei = Sco_Val/100;
	shiwei = Sco_Val%100/10;
	gewei  = Sco_Val%10;
	
	
	if(baiwei==0)
	{
	  	if(shiwei==0)
		{
			Ht1621_Show_One_Num(1,baiwei,0);
			Ht1621_Show_One_Num(2,gewei,1);
			Ht1621_Show_One_Num(3,shiwei,0);
		}
		else
		{
			Ht1621_Show_One_Num(1,baiwei,0);
			Ht1621_Show_One_Num(2,shiwei,1);
			Ht1621_Show_One_Num(3,gewei,1);
		}
	}
	else
	{
		Ht1621_Show_One_Num(1,baiwei,1);
		Ht1621_Show_One_Num(2,shiwei,1);
		Ht1621_Show_One_Num(3,gewei,1);
	}
}
/*--------------Write-by-xiao-kai-2017-10-10-11-48----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/