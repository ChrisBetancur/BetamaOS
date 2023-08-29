
#include "graphics.h"
#include <stdint.h>

// private functions definitions
int print_char(char character, int col, int row, char attrib);

int get_cursor();
void set_cursor(int offset);
int get_cursor_offset(int col, int row);
int get_cursor_row(int offset);
int get_cursor_col(int offset);

// Public functions

// printing in text mode
void kprint_at(char *str, int col, int row) {
    int offset;

    if (col >= 0 && row >= 0)
        offset = get_cursor_offset(col, row);
    else {
        // get the location where the cursor is currently at when row and col are less than 0
        offset = get_cursor();
        col = get_cursor_col(offset);
        row = get_cursor_row(offset);
    }

    int i = 0;

    while(str[i] != '\0') {
        offset = print_char(str[i], col, row);
        // after each print char then  the new cursor offset is set then get new row and col
        row = get_cursor_row(offset);
        col = get_cursor_col(offset);
    }
}

void kprint(char *str) {
    kprint_at(str, -1, -1);
}

void kprint_backspace(char *str) {
    int offset = get_cursor() - 2;
    int row = get_cursor_row(offset);
    int col = get_cursor_col(offset);

    print_char(0x08, col, row, WHITE_ON_BLACK);
}

void clear_screen();

// private functions

// printing in text mode
int print_char(char character, int col, int row, char attrib) {
     unsigned char *vidmem = (uint8_t*) VIDEO_ADDRESS;

     if (!attrib)
         attrib = WHITE_ON_BLACK;

     int offset;

     if (col >= 0 && row >= 0)
        offset = get_cursor_offset(col, row);
     else
        offset = get_cursor();

     if (character == '\n')
         offset = get_cursor_offset(col, row + 1);
     else if (character == 0x08) { // checks if the character being printed is a backspace
        vidmem[offset] = ' ';
        vidmem[offset + 1] = attrib;
     }
     else {
        vidmem[offset] = character;
        vidmem[offset + 1] = attrib;
        offset += 2
     }

     //offset = handle_scrolling(offset);

     set_cursor(offset);

     return offset;
}

// Cursor functions
int get_cursor() {
    outb(REG_SCREEN_CTRL, 14); // high byte of cursors offset
    int offset = inb(REG_SCREEN_DATA) << 8; // convert to high byte

    outb(REG_SCREEN_DATA, 15); // low byte of cursors offset
    offset += inb(REG_SCRENN_DATA);

    return offset * 2;
}

void set_cursor(int offset) {
    offset /= 2;

    outb(REG_SCREEN_CTRL, 14); // prep to set the new high byte
    outb(REG_SCREEN_DATA, (uint8_t) (offset >> 8));

    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, (uint8_t) (offset & 0xff));
}

// get cursor through the col and row of the cursor
int get_cursor_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int get_cursor_row(int offset) {
    return offset / (2 * MAX_COLS);
}

int get_cursor_col(int offset) {
    return (offset - (get_cursor_row(offset) * 2 * MAX_COLS)) / 2;
}
