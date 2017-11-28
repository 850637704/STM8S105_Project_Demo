
#include "uart1.h"

void Uart_Init(void)
{
    UART1_DeInit();																//波特率：115200、8位字长、1位停止位 //无校验、同步模式禁止、允许接收
    UART1_Init((u32)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);  
//    UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);   									//接收数据寄存器非空或溢出错误中断
    UART1_Cmd(ENABLE);  														//启用串口  UART1_IT_RXNE
}

void UART1_SendByte(u8 data)
{
    UART1_SendData8((unsigned char)data);
    /* Loop until the end of transmission */
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}

//void UART1_SendString(u8* Data,u16 len)
//{
//    u16 i=0;
//    for(;i<len;i++)
//    UART1_SendByte(Data[i]);
//}
//
//u8 UART1_ReceiveByte(void)
//{
//    u8 USART1_RX_BUF; 
//    while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
//    USART1_RX_BUF=UART1_ReceiveData8();
//    return  USART1_RX_BUF;
//}
/*--------------Write-by-xiao-kai\2017\05\06\17\14----QQ-850637704------------*/
/*-------------------------Always have a nice day-----------------------------*/