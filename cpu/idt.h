#ifndef IDT_H
#define IDT_H

#include "../libc/type.h"

// Privilege level of the kernel code segment sleelctor for handling interrupts
#define KERNEL_CS 0x08

typedef struct {
    // lower 16 bits of handler function address
    uint16 low_offset;
    // defines what code segment selector
    uint16 sel;
    uint8 always0;
    /*
     * First byte
     * Bit 7: interrupt is present
     * Bits 6 - 5: Privilege level of caller (0=kernel...3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3 - 0: bits 1110 = decimal 14 = 32-bit interrupt gate
     */
    uint8 flags;
    // Higher 16 bits of handler funciton address
    uint16 high_offset;

    // __attribute__((packed)) tells the compiler to minimize padding so that each bit can be defined for what we need it to be defined for
} __attribute__((packed)) idt_gate_t;

// pointer to the array of interrupt handlers where asm instruction lidgt will read it
typedef struct {
    uint16 limit;
    uint32 base;
} __attribute__ ((packed)) idt_register_t;

#define IDT_ENTRIES 256

// Stores all entries to the idt which also contain the appropriate handler to each interrupt
idt_gate_t idt[IDT_ENTRIES];
// struct defined to register the IDT into the CPU
idt_register_t idt_reg;

void set_idt_gate(int n, uint32 handler);

void set_idt();

#endif
