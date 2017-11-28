
#ifndef __KEY_H
#define __KEY_H

#include "stm8s_gpio.h"

#define KEY_PORT_0		GPIOD
#define KEY_PORT_1		GPIOC

#define POWER_PORT		GPIOC
#define POWER_PIN		GPIO_PIN_7

#define Gam_Mod_Key		GPIO_PIN_2
#define Gam_Spd_Key		GPIO_PIN_0
#define Gam_Com_S1		GPIO_PIN_1
#define Gam_Com_S2		GPIO_PIN_2
#define Gam_Com_S3		GPIO_PIN_3
#define Gam_Com_S4		GPIO_PIN_4
#define Gam_Com_S5		GPIO_PIN_5
#define Gam_Com_S6		GPIO_PIN_6
#define Gam_Com_S7		GPIO_PIN_7


void Key_Init(void);

uint8_t Com_Key_Scan(void);

uint8_t Mod_Key_Scan(void);

uint8_t Sud_Key_Scan(void);

void Mod_Key_Processes(uint8_t mod_key);

void Sud_Key_Processes(uint8_t sud_key);

void Com_Key_Processes(uint8_t com_key);

#endif /* __KEY_H */
/*--------------Write-by-xiao-kai-2017-09-05-13-53----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/