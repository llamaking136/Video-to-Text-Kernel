#if !defined(VGA_H)
#define VGA_H

#include <stdarg.h>
#include "types.h"
#include "common.h"

#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES
#define LINES 25

#define EOF -1

typedef enum colors {
	f_black,
	f_blue,
	f_green,
	f_cyan,
	f_red,
	f_magenta,
	f_brown,
	f_lgrey,
	f_dgrey,
	f_lblue,
	f_lgreen,
	f_lcyan,
	f_lred,
	f_lmagents,
	f_yellow,
	f_white
} colors;

extern uint16_t pos_x;
extern uint16_t pos_y;
extern uint16_t* vidmem;

void putchar(int8_t, colors, uint16_t, uint16_t);
void putc(int8_t, colors);
void printc(string, colors);
// void printl();
void printf(string, ...);
void clear();
void movecursor();
void screen_scroll_check();

#endif // VGA_H
