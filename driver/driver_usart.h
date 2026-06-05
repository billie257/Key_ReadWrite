#ifndef __DRIVER_USART_H__
#define __DRIVER_USART_H__

#include <stdint.h>

struct usart_desc;
typedef struct usart_desc *usart_desc_t;

void usart_init(usart_desc_t usart);

void usart_write(usart_desc_t usart, const char str[]);

uint8_t usart_get_data(usart_desc_t usart);

#endif /* __DRIVER_USART_H__ */
