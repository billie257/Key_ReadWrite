#ifndef __KEY_H__
#define __KEY_H__

#include <stdint.h>
#include <stdbool.h>

struct key_desc;
typedef struct key_desc *key_desc_t;

void key_init(key_desc_t key);

uint8_t ReadInputKeyData(key_desc_t key);

bool CheckInput(uint8_t KeyData, key_desc_t key);

#endif /* __KEY_H__ */
