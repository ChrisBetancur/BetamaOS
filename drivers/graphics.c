#include "graphics.h"
#include "ports.h"
#include "../libc/string.h"
#include "../libc/mem.h"

// Private Kernel API functions

int print_char(char character, int col, int row, char attribute_byte);

int get_cursor();

void set_cursor_offset(int offset);

int get_cursor_offset(int col, int row);

int get_cursor_row(int offset);

int get_cursor_col(int offset);

int handle_scrolling(int offset);

void kprint(char* msg) {
    kprint_at(msg, -1, -1);
}

void kprint_at(char* msg, int col, int row) {
    int offset;

    if (col >= 0 && row >= 0) {
        offset = get_cursor_offset(col, row);
    }
    else {
        offset = get_cursor();
        row = get_cursor_row(offset);
        col = get_cursor_col(offset);
    }

    int i = 0;
    while (msg[i] != 0) {
        // get the offset of the next offset and inc the index
        offset = print_char(msg[i++], col, row, WHITE_ON_BLACK);
        // based on the new offset get the col and row
        col = get_cursor_col(offset);
        row = get_cursor_row(offset);
    }
}

void kprint_backspace() {
    int offset = get_cursor() - 2;
    int row = get_cursor_row(offset);
    int col = get_cursor_col(offset);
    // 0x08 is the backspace ascii
    print_char(0x08, col, row, WHITE_ON_BLACK);
}

// Princ char at location
int print_char(char character, int col, int row, char attrib_byte) {
    unsigned char* vidmem = (unsigned char*) VIDEO_ADDRESS;

    if (!attrib_byte)
        attrib_byte = WHITE_ON_BLACK;

    // get video memory offset for the screen location
    int offset;

    // if col and row are non negative use the for offset otherwise use the cursor location
    if (col >= 0 && row >=0) {
        offset = get_cursor_offset(col, row);
    }
    else {
        offset = get_cursor();
    }

    // if char is a newline char then set offset to the end of the current row so it will be advanced to the first col of the next row, otherwise, write the char and its attribute byte to video memoryat calcualted offset
    if (character == '\n') {
        row = get_cursor_row(offset);
        offset = get_cursor_offset(0, row + 1);

    }
    else if (character == 0x08) {
        vidmem[offset] = ' ';
        vidmem[offset + 1] = attrib_byte;
    }
    else {
        vidmem[offset] = character;
        vidmem[offset + 1] = attrib_byte;
        offset += 2;
    }

    offset = handle_scrolling(offset);


    set_cursor_offset(offset);

    return offset;
}

// device uses its control register as an index to select its internal registers which are
// reg 14: the high byte of the cursor's offset
// reg 15: which is the low byte of the cursor's offset
// once the internal register has been selected, we may read or write a byte on the data register.
int get_cursor() {
    // selects its internal reg 14, which corresponds to the high byte of the cursor's offset
    port_byte_out(REG_SCREEN_CTRL, 14);
    // Reads the high byte of the cursor's offset from the data register then converts it to a high byte
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    // select the reg 15 which is the low byte of the cursor's offset
    port_byte_out(REG_SCREEN_CTRL, 15);
    // reads the low byte of the cursor's offset
    offset += port_byte_in(REG_SCREEN_DATA);

    // Since the cursor offset reported by the VGA hardware is the number of chars, we multiply
    // by two to convert it to a char cell offset
    return offset * 2;
}

// we do not need to read data (port_byte_in) we need to update the cursor (port_byte_out)
void set_cursor_offset(int offset) {
    offset /= 2;

    // select reg 14 in charge of the high byte of the cursor's offset
    port_byte_out(REG_SCREEN_CTRL, 14);
    // set the new offset to the cursor's offset, shift 8 for the high byte
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset >> 8));

    // select reg 15 in charge of the low byte of the cursor's offset
    port_byte_out(REG_SCREEN_CTRL, 15);
    //set the new offset to the cursor's offset, and the offset to 0xff for the low byte
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset & 0xff));
}

int get_cursor_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int get_cursor_row(int offset) {
    return offset / (2 * MAX_COLS);
}

int get_cursor_col(int offset) {
    //return offset / (2 * get_screen_offset_row(offset) * MAX_COLS);
    return (offset - (get_cursor_row(offset) * 2 * MAX_COLS)) / 2;
}

int handle_scrolling(int offset) {
    if (offset < MAX_ROWS * MAX_COLS * 2) {
        return offset;
    }

    for (int i = 1; i < MAX_ROWS; i++) {
        mem_copy(get_cursor_offset(0, i) + VIDEO_ADDRESS, get_cursor_offset(0, i - 1) + VIDEO_ADDRESS, MAX_COLS * 2);
    }

    char* last_line = get_cursor_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;

    for (int i = 0; i < MAX_COLS * 2; i++) {
        last_line[i] = 0;
    }
    //kprint(last_line, 0, 0);

    offset -= 2 * MAX_COLS;

    return offset;
}

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    char* screen = VIDEO_ADDRESS;

    for (int i = 0; i < SCREEN_SIZE_T; i++) {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }

    set_cursor_offset(get_cursor_offset(0, 0));
}
