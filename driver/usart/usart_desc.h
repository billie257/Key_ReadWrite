#ifndef __USART_DESC_H__
#define __USART_DESC_H__

#include "stm32f4xx.h"
#include "driver_usart.h"

struct usart_desc
{
	USART_TypeDef* USARTx;
	uint16_t Pin;
	uint32_t BaudRate;
	uint16_t StopBits;
	uint16_t PinSource_1;
	uint16_t PinSource_2;
	uint8_t AF_usart;
	usart_received_func_t func;
};

#endif /* __USART_DESC_H__ */
