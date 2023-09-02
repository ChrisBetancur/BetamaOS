#include "isr.h"
#include "idt.h"
#include "../drivers/graphics.h"
#include "../drivers/ports.h"
#include "../libc/string.h"
#include "timer.h"
#include "../drivers/keyboard.h"

void isr_install() {
    set_idt_gate(0, (uint32)isr0);
    set_idt_gate(1, (uint32)isr1);
    set_idt_gate(2, (uint32)isr2);
    set_idt_gate(3, (uint32)isr3);
    set_idt_gate(4, (uint32)isr4);
    set_idt_gate(5, (uint32)isr5);
    set_idt_gate(6, (uint32)isr6);
    set_idt_gate(7, (uint32)isr7);
    set_idt_gate(8, (uint32)isr8);
    set_idt_gate(9, (uint32)isr9);
    set_idt_gate(10, (uint32)isr10);
    set_idt_gate(11, (uint32)isr11);
    set_idt_gate(12, (uint32)isr12);
    set_idt_gate(13, (uint32)isr13);
    set_idt_gate(14, (uint32)isr14);
    set_idt_gate(15, (uint32)isr15);
    set_idt_gate(16, (uint32)isr16);
    set_idt_gate(17, (uint32)isr17);
    set_idt_gate(18, (uint32)isr18);
    set_idt_gate(19, (uint32)isr19);
    set_idt_gate(20, (uint32)isr20);
    set_idt_gate(21, (uint32)isr21);
    set_idt_gate(22, (uint32)isr22);
    set_idt_gate(23, (uint32)isr23);
    set_idt_gate(24, (uint32)isr24);
    set_idt_gate(25, (uint32)isr25);
    set_idt_gate(26, (uint32)isr26);
    set_idt_gate(27, (uint32)isr27);
    set_idt_gate(28, (uint32)isr28);
    set_idt_gate(29, (uint32)isr29);
    set_idt_gate(30, (uint32)isr30);
    set_idt_gate(31, (uint32)isr31);

    // remapping the PICs by reinitialising them
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // Install the IRQs
    set_idt_gate(32, (uint32)irq0);
    set_idt_gate(33, (uint32)irq1);
    set_idt_gate(34, (uint32)irq2);
    set_idt_gate(35, (uint32)irq3);
    set_idt_gate(36, (uint32)irq4);
    set_idt_gate(37, (uint32)irq5);
    set_idt_gate(38, (uint32)irq6);
    set_idt_gate(39, (uint32)irq7);
    set_idt_gate(40, (uint32)irq8);
    set_idt_gate(41, (uint32)irq9);
    set_idt_gate(42, (uint32)irq10);
    set_idt_gate(43, (uint32)irq11);
    set_idt_gate(44, (uint32)irq12);
    set_idt_gate(45, (uint32)irq13);
    set_idt_gate(46, (uint32)irq14);
    set_idt_gate(47, (uint32)irq15);

    // load the IDT through asm
    set_idt();
}

void irq_install() {
    // enable interruptions
    asm volatile("sti");
    // initialize
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

void isr_handler(registers_t r) {
    kprint("received interrupt: ");
    char s[3];
    int_to_ascii(r.int_no, s);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r.int_no]);
    kprint("\n");
}

// handlers for each interrupt arranged based on the r.int_no
isr_t interrupt_handlers[256];

// puts the correct handler in the correct IRQ index
void register_interrupt_handler(uint8 n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

// called from asm such that it sends the EOI signals indicating that interrupt has ended then we are able to call the appropariate function handling the interrupt
void irq_handler(registers_t r) {
    // value 40 correpsonds to interrupt 0 on the slave PIC
    // if this interrupt belonds to the slave PIC then send update the slave PIC port (oxa0) with the EOI signal (0x20)
    if (r.int_no >= 40)
        outb(SLAVE_PIC, EOI_SIGNAL);

    // send signal to master by updating master PIC port (0x20)
    outb(MASTER_PIC, EOI_SIGNAL);

    // handle the interrupt in a more modular way where the interrupt_handlers contains the pointers to the functions that should be called when the interrupt is called
    // such that isr_t handlers is the pointer to a function which should be the pointer to the correct handler for that interrupt
    // Therefore call handler
    if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}
