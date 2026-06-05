#include <string.h>
#include "stm32f4xx.h"
#include "usart_desc.h"
#include "driver_usart.h"

void usart_init(usart_desc_t usart)
{
	if (usart == NULL)
		return;
	
	USART_InitTypeDef USART_InitStructure;
	USART_StructInit(&USART_InitStructure);
	
	USART_InitStructure.USART_BaudRate = usart->BaudRate;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = usart->StopBits;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	
	
	GPIO_PinAFConfig(GPIOA, usart->PinSource_1, usart->AF_usart);
	GPIO_PinAFConfig(GPIOA, usart->PinSource_2, usart->AF_usart);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = usart->Pin;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	USART_Init(usart->USARTx, &USART_InitStructure);   
  USART_Cmd(usart->USARTx, ENABLE);
}

void usart_write(usart_desc_t usart, const char str[])
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		USART_ClearFlag(usart->USARTx, USART_FLAG_TC);
		USART_SendData(usart->USARTx, str[i]);
		while (USART_GetFlagStatus(usart->USARTx, USART_FLAG_TC) == RESET);
	}
}

uint8_t usart_get_data(usart_desc_t usart)
{
		// wait for usart received data
		USART_ClearFlag(usart->USARTx, USART_FLAG_RXNE);
		while (USART_GetFlagStatus(usart->USARTx, USART_FLAG_RXNE) == RESET);		
		// read data from usart register
	  uint8_t rdata = (uint8_t)USART_ReceiveData(usart->USARTx);
		return rdata;
}
