

#ifndef __UART1_H
#define __UART1_H

#include "stm8s_uart1.h"

void Uart_Init(void);

void UART1_SendByte(u8 data);

void UART1_SendString(u8* Data,u16 len);

u8 UART1_ReceiveByte(void);

#endif
/*--------------Write-by-xiao-kai\2017\05\06\17\14----QQ-850637704------------*/
/*-------------------------Always have a nice day-----------------------------*/