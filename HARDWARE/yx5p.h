
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
//������Ч3.579S
0x00	.\������Ч\����\����_0.mp3
0x01	.\������Ч\�ػ�\�ػ�_0.mp3
//����14.009S
0x02	.\����\Do.ogg
0x03	.\����\Re.ogg
0x04	.\����\Mi.ogg
0x05	.\����\Fa.ogg
0x06	.\����\So.ogg
0x07	.\����\La.ogg
0x08	.\����\Xi.ogg
//�ϻ���11.691S
0x09	.\�ϻ���\������Ч\�������_8.mp3
0x0A	.\�ϻ���\δ�н���Ч\��Ǯ_0.mp3
0x0B	.\�ϻ���\��ע��Ч\��ע_4.mp3
0x0C	.\�ϻ���\ҡ��ת����Ч\ת��_3.mp3
//������10.274S
0x0D	.\������\1������Чһ\����_8.mp3
0x0E	.\������\2������Ч��\����_1.wav
0x0F	.\������\3������Ч��\baby laugh 5.mp3
0x10	.\������\3������Ч��\baby laugh 6.mp3
0x11	.\������\4������Ч��\2987.wav
0x12	.\������\5������Ч��\5993.wav
0x13	.\������\5������Ч��\5994.wav
//�����9.212S
0x14	.\�����\Amazing\Amazing_1.mp3
0x15	.\�����\Cool\Cool_0.mp3
0x16	.\�����\Game Over\Game Over.mp3
0x17	.\�����\Good\Good_0.mp3
0x18	.\�����\Hit\Hit_1.wav
0x19	.\�����\Miss\ʧ��_2.mp3
0x1A	.\�����\NEW HIGH SCORE\New High Score.mp3
0x1B	.\�����\Ready Go\ready-go_0.mp3
0x1C	.\�����\Times Over\Time-s-Over_2.mp3
//48.765S
*/
//------------------+---------------------------------------------
//	  0x3C-->0x4B	|						��������ָ��
//----------------------------------------------------------------
//	  	 0x4C		|						ֹͣ����ָ��
//----------------------------------------------------------------
/*--------------Write-by-xiao-kai-2017-09-26-15-43----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/

