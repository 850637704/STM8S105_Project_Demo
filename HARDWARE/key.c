
#include "key.h"
#include "yx5p.h"
#include "flash.h"
#include "ht1621.h"
#include <stdlib.h>
#include "Gam_Mod_0.h"
#include "Gam_Mod_1.h"
#include "Gam_Mod_2.h"
#include "Gam_Mod_3.h"

uint8_t Slot_Time	= 0x00;
extern uint8_t Win_Rate;
extern uint8_t Slot_Time;
extern uint8_t Gam_Tim_Val;
extern uint8_t Gam_Mod_Val;
extern uint16_t Mod1_Sco_Val;
extern uint16_t Mod2_Sco_Val;
extern uint16_t Slot_Sco_Val;
extern uint16_t Slot_Sco_Val1;
extern BitStatus Slot_IsBegin;
extern BitStatus Mode_OfPiano;
extern uint8_t dijicizhongjiang;
extern BitStatus If_Slot_Sco_Val_X_0;

#define key_state_0        0   													// 按键的初始状态
#define key_state_1        1   													// 按键按下的状态
#define key_state_2        2   													// 按键释放的状态

/*******************************************************************************
 * 函 数 名: Key_Init
 * 功能说明: 按键端口初始化
 * 形    参: void
 * 返 回 值: void
 ******************************************************************************/
void Key_Init(void)
{
	GPIO_Init(KEY_PORT_0,(GPIO_Pin_TypeDef)(Gam_Com_S1|Gam_Com_S2|Gam_Com_S3|\
	  		Gam_Com_S4|Gam_Com_S5|Gam_Com_S6|Gam_Com_S7),GPIO_MODE_IN_PU_NO_IT);// 地鼠		按键
	GPIO_Init(KEY_PORT_0,Gam_Spd_Key,GPIO_MODE_IN_PU_NO_IT);					// 速度调节 按键
	GPIO_Init(KEY_PORT_1,Gam_Mod_Key,GPIO_MODE_IN_FL_NO_IT);					// 游戏模式 按键
	
	GPIO_Init(POWER_PORT,POWER_PIN,GPIO_MODE_OUT_PP_HIGH_SLOW);					// 电源 按键
}
/*******************************************************************************
 * 函 数 名: Com_Key_Scan
 * 功能说明: 检测按键,并返回按键值,bit0 用来标识长短按键,不同与单个按键,
													这里读取的是多个IO口的电平值
 * 形    参: void
 * 返 回 值: 键值
 ******************************************************************************/
uint8_t Com_Key_Scan(void)
{
	static uint8_t key_state0 = 0;     											// 按键的状态
	static uint8_t key_count0 = 0;     											// 按键计数器
	uint8_t key_press = 0xfe;       											// 按键是否被按下
	uint8_t key_return = 0xfe;  												// 按键返回值
	
	key_press = (uint8_t)GPIO_ReadInputData(KEY_PORT_0)&0xfe;        			// 读按键I/O电?
	
	switch (key_state0)
	{
		case key_state_0:                 										// 按键初始态
			if (0xfe!=key_press)
			{
				key_state0 = key_state_1;										// 键被按下，状态转换到键确认态
			}
		break;
		case key_state_1:                   									// 按键确认态
			if (0xfe!=key_press)
			{
				key_return = key_press;         								// 按键仍按下，按键确认输出为“1”
				key_state0 = key_state_2;										// 状态转换到键释放态
			}
			else
			{
				key_state0 = key_state_0; 										// 按键已抬起，转换到按键初始态
			}
		break;
		case key_state_2:
			if (0xfe==key_press) 												// 按键已释放，转换到按键初始态
			{
				key_return = (key_count0>25)?key_press|0x01: key_press&0xfe;	// 500ms长按键
				
				key_state0 = key_state_0;
				key_count0 = 0;
			}
			else if(0xfe!=key_press)
			{
				key_count0++;
			}
		break;
	}
	return key_return;                            								// 返回按键值
}
/*******************************************************************************
 * 函 数 名: Mod_Key_Scan
 * 功能说明: 扫描模式功能键
 * 形    参: void
 * 返 回 值: 键值
 ******************************************************************************/
uint8_t Mod_Key_Scan(void)
{
	static uint8_t key_state1 = 0;     											// 按键的状态
	static uint8_t key_count1 = 0;     											// 按键计数器
	BitStatus key_press = RESET;       											// 按键是否被按下
	uint8_t key_return = 0;  													// 按键返回值
	
	key_press = (BitStatus)!GPIO_ReadInputPin(KEY_PORT_1,Gam_Mod_Key);        	// 读按键I/O电?
	
	switch (key_state1)
	{
		case key_state_0:                 										// 按键初始态
			if (RESET==key_press)
			{
				key_state1 = key_state_1;										// 键被按下，状态转换到键确认态
			}
		break;
		case key_state_1:                   									// 按键确认态
			if (RESET==key_press)
			{
				key_state1 = key_state_2;										// 状态转换到键释放态
			}
			else
			{
				key_state1 = key_state_0; 										// 按键已抬起，转换到按键初始态
			}
		break;
		case key_state_2:
			if (SET==key_press) 												// 按键已释放，转换到按键初始态
			{
				key_return = (key_count1>25)? 2 : 1;							// 500ms长按键
				
				key_state1 = key_state_0;
				key_count1 = 0;
			}
			else if(RESET==key_press)											// 按键没有释放
			{
				key_count1++;
			}
		break;
	}
	return key_return;
}
/*******************************************************************************
 * 函 数 名: Sud_Key_Scan
 * 功能说明: 扫描速度功能键,0,表示 未按;1,表示 短按;2,表示 长按;//3,表示 超长按;
 * 形    参: void
 * 返 回 值: 键值
 ******************************************************************************/
uint8_t Sud_Key_Scan(void)
{
	static uint8_t key_state2 = 0;     											// 按键的状态
	static uint8_t key_count2 = 0;     											// 按键计数器
	BitStatus key_press = SET;       											// 按键是否被按下
	uint8_t key_return = 0;  													// 按键返回值
	
	key_press = (BitStatus)GPIO_ReadInputPin(KEY_PORT_0,Gam_Spd_Key);        	// 读按键I/O电?
	
	switch (key_state2)
	{
		case key_state_0:                 										// 按键初始态
			if (RESET==key_press)
			{
				key_state2 = key_state_1;										// 键被按下，状态转换到键确认态
			}
		break;
		case key_state_1:                   									// 按键确认态
			if (RESET==key_press)
			{
				key_state2 = key_state_2;										// 状态转换到键释放态
			}
			else
			{
				key_state2 = key_state_0; 										// 按键已抬起，转换到按键初始态
			}
		break;
		case key_state_2:
			if (SET==key_press) 												// 按键已释放，转换到按键初始态
			{			
				key_return = (key_count2>25)? 2 : 1;							// 500ms长按键
				
				key_state2 = key_state_0;
				key_count2 = 0;
			}
			else if(RESET==key_press)											// 按键没有释放
			{
				key_count2++;
			}
		break;
	}
	return key_return;
}
/*******************************************************************************
 * 函 数 名: Mod_Key_Processes
 * 功能说明: 模式按键处理函数
 * 形    参: mod_key 键值
 * 返 回 值: void
 ******************************************************************************/
void Mod_Key_Processes(uint8_t mod_key)
{
	switch(mod_key)
	{
		/*-----------------短按表示模式切换----------------*/
		case 0x01:
		{
			if(++Gam_Mod_Val>=4) Gam_Mod_Val = 0;								// Gam_Mod: 0 - 3
			/*进行模式切换前记得保存相关的数据，比如得分etc.*/
			Ht1621_Show_Mod(Gam_Mod_Val);
			switch(Gam_Mod_Val)													// 模式之间的切换需要初始化
			{
				case 0x00: // 模式 1  打地鼠 模式
				{
				  	if(Slot_Sco_Val1!=0)
					{
					  	if(If_Slot_Sco_Val_X_0 == RESET)
						{
							Slot_Sco_Val = Slot_Sco_Val + Slot_Sco_Val1;
							Slot_Sco_Val1 = 0;
						}
						else
						{
							If_Slot_Sco_Val_X_0 = RESET;
							Slot_Sco_Val1 = 0;
						}
					}
					Gam_IsBegin = RESET;										// 游戏切换到打地鼠模式	
					Gam_Tim_Val = 0;											// 游戏 时长 清零	
					Gam_Sco_Val = 0;											// 游戏 得分 清零
					Gam_Err_Val = 0;											// 错误 次数 清零
				}break;
				case 0x01: // 模式 2  按泡泡 模式
				{
				  	Mod1_Sco_Val = 0;
					Gam_Mod_tmp0 = 0xfe;										// 还未按下的泡泡
					GPIO_Write(GPIOB,0x00);										// LED 全亮 				
				}break;
				case 0x02: // 模式 3  弹钢琴 模式
				{
				  	Mod2_Sco_Val = 0;
					GPIO_Write(GPIOB,0xfe);										// LED 全灭
				}break;
				case 0x03: // 模式 4  老虎机 模式
				{
					Gam_Mod_tmp1 = 0xfe;
					GPIO_Write(GPIOB,0xfe);										// LED 全灭
				}break;
				default:{}break;
			}
			Flash_Write_Byte(Addr_Mod_Val,Gam_Mod_Val);							// 存储当前模式
		}break;
		/*-----------------长按表示开关机------------------*/
		case 0x02:
		{
		  	
			if(Slot_Sco_Val1!=0)
			{
			  	if(If_Slot_Sco_Val_X_0 == RESET)
				{
					Slot_Sco_Val = Slot_Sco_Val + Slot_Sco_Val1;
					Slot_Sco_Val1 = 0;
				}
				else
				{
					If_Slot_Sco_Val_X_0 = RESET;
					Slot_Sco_Val1 = 0;
				}
			}
			Flash_Write_Word(Addr_Sco_Slot,Slot_Sco_Val);
			Yx5p_Speak(0x01);
			while(Yx5p_Isbusy());
			GPIO_WriteHigh(HT_PORT0,HT_LEDB);									// 背光断电
			GPIO_WriteLow(POWER_PORT,POWER_PIN);
		}break;
		default:{}break;
	}
}
/*******************************************************************************
 * 函 数 名: Sud_Key_Processes
 * 功能说明: 声音按键处理函数
 * 形    参: sud_key 键值
 * 返 回 值: void
 ******************************************************************************/
void Sud_Key_Processes(uint8_t sud_key)
{
	switch(sud_key)
	{
		case 0x01:{																// 短按	
			/* 音效切换 */
			switch(Gam_Mod_Val)
			{
				case 0x00:
				{
					if(Gam_IsBegin)
					  	Gam_IsBegin = (BitStatus)!Gam_IsBegin;
				}break;
				case 0x01:
				{
				  	if(++Gam_Sud_Val>=6) Gam_Sud_Val = 1;						// Gam_Sud: 1 - 5
					Talk(Gam_Sud_Val,0xf6);
					Flash_Write_Byte(Addr_Sud_Val,Gam_Sud_Val);					// 存储当前音效
				}break;
				case 0x02:
				{
					Mode_OfPiano = (BitStatus)!Mode_OfPiano;
					Flash_Write_Word(Addr_Pio_Mod,Mode_OfPiano);				//
					GPIO_Write(GPIOB,0xfe);										// 熄灭所有LED
					Yx5p_Speak(0xC4);											// 停止播放
				}break;
				case 0x03:
				{
				  	if(Gam_Mod_tmp1!=0xfe)
					{
				  		if(!Slot_IsBegin)
						{
							Slot_IsBegin = SET;
							Slot_Time += 1;
							//根据Sud_Key按下次数，也就是玩老虎机的次数来控制一下是否中奖
							if(Slot_Time == Win_Rate)//每Win_Rate次至少中奖一次,当有多个下注时，在已经下注中随机抽取一个为中奖号码
							{
							  	Slot_Time = 0;
								dijicizhongjiang = rand()%Win_Rate;
							}
						}
					}
				}break;
				default:{}break;
			}
		}break;
		case 0x02:{																// 长按（调音效）
			/* 音量切换 */
			if(++Gam_Vol_Val>=4) Gam_Vol_Val = 0;								// Gam_Vol: 0 - 3
			Yx5p_V_Level(Gam_Vol_Val);
			Yx5p_Speak(0x0b);													// 音量提示
			Flash_Write_Byte(Addr_Vol_Val,Gam_Vol_Val);							// 存储当前音量
		}break;
		default:{}break;
	}
}
/*******************************************************************************
 * 函 数 名: Com_Key_Processes
 * 功能说明: 地鼠按键处理函数
 * 形    参: com_key 键值
 * 返 回 值: void
 ******************************************************************************/
void Com_Key_Processes(uint8_t com_key)
{
	switch(Gam_Mod_Val)
	{
		case 0x00:Gam_Mod_0(com_key);break;
		case 0x01:Gam_Mod_1(com_key);break;
		case 0x02:Gam_Mod_2(com_key);break;
		case 0x03:Gam_Mod_3(com_key);break;
		default:break;
	}
}
/*--------------Write-by-xiao-kai-2017-09-19-09-47----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/
