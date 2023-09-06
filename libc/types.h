
#ifndef TYPES_H
#define TYPES_H

// instead of using chars to allocate non-char bytes, these types will be used instead
typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef char s8;

// macros defined to get the high and low bits of an address
// any input of 32 bits, in this case the address, & 0xffff will get rid of the first 16 bits
#define low_16(address) (u16)(address & 0xffff)
#define high_16(address) (u16)(((address) >> 16) & 0xffff)

#endif
