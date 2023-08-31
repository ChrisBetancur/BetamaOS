
#ifndef TYPE_H
#define TYPE_H

typedef unsigned int uint32;

typedef unsigned short uint16;

typedef unsigned char uint8;

#define low_16(address) (u16)(address & 0xffff)
#define high_16(address) (u16)(((address) >> 16) & 0xffff)

#endif
