#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

void memcpy(char src[], char dest[], int size);

void memset(u8 *dest, u8 src, u32 len);

u32 kmalloc(u32 size, int align, u32 *phys_addr);

#endif
