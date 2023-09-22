#include "keyboard.h"
#include "../drivers/ports.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../shell/shell.h"
#include "../drivers/graphics.h"

#define BACKSPACE 0x0e
#define ENTER 0x1c

static char key_buffer[256];

#define SC_MAX 57

// defining scan codes
const char *sc_name[] = {
    "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
    "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
    "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
    "/", "RShift", "Keypad *", "LAlt", "Spacebar"
};

// defining scan codes in ascii
const char sc_ascii[] = {
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
    'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
    'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '
};

static void keyboard_callback(registers_t regs) {
    // PIC will leave the scancode in port 0x60
    u8 scan_code = port_byte_in(0x60);

    if (scan_code > SC_MAX)
        return;

    if (scan_code == BACKSPACE) {
        char empty[256];
        if (strcmp(key_buffer, empty) == 0) {
            return;
        }
        backspace(key_buffer);
        kprint_backspace();
    }
    else if (scan_code == ENTER) {
        kprint("\n");

        //handle_cmd(key_buffer);
        user_input(key_buffer);
        key_buffer[0] = '\0';
    }
    else {
        char letter = sc_ascii[(int) scan_code];

        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}
