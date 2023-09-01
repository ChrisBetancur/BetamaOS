#include "timer.h"
#include "../libc/type.h"
#include "isr.h"
#include "../drivers/ports.h"

uint32 tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
}

void init_timer(uint32 freq) {
    // sets the timer at IRQ0 which is the convention used therefore when interrupt 32 (IRQ0) is exectuted then timer_callback is executed since this function
    // is the handler function for this interrupt
    register_interrupt_handler(IRQ0, timer_callback);

    // get the put value: clock is set at 1193180 Hz
    // freq is the deisried interrupt frequence
    // the divisor represents the number of clock cycles that need to elapse before the timer triggers an interrupt
    // such that the timer counts down from an initial value (divisor) to 0 and when 0 is reached, the interrupt is generated then the value is once again is set to the initial value
    uint32 divisor = 1193180 / freq;
    // seperate high and lows of the divisor
    uint8 low = (uint8) (divisor & 0xff);
    uint8 high = (uint8) ((divisor >> 8) & 0xff);

    // send the command to the ports
    // command to set the mode of the PIT sent to port 0x43
    outb(0x43, 0x36);
    // low and highs are sent to port 0x40 to configure the timer frequency
    outb(0x40, low);
    outb(0x40, high);
}
