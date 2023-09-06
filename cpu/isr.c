#include "isr.h"
#include "idt.h"
#include "../drivers/graphics.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "../drivers/ports.h"

isr_t interrupt_handlers[256];

// responsible to set up all 32 gates
void isr_install() {
    // used the prototype definitions to pass as the handler
    set_idt_gate(0, (u32)isr0);
    set_idt_gate(1, (u32)isr1);
    set_idt_gate(2, (u32)isr2);
    set_idt_gate(3, (u32)isr3);
    set_idt_gate(4, (u32)isr4);
    set_idt_gate(5, (u32)isr5);
    set_idt_gate(6, (u32)isr6);
    set_idt_gate(7, (u32)isr7);
    set_idt_gate(8, (u32)isr8);
    set_idt_gate(9, (u32)isr9);
    set_idt_gate(10, (u32)isr10);
    set_idt_gate(11, (u32)isr11);
    set_idt_gate(12, (u32)isr12);
    set_idt_gate(13, (u32)isr13);
    set_idt_gate(14, (u32)isr14);
    set_idt_gate(15, (u32)isr15);
    set_idt_gate(16, (u32)isr16);
    set_idt_gate(17, (u32)isr17);
    set_idt_gate(18, (u32)isr18);
    set_idt_gate(19, (u32)isr19);
    set_idt_gate(20, (u32)isr20);
    set_idt_gate(21, (u32)isr21);
    set_idt_gate(22, (u32)isr22);
    set_idt_gate(23, (u32)isr23);
    set_idt_gate(24, (u32)isr24);
    set_idt_gate(25, (u32)isr25);
    set_idt_gate(26, (u32)isr26);
    set_idt_gate(27, (u32)isr27);
    set_idt_gate(28, (u32)isr28);
    set_idt_gate(29, (u32)isr29);
    set_idt_gate(30, (u32)isr30);
    set_idt_gate(31, (u32)isr31);

    // remapping the PICs by reinitialising them
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);

    // Install the IRQs
    set_idt_gate(32, (u32)irq0);
    set_idt_gate(33, (u32)irq1);
    set_idt_gate(34, (u32)irq2);
    set_idt_gate(35, (u32)irq3);
    set_idt_gate(36, (u32)irq4);
    set_idt_gate(37, (u32)irq5);
    set_idt_gate(38, (u32)irq6);
    set_idt_gate(39, (u32)irq7);
    set_idt_gate(40, (u32)irq8);
    set_idt_gate(41, (u32)irq9);
    set_idt_gate(42, (u32)irq10);
    set_idt_gate(43, (u32)irq11);
    set_idt_gate(44, (u32)irq12);
    set_idt_gate(45, (u32)irq13);
    set_idt_gate(46, (u32)irq14);
    set_idt_gate(47, (u32)irq15);

    // load the IDT through asm
    set_idt();
}

void irq_install() {
    // enable interruptions
    __asm__ __volatile__("sti");
    init_timer(50);
    init_keyboard();
}

char *exception_messages[] = {
    EXCEPTION("Division By Zero"),
    EXCEPTION("Debug"),
    EXCEPTION("Non Maskable Interrupt"),
    EXCEPTION("Breakpoint"),
    EXCEPTION("Into Detected Overflow"),
    EXCEPTION("Out of Bounds"),
    EXCEPTION("Invalid Opcode"),
    EXCEPTION("No Coprocessor"),
    EXCEPTION("Double Fault"),
    EXCEPTION("Coprocessor Segment Overrun"),
    EXCEPTION("Bad TSS"),
    EXCEPTION("Segment Not Present"),
    EXCEPTION("Stack Fault"),
    EXCEPTION("General Protection Fault"),
    EXCEPTION("Page Fault"),
    EXCEPTION("Unknown Interrupt"),
    EXCEPTION("Coprocessor Fault"),
    EXCEPTION("Alignment Check"),
    EXCEPTION("Machine Check"),
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

// when call from asm, pusha and after push the ds to then form param r
void isr_handler(registers_t r) {
    kprint("received interrupt: ");
    char s[3];
    int_to_ascii(r.int_no, s);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r.int_no]);
    kprint("\n");
}

// puts the correct handler in the correct IRQ index
void register_interrupt_handler(u8 n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

// called from asm such that it sends the EOI signals indicating that interrupt has ended then we are able to call the appropariate function handling the interrupt
void irq_handler(registers_t r) {
    // value 40 correpsonds to interrupt 0 on the slave PIC
    // if this interrupt belonds to the slave PIC then send update the slave PIC port (oxa0) with the EOI signal (0x20)
    if (r.int_no >= 40)
        port_byte_out(0xa0, 0x20);

    // send signal to master by updating master PIC port (0x20)
    port_byte_out(0x20, 0x20);

    // handle the interrupt in a more modular way where the interrupt_handlers contains the pointers to the functions that should be called when the interrupt is called
    // such that isr_t handlers is the pointer to a function which should be the pointer to the correct handler for that interrupt
    // Therefore call handler
    if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}
