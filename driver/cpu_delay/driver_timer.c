#include "stm32f4xx.h"
#include "driver_timer.h"

void cpu_delay(uint32_t us)
{  
		while (us >= 1000)		
		{
			SysTick->LOAD = SystemCoreClock / 1000 - 1;
			SysTick->VAL = 0;
			SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
			while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
			SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
			us -= 1000;
		}
		
		if (us > 0)
		{
			SysTick->LOAD = (SystemCoreClock / 1000 / 1000) * us - 1;
			SysTick->VAL = 0;
			SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
			while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
			SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
		}
}
