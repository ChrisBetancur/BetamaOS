#ifndef PORTS_H
#define PORTS_H

#include "../libc/type.h"

//#define asm __asm__ __volatile__

uint8 inb(uint16 port);

// update the contents of the port
void outb(uint16 port, uint8 data);

uint16 inw(uint16 port);

void outw(uint16 port, uint8 data);

#endif
