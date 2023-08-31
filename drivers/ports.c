
#include "ports.h"
#include <stdint.h>

// "=a"(result) means: put AL register in variable Result when finished
// "d" (port) means: load EDX with port

unsigned char inb(unsigned short port) {
    unsigned char result;
    // "=a"(result) means: put AL register in variable Result when finished
    // "d" (port) means: load EDX with port
    // in inline asm, dest and src registers are switched
    __asm__("in %%dx, %%al": "=a" (result) : "d" (port));
    return result;
}

// update the contents of the port
void outb(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx":: "a" (data), "d" (port));
}

// same is port_byte in but it returns short (2 bytes) instead of char (1 byte)
unsigned short inw(unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%al": "=a" (result): "d" (port));
    return result;
}

void outw(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx":: "a" (data), "d" (port));
}

