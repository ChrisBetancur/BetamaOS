#ifndef MEMORY_H
#define MEMORY_H

#include "type.h"


void memcpy(char src[], char dest[], int size);

void memset(uint8 *dest, uint8 data, uint32 len);

uint32 kmalloc(uint32 size, int align, uint32 *phys_addr);

#endif
