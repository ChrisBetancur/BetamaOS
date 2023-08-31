
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define SCREEN_SIZE_T (MAX_ROWS * MAX_COLS)

#define WHITE_ON_BLACK 0x0f

// VGA I/O ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

// Text mode functions
void kprint_at(char *str, int col, int row);

void kprint(char *str);

void kprint_backspace();

void clear_screen();

// Graphics mode functions


#endif
