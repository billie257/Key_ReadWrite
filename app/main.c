#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "driver_timer.h"

#define delay(ms) cpu_delay((ms) * 1000)

int main(void)
{
	  board_lowlevel_init();
	
    key_init(key1);
	  key_init(key2);
		key_init(key3);
	  
	  led_init(led1);
	  led_init(led2);
		
		usart_init(usart_1);
		
	  while(1)
		{
			led_off(led1);
			led_off(led2);
			
			static uint8_t key1_prev = 0;
      static uint8_t key2_prev = 0;
			
			uint8_t data1 = ReadInputKeyData(key1);
			delay(10);
			uint8_t isPressed1 = CheckInput(data1, key1);
			if (isPressed1 == 0x01 && key1_prev == 0)
			{			
				usart_write(usart_1, "Key1 pressed!\r\n");	
				delay(10);				
			}
			key1_prev = isPressed1;
			
			uint8_t data2 = ReadInputKeyData(key2);
			delay(10);
			uint8_t isPressed2 = CheckInput(data2, key2);
			if (isPressed2 == 0x01 && key2_prev == 0)
			{		
				usart_write(usart_1, "Key2 pressed!\r\n"); 
				delay(10);				
			}
			key2_prev = isPressed2;
		
		}
}
