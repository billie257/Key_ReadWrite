#ifndef __DRIVER_USART_H__
#define __DRIVER_USART_H__

#include <stdint.h>

struct usart_desc;
typedef struct usart_desc *usart_desc_t;

typedef void (*usart_received_func_t)(uint8_t data);

void usart_init(usart_desc_t usart);

void usart_write(usart_desc_t usart, const char str[]);

uint8_t usart_get_data(usart_desc_t usart);

void usart_received_callback_register(usart_desc_t usart, usart_received_func_t func);

#endif /* __DRIVER_USART_H__ */
