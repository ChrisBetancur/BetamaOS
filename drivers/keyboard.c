#include "keyboard.h"
#include "../drivers/ports.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/type.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57
#define SC_PORT 0x60

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

static void keyboard_callback(registers_t r) {
    // PIC will leave the scan code in port 0x60
    uint8 scan_code = inb(SC_PORT);

    if (scan_code > SC_MAX)
        return;

    if (scan_code == BACKSPACE) {
        backspace(key_buffer);
        kprint_backspace();
    }
    else if (scan_code == ENTER) {
        kprint("\n");
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
