#ifndef __DRIVER_TIMER_H__
#define __DRIVER_TIMER_H__

#include <stdint.h>

void cpu_delay(uint32_t us);

void SetTickInt(void);

#endif /* __DRIVER_TIMER_H__ */

