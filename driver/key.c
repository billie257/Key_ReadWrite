#include <stdbool.h>
#include "key_desc.h"
#include "key.h"


void key_init(key_desc_t key)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	
	  GPIO_StructInit(& GPIO_InitStruct);
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStruct.GPIO_PuPd = key->Pupd;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;	
	  GPIO_InitStruct.GPIO_Pin = key->Pin;
	  GPIO_Init(key->Port, &GPIO_InitStruct);	
}

uint8_t ReadInputKeyData(key_desc_t key)
{
	uint8_t data = GPIO_ReadInputDataBit(key->Port, key->Pin);
	return data;
}

bool CheckInput(uint8_t KeyData, key_desc_t key)
{
	bool isPressed = (KeyData == key->set);
	return isPressed;
}
