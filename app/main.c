#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "driver_timer.h"

#define delay(ms) cpu_delay((ms) * 1000)

int main(void)
{
	  board_lowlevel_init();
		SetTickInt();
	  
	  led_init(led1);
	  led_init(led2);
	
	  usart_init(usart_1);
		
	  led_off(led1);
	  led_off(led2);

	  while (1)
		{
			;
		}		
}

void SysTick_Handler(void)
{
	static bool led_state = false;
	static int count = 0;
	
	if (++count >= 500)
	{
		 count = 0;
		 led_state = !led_state;
		 led_set(led1, led_state);
	}
}
