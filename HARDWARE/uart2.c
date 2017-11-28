
#include "uart2.h"

void Uart_Init(void)
{
    UART2_DeInit();																// �����ʣ�115200��8λ�ֳ���1λֹͣλ //��У�顢ͬ��ģʽ��ֹ���������
    UART2_Init((uint32_t)115200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, \
	  	  UART2_PARITY_NO, UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);  
//  UART2_ITConfig(UART1_IT_RXNE_OR,ENABLE);   									// �������ݼĴ����ǿջ���������ж�
    UART2_Cmd(ENABLE);  														// ���ô���  UART1_IT_RXNE
}

void UART2_SendByte(uint8_t data)
{
    UART2_SendData8((uint8_t)data);
    /* Loop until the end of transmission */
    while (UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET);
}

void UART2_SendString(uint8_t* Data,uint16_t len)
{
    uint16_t i=0;
    for(;i<len;i++)
    	UART2_SendByte(Data[i]);
}

uint8_t UART2_ReceiveByte(void)
{
    uint8_t USART2_RX_BUF; 
    while (UART2_GetFlagStatus(UART2_FLAG_RXNE) == RESET);
    USART2_RX_BUF=UART2_ReceiveData8();
    return  USART2_RX_BUF;
}
/*--------------Write-by-xiao-kai-2017-09-11-10-00----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/