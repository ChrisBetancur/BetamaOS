
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define SCREEN_SIZE_T (MAX_ROWS * MAX_COLS)

#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3d4 // I/O port address used to control the VGA screen
#define REG_SCREEN_DATA 0x3d5 // I/O port address used for sending data to the VGA screen

// public functions
void kprint_at(char* msg, int col, int row);

void kprint(char* msg);

void kprint_backspace();

void clear_screen();

#endif
