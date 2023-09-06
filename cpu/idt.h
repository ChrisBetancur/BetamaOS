#ifndef IDT_H
#define IDT_H

#include "../libc/types.h"


// Defines the value of the kernel code segment selecter to set the privilege level when handling interrupts
#define KERNEL_CS 0x08

typedef struct {
    // Lower 16 bits of handler function address
    u16 low_offset;
    u16 sel;
    u8 always0;
    /*
     * First byte
     * Bit 7: interrupt is present
     * Bits 6 - 5: Privilege level of caller (0=kernel...3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3 - 0: bits 1110 = decimal 14 = 32-bit interrupt gate
     */
    u8 flags;
    // Higher 16 bits of handler funciton address
    u16 high_offset;
} __attribute__((packed)) idt_gate_t; // __attribute__((packed)) tells the compiler to minimize padding so that each bit can be defined for what we need it to be defined for

// pointer to the array of interrupt handlers where asm intruction lidgt will read it
typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, u32 handler);
void set_idt();

#endif
