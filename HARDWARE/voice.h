
#ifndef __VOICE_H
#define __VOICE_H

#include "stm8s_gpio.h"

void NV20C_Init(void);

void Speak(uint8_t addr);

void Volume(uint8_t level);

BitStatus Isbusy(void);

void Repeat(void);

void Notone(void);

#endif /* __VOICE_H */
/*--------------Write-by-xiao-kai-2017-09-22-10-46----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/
//00H     :   ǰ��	
//01H     :   ������ע��	
//02H     :   ��ת����ע��	
//03H     :   ��ת����ע��		
//04H     :   ǰ�������ϰ���	
//05H     :   ��·��ͨ	
//06H     :   The car is driving forward.	
//07H     :   The car is driving backwards.	
//08H     :   The car is turning right.
//09H     :   The car is turning left.
//0AH     :   Not a Through Road!	