#include <stdio.h>
#include "stm32f4xx.h"
#include "led_desc.h"
#include "led.h"
#include "usart_desc.h"
#include "driver_usart.h"
#include "key_desc.h"
#include "key.h"

// LED1: PF9
// LED2: PF10

// #################### LED define #################### 
static struct led_desc led1_desc = {GPIOF, GPIO_Pin_9, Bit_RESET, Bit_SET};
static struct led_desc led2_desc = {GPIOF, GPIO_Pin_10, Bit_RESET, Bit_SET};

led_desc_t led1 = &led1_desc;
led_desc_t led2 = &led2_desc;

// KEY1: PE4
// KEY2: PE3
// KEY3: PA0

// ####################  key define  #################### 
#define KEY_DEFINE(n, PORT, PIN, IRQn) \
static struct key_desc _key##n = \
{\
		.port = GPIO##PORT, \
		.pin = GPIO_Pin_##PIN, \
		.exti_port_src = EXTI_PortSourceGPIO##PORT, \
		.exti_pin_src = EXTI_PinSource##PIN, \
		.exti_line = EXTI_Line##PIN, \
		.irqn = IRQn, \
};\
key_desc_t key##n = &_key##n
KEY_DEFINE(1, E, 4, EXTI4_IRQn);
KEY_DEFINE(2, E, 3, EXTI3_IRQn);
KEY_DEFINE(3, A, 0, EXTI0_IRQn);

// ####################  usart define  #################### 
static struct usart_desc usart1_desc = {USART1,GPIO_Pin_9 | GPIO_Pin_10, 115200u, 
																USART_StopBits_1, GPIO_PinSource9, 
																GPIO_PinSource10, GPIO_AF_USART1};

usart_desc_t usart_1 = &usart1_desc;

void board_lowlevel_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
}

int fputc(int ch, FILE* stream)
{
	 (void)stream;
	
		USART_ClearFlag(USART1, USART_FLAG_TC);
		USART_SendData(USART1, (uint16_t)ch);		
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	
		return ch;  
}

void EXTI4_IRQHandler(void)
{
	 if (key1->func != NULL)
	 {
		   key1->func(key1);
	 }
	 EXTI_ClearITPendingBit(EXTI_Line4);
}

void EXTI3_IRQHandler(void)
{
	 if (key2->func != NULL)
	 {
		   key2->func(key2);
	 }
		EXTI_ClearITPendingBit(EXTI_Line3);	 
}
	
void EXTI0_IRQHandler(void)
{
	if (key3->func != NULL)
	 {
		   key3->func(key3);
	 }
	 EXTI_ClearITPendingBit(EXTI_Line0);
}

void USART1_IRQHandler(void)
{
		if (USART_GetITStatus(usart_1->USARTx, USART_IT_RXNE) != RESET)
		{
			 if (usart_1->func != NULL)
			 {
					uint8_t data = USART_ReceiveData(usart_1->USARTx);
				  usart_1->func(data);
			 }
			 
			 USART_ClearITPendingBit(usart_1->USARTx, USART_IT_RXNE);
		}		
}
