
#include "ports.h"
#include "../libc/type.h"

// "=a"(result) means: put AL register in variable Result when finished
// "d" (port) means: load EDX with port

uint8 inb(uint16 port) {
    uint8 result;
    // "=a"(result) means: put AL register in variable Result when finished
    // "d" (port) means: load EDX with port
    // in inline asm, dest and src registers are switched
    asm("in %%dx, %%al": "=a" (result) : "d" (port));
    return result;
}

// update the contents of the port
void outb(uint16 port, uint8 data) {
    asm("out %%al, %%dx":: "a" (data), "d" (port));
}

// same is port_byte in but it returns short (2 bytes) instead of char (1 byte)
uint16 inw(uint16 port) {
    uint16 result;
    asm("in %%dx, %%al": "=a" (result): "d" (port));
    return result;
}

void outw(uint16 port, uint8 data) {
    asm("out %%al, %%dx":: "a" (data), "d" (port));
}

