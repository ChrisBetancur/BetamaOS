
#include "ports.h"
#include <stdint.h>

// "=a"(result) means: put AL register in variable Result when finished
// "d" (port) means: load EDX with port

uint8_t inb(uint16_t port) {
    uint8_t output;
    __asm__("in %%dx, %%al": "=a" (output) : "d" (port));

    return output;
}

void outb(uint16_t port, uint8_t data) {
    __asm__("out %%al, %%dx" :: "a" (data), "d" (port));
}

uint16_t inw(uint16_t port) {
    uint16_t output;
    __asm__("in %%dx, %%al": "=a" (output) : "d" (port));

    return output;
}

void outw(uint16_t port, uint8_t data) {
    __asm__("out %%al, %%dx" :: "a" (data), "d" (port));
}
