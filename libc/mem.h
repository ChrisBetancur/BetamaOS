#ifndef MEM_H
#define MEM_H

#include "types.h"

void mem_copy(char* src, char* dest, int num_bytes);

void mem_copy_at(char* src, char* dest, int start, int end);

void mem_set(u8 *dest, u8 val, u32 len);

u32 kmalloc(u32 size, int align, u32 *phys_addr);

#endif
