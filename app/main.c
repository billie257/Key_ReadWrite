#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "driver_timer.h"

#define delay(ms) cpu_delay((ms) * 1000)

static void key_press_handler(key_desc_t key)
{
	  if (key == key1)
		{			
			static bool state = true;
			led_set(led1, state);
			state = !state;
		}
		else if (key == key2)
		{
			static bool state = true;
			led_set(led2, state);
			state = !state;
		}
    else
		{
		}	
}

static void usart_received_func(uint8_t data)
{
		switch (data)
		{
			case '1': 
			{
					static bool state = true;
					led_set(led1, state);
					state = !state;
					break;
			}
			case '2': 
			{
					static bool state = true;
					led_set(led2, state);
					state = !state; 
					break;
			}
			default: break;
		}
}


int main(void)
{
	  board_lowlevel_init();
	
    key_init(key1);
		key_init(key2);
		key_init(key3);
	  
	  led_init(led1);
	  led_init(led2);
		
		usart_init(usart_1);
	
	  key_press_callback_register(key1, key_press_handler);
	  key_press_callback_register(key2, key_press_handler);
	
	  usart_received_callback_register(usart_1, usart_received_func);
		
	  while(1)
		{
			;
		}
}
