
#ifndef __GAM_MOD_0_H
#define __GAM_MOD_0_H

#include "stm8s_gpio.h"

void Gam_Mod_0(uint8_t Key_Val);

extern uint8_t NUM[3];	
extern BitStatus Gam_IsBegin;
extern uint8_t Gam_Vol_Val; 
extern uint8_t Gam_Spd_Val;
extern BitStatus Key_IsRight;
extern BitStatus Key_IsFault;
extern BitStatus Rand_Done;
extern uint8_t Delay_50MS;
extern uint8_t Gam_Sco_Val;														// ��Ϸ ����
extern uint8_t Gam_Err_Val;														// ��Ϸ �������
extern uint8_t Gam_Tim_Val;

#endif /* __GAM_MOD_0_H */
