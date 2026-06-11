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

static struct led_desc led1_desc = {GPIOF, GPIO_Pin_9, Bit_RESET, Bit_SET};
static struct led_desc led2_desc = {GPIOF, GPIO_Pin_10, Bit_RESET, Bit_SET};

led_desc_t led1 = &led1_desc;
led_desc_t led2 = &led2_desc;

static struct usart_desc usart1_desc = {USART1,GPIO_Pin_9 | GPIO_Pin_10, 115200u, 
																USART_StopBits_1, GPIO_PinSource9, 
																GPIO_PinSource10, GPIO_AF_USART1};

usart_desc_t usart_1 = &usart1_desc;

static struct key_desc key1_desc = {GPIOE, GPIO_Pin_4, GPIO_PuPd_UP, Bit_RESET};
static struct key_desc key2_desc = {GPIOE, GPIO_Pin_3, GPIO_PuPd_UP, Bit_RESET};
static struct key_desc key3_desc = {GPIOA, GPIO_Pin_0, GPIO_PuPd_DOWN, Bit_SET};

key_desc_t key1 = &key1_desc;
key_desc_t key2 = &key2_desc;
key_desc_t key3 = &key3_desc;

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
