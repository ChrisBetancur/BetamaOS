#include "../drivers/graphics.h"
#include "../cpu/isr.h"
#include "../libc/type.h"

void main() {
    clear_screen();

    isr_install();
    irq_install();

    kprint("Type END to halt CPU...\n>");

}


void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU...\n");
        asm volatile("hlt");
    }
    else if (strcmp(input, "PAGE") == 0) {
        /*uint32 phys_addr;
        uint32 page = kmalloc(1, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");*/
    }

    kprint("Input: ");
    kprint(input);
    kprint("-\n>");
}
