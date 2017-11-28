

#ifndef __UART2_H
#define __UART2_H

#include "stm8s_uart2.h"

void Uart_Init(void);

void UART2_SendByte(uint8_t data);

void UART2_SendString(uint8_t* Data,uint16_t len);

uint8_t UART2_ReceiveByte(void);

#endif
/*--------------Write-by-xiao-kai-2017-09-11-10-00----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/