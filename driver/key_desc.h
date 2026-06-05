#ifndef __KEY_DESC_H__
#define __KEY_DESC_H__

#include "stm32f4xx.h"

struct key_desc
{
	 GPIO_TypeDef* Port;
	 uint16_t Pin;
	 GPIOPuPd_TypeDef Pupd;
	 BitAction set;
};

#endif /* __KEY_DESC_H__ */
