#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

#define asm __asm__ __volatile__

unsigned char inb(unsigned short port);

// update the contents of the port
void outb(unsigned short port, unsigned char data);

unsigned short inw(unsigned short port);

void outw(unsigned short port, unsigned char data);

#endif
