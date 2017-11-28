
#ifndef __GAM_MOD_0_H
#define __GAM_MOD_0_H

#include "stm8s_gpio.h"

extern uint8_t NUM[3];															// 随机数
extern uint8_t Gam_Spd_Val;														// 定义游戏速度
extern uint8_t Delay_50MS;
extern BitStatus Rand_Done;

void Create_Rand(void) ;

#endif /* __GAM_MOD_0_H */

