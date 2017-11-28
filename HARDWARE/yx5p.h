
#ifndef __YX5P_H
#define __YX5P_H

#include "stm8s_gpio.h"

#define YX5P_PORT0			GPIOC
#define YX5P_PORT2			GPIOE
#define YX5P_PORT1			GPIOA

#define YX5P_BUSY			GPIO_PIN_5
#define YX5P_DATA			GPIO_PIN_1
#define YX5P_CLK			GPIO_PIN_4

void Yx5p_Init(void);

void Yx5p_Speak(uint8_t addr);

void Yx5p_Volume(uint8_t level);

BitStatus Yx5p_Isbusy(void);

void Yx5p_Stop(void);

void Yx5p_V_Level(uint8_t lvl);

#endif /* __YX5P_H */

/*
//其它音效3.579S
0x00	.\其它音效\开机\开机_0.mp3
0x01	.\其它音效\关机\关机_0.mp3
//钢琴14.009S
0x02	.\钢琴\Do.ogg
0x03	.\钢琴\Re.ogg
0x04	.\钢琴\Mi.ogg
0x05	.\钢琴\Fa.ogg
0x06	.\钢琴\So.ogg
0x07	.\钢琴\La.ogg
0x08	.\钢琴\Xi.ogg
//老虎机11.691S
0x09	.\老虎机\开奖音效\倒金币声_8.mp3
0x0A	.\老虎机\未中奖音效\输钱_0.mp3
0x0B	.\老虎机\下注音效\下注_4.mp3
0x0C	.\老虎机\摇奖转盘音效\转盘_3.mp3
//按泡泡10.274S
0x0D	.\按泡泡\1泡泡音效一\泡泡_8.mp3
0x0E	.\按泡泡\2泡泡音效二\泡泡_1.wav
0x0F	.\按泡泡\3泡泡音效三\baby laugh 5.mp3
0x10	.\按泡泡\3泡泡音效三\baby laugh 6.mp3
0x11	.\按泡泡\4泡泡音效四\2987.wav
0x12	.\按泡泡\5泡泡音效五\5993.wav
0x13	.\按泡泡\5泡泡音效五\5994.wav
//打地鼠9.212S
0x14	.\打地鼠\Amazing\Amazing_1.mp3
0x15	.\打地鼠\Cool\Cool_0.mp3
0x16	.\打地鼠\Game Over\Game Over.mp3
0x17	.\打地鼠\Good\Good_0.mp3
0x18	.\打地鼠\Hit\Hit_1.wav
0x19	.\打地鼠\Miss\失误_2.mp3
0x1A	.\打地鼠\NEW HIGH SCORE\New High Score.mp3
0x1B	.\打地鼠\Ready Go\ready-go_0.mp3
0x1C	.\打地鼠\Times Over\Time-s-Over_2.mp3
//48.765S
*/
//------------------+---------------------------------------------
//	  0x3C-->0x4B	|						音量调节指令
//----------------------------------------------------------------
//	  	 0x4C		|						停止播放指令
//----------------------------------------------------------------
/*--------------Write-by-xiao-kai-2017-09-26-15-43----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/

