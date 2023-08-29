
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS = 25
#define MAX_COLS = 80
#define SCREEN_SIZE_T (MAX_ROWS * MAX_COLS)

#define SCREEN_WIDTH = 640
#define SCREEN_HEIGHT = 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)
#define WHITE_ON_BLACK 0x0F

// VGA I/O ports
#define REG_SCREEN_CTRL 0x3D4 // used to set the VGA screen (prep)
#define REG_SCREEN_DATA 0x3D4 // used to send data to VGA screen

// Text mode functions
void kprint_at(char *str, int col, int row);

void kprint(char *str);

void kprint_backspace(char *str);

void clear_screen();

// Graphics mode functions


#endif
