#include "idt.h"
#include "../libc/types.h"

// BY USING STRUCTS, WE CAN GROUP THE NECESSARY BITS IN THE CORRECT ORDER SO THAT THE CPU CAN READ IT

// n defines the index of the entry/gate for the IDT
void set_idt_gate(int n, u32 handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;

    // Binary: 1 (Interrupt present) 00 (Kernel privilege level) 0 (0 for interrupt gates) 1110 (in decimal, 14 indicates 32-bit interrupt gate)
    idt[n].flags = 0x8e;
    idt[n].high_offset = high_16(handler);
}

// lods the IDT into the CPU so that CPU knows where to find the interrupt and exception handers when an interrupt occurs
void set_idt() {
    idt_reg.base = (u32) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}
