
#include "includes.h"

uint8_t Slot_Rand = 0xff;														// 老虎机随机数
uint8_t Gam_Sco_Val = 0x00;														// 游戏 分数
uint8_t Gam_Err_Val = 0x00;														// 游戏 错误次数
uint8_t Gam_Mod_Val = 0x00;														// 游戏 模式
uint8_t Gam_Sud_Val = 0x01;		 												// 游戏 音效
uint8_t Gam_Vol_Val = 0x01;														// 游戏 音量
uint8_t Gam_Tim_Val = 0x00;														// 游戏 模式
uint8_t Gam_Spd_Val = 0x01;														// 游戏 时间
uint8_t Mod_Key_Val = 0x00;														// 模式 键值
uint8_t Sud_Key_Val = 0x00;														// 速度 键值
uint8_t Com_Key_Val = 0x00;														// 普通 键值
uint16_t Power_Down = 0x00;														// 自动 关机
uint16_t Battery_Val = 0x00;													// 电池 电量
uint16_t Mod1_Sco_Val = 0x00;													// 泡泡 按下次数
uint16_t Mod2_Sco_Val = 0x00;													// 泡泡 按下次数
int16_t Slot_Sco_Val = 100;														// 老虎机初始分数
uint8_t dijicizhongjiang = 0xff;
BitStatus Gam_IsBegin = RESET;													// 打地鼠 开始?
BitStatus Bat_IsCharg = RESET;													// 正在 充电?
BitStatus Slot_IsBegin = RESET;													// 老虎机 开始?
BitStatus Mode_OfPiano = RESET;													// 钢琴 模式?
BitStatus Piano_IsBegin = RESET;												// 钢琴 模式?
uint8_t Mod0_Led_Flash = 0x00;
uint16_t Gam_Sco_[7] = {0};														// 存储关卡分数
const uint8_t Max_Err_Tim[8] = {6,6,7,7,8,8,9};									// 每个关卡允许错误的次数
const uint8_t Max_Rand_Tim[8] = {40,35,30,25,20,15,15,20};						// 每个关卡允许等待的时间，单位50ms

void main(void)
{
	Clk_Init();																	// 初始化 CLK
	Led_Init();																	// 初始化 LED
	Key_Init();																	// 初始化 KEY
	Iwdg_Init();																// 初始化 IWDG
	Tim2_Init();																// 初始化 TIM2
//	Tim3_Init();																// 初始化 TIM3
	Tim4_Init();																// 初始化 TIM4
	Adc1_Init();																// 初始化 ADC1
	Yx5p_Init();																// 初始化 VOICE
	Flash_Init();																// 初始化 FLASH
	Ht1621_Init();																// 初始化 HT1621
	delay_ms(350);																
	__enable_interrupt();														// 开中断
	Yx5p_Speak(0x00);															// 开机音效
	while(Yx5p_Isbusy());
	
	while(1)
	{
		/*-----------------------20ms-----------------------*/
		if(loop50HzFlag)//显示处理
		{
		  	loop50HzFlag = 0;
			/*---------------模式按键处理---------------*/
/*Mod_Key*/	Mod_Key_Val = Mod_Key_Scan();
			Mod_Key_Processes(Mod_Key_Val);
			/*---------------音效按键处理---------------*/
/*Sud_Key*/	Sud_Key_Val = Sud_Key_Scan();
			Sud_Key_Processes(Sud_Key_Val);
			/*---------------地鼠按键处理---------------*/
/*Com_Key*/	Com_Key_Val = Com_Key_Scan();
			Com_Key_Processes(Com_Key_Val);
			
			if(Com_Key_Val!=0xfe|Sud_Key_Val!=0|Mod_Key_Val!=0)					// 关机计数器清零
			  	Power_Down = 0;
		} 
		/*-----------------------25ms-----------------------*/
		if(loop40HzFlag)//显示处理
		{
			loop40HzFlag = 0;										
			Ht1621_Show_All(Gam_Mod_Val);										// 模式不同,LCD显示的内容不同
		} 
		/*-----------------------50ms-----------------------*/
		if(loop20HzFlag)//随机数处理
		{
			loop20HzFlag = 0;
			if(!Gam_Mod_Val)													// 打地鼠模式
			{
			  	if(Gam_IsBegin)
				{
					Create_Rand();												// 产生随机数

					if(Gam_Err_Val >= Max_Err_Tim[Gam_Spd_Val-1])
					{
					  	Gam_IsBegin = RESET;
						Gam_Tim_Val = 0;
					  	if(Gam_Vol_Val)
						{
							if(Gam_Sco_Val>Gam_Sco_[Gam_Spd_Val-1])				// 超过本关历史最高分
							{
								Yx5p_Speak(0x1a);								// New High Score
								Gam_Sco_[Gam_Spd_Val-1] = Gam_Sco_Val;
								Flash_Write_Word(Addr_temp[Gam_Spd_Val-1],Gam_Sco_[Gam_Spd_Val-1]);// 存储分数
							}
							else
							{
								if(Gam_Sco_Val>80)
									Yx5p_Speak(0x14);							// Amazing
								else if(Gam_Sco_Val>50)
									Yx5p_Speak(0x15);							// cool
								else if(Gam_Sco_Val>20)
									Yx5p_Speak(0x17);							// good
								else if(Gam_Sco_Val<20)
									Yx5p_Speak(0x16);							// Game Over
							}
						}
					}
				}
				else//打地鼠游戏没有开始时
				{
				  	GPIO_Write(GPIOB,0xfe);
				}
			}
			if(Mod_Key_Val!=0x03)												// 消除老虎机随机数可预测的BUG
			  	(void)rand();//Slot_Rand = 
		}
		/*-----------------------500ms----------------------*/
		if(loop2HzFlag)//充电处理
		{
		  	loop2HzFlag = 0;
			
			Battery_Val = Get_Adc1_Value(ADC1_CHANNEL_0);						// 电压检测
			
			if((BitStatus)GPIO_ReadInputPin(GPIOA,GPIO_PIN_1))
				  	Power_Down = 0;
			if(((BitStatus)GPIO_ReadInputPin(GPIOA,GPIO_PIN_1))&&				// 检测 USB是否插入
			   ((BitStatus)!GPIO_ReadInputPin(GPIOA,GPIO_PIN_3)))				// 检测6011是否工作
			{
				Bat_IsCharg = SET;
				Bat_Charging();
			}
			else
				Bat_IsCharg = RESET;
			
			Mod0_Led_Flash = (BitStatus)!Mod0_Led_Flash;
			//if(++Mod0_Led_Flash>=7) Mod0_Led_Flash = 0;
		}
		/*-----------------------1000ms---------------------*/
		if(loop1HzFlag)
		{
			loop1HzFlag = 0;
			
			if(++Power_Down>=214)
			{
			  	Flash_Write_Word(Addr_Sco_Slot,Slot_Sco_Val);
				Yx5p_Speak(0x01);												// 关机音效
				while(Yx5p_Isbusy());
				GPIO_WriteHigh(HT_PORT0,HT_LEDB);								// 背光断电
			  	GPIO_WriteLow(POWER_PORT,POWER_PIN);							// 长时间没有按键按下,断电休眠
			}
			
			if(!Gam_Mod_Val)
			{
			  	if(Gam_IsBegin)
				{
					if(++Gam_Tim_Val>=60) 										// 游戏时长
					{
					  	Gam_Tim_Val = 0;											
						Gam_IsBegin = RESET;									// 游戏结束
					  	if(Gam_Vol_Val)
						{
							if(Gam_Sco_Val>Gam_Sco_[Gam_Spd_Val-1])				// 超过本关历史最高分
							{
								Yx5p_Speak(0x1a);								// New High Score
								Gam_Sco_[Gam_Spd_Val-1] = Gam_Sco_Val;
								Flash_Write_Word(Addr_temp[Gam_Spd_Val-1],Gam_Sco_Val);		// 存储分数
							}
							else 
							{
								if(Gam_Sco_Val>80)
									Yx5p_Speak(0x14);							// Amazing
								else if(Gam_Sco_Val>50)
									Yx5p_Speak(0x15);							// cool
								else if(Gam_Sco_Val>20)
									Yx5p_Speak(0x17);							// good
								else
									Yx5p_Speak(0x1c);							// Time is over 
							}
						}
					}
				}
			}
		}
	}
}
/*--------------Write-by-xiao-kai-2017-08-18-14-18----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/
#ifdef USE_FULL_ASSERT 
void assert_failed(u8* file, u32 line)
{ 
  while (1)
  {
      
  }
}
#endif