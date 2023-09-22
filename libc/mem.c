#include "mem.h"
#include "../drivers/graphics.h"

void mem_copy(char* src, char* dest, int num_bytes) {
    for (int i = 0; i < num_bytes; i++) {
        dest[i] = src[i];
    }
}

// will copy char at index end
void mem_copy_at(char* src, char* dest, int start, int end) {
    for (int i = start; i <= end; i++) {
        dest[i - start] = src[i];
    }
}

void mem_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8*) dest; // pointer to the base of the dest

    for ( ; len != 0; len--)
        *temp++ = val;
}

// init var to base addr 0x10000 indicating the starting point of available memory for allocation which will be updated each time kmalloc is used
u32 free_mem_addr = 0x10000;

u32 kmalloc(u32 size, int align, u32 *phys_addr) {
    // if the page is not aligned to a page boundary 0xfffff000 and align is 1 then
    if (align == 1 && (free_mem_addr & 0xfffff000)) {
        // align the address by value then add 0x1000
        // 0xfffff000 is used as the page boundary since it represents the last address within a 4kb page where in most systems memory is divided in 4 kb pages
        free_mem_addr &= 0xfffff000;
        free_mem_addr += 0x1000;
    }

    // if the pointer is provided, assign the free_mem_addr to it
    if (phys_addr)
        *phys_addr = free_mem_addr;

    // store the current val to the ret var
    u32 ret = free_mem_addr;
    // set the free_mem_addr to the next available spot for the next value hence += size since the value will occupy size
    free_mem_addr += size;

    // return ret
    return ret;
}
