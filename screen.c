#include "screen.h"

uint16_t pos_x = 0;
uint16_t pos_y = 0;

uint16_t* vidmem = (uint16_t*)0xb8000;

void putchar(int8_t chr, colors col, uint16_t x, uint16_t y) {
	uint8_t attributeByte = (0 << 4) | (col & 0x0f);
	uint16_t attribute = attributeByte << 8;
	uint16_t *location;
	location = vidmem + (y*80 + x);
	*location = chr | attribute;
}

void putc(int8_t chr, colors col) {
	// screen_scroll_check(current_loc);
	// if (chr == '\n') {
	// 	printl();
	// 	// movecursor(current_loc);
	// 	return;
	// }
	// vidmem[(pos_y * 80 + pos_x) * 2] = chr;
	// vidmem[current_loc++] = col;
	// movecursor(amnt_chars++);

	if (pos_x >= 80) {
		pos_x = 0;
		pos_y ++;
	}

	if (chr == 0x08 && pos_x) {
		pos_x--;
	} else if (chr == 0x09) {
		pos_x = (pos_x+8) & ~(8-1);
	} else if (chr == '\r') {
		pos_x = 0;
	} else if (chr == '\n') {
		pos_x = 0;
		pos_y++;
	} else if (chr == '\b') {
		if (pos_x <= 0) {
			// goto pos_y_bell_beep;
			pos_y--;
		}
		// pos_x <= 0 ? (pos_y <= 0 ? bell_beep() : pos_y--) : pos_x--;
		// location = vidmem + (pos_y*80 + pos_x - 1);
		// *location = ' ' | attribute;
		putchar(' ', col, pos_x--, pos_y);
	} else if (chr >= ' ') {
		// location = vidmem + (pos_y*80 + pos_x);
		// *location = chr | attribute;
		putchar(chr, col, pos_x++, pos_y);
	}


	screen_scroll_check();
	movecursor();
}

void printc(const string str, colors col) {
	for (uint32_t i = 0; str[i] != '\0'; i++) { 
		/*
		if (str[i] == '\n') {   
			printl();
			break;
		}  
		vidmem[current_loc++] = str[i++];
		vidmem[current_loc++] = col;
		*/
		putc(str[i], col);
	}	
}

/*
void printl() {
	uint32_t line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc += (line_size - current_loc % (line_size));
	amnt_chars += (line_size - current_loc % (line_size)) / 2;
}
*/

void screen_scroll_check() {
	// if (position > SCREENSIZE / 2) {
	// 	// will use memcpy when i can figure out how to implement it..
	// 	clear();
	// }
	uint8_t attributeByte = (0 << 4) | (15 & 0x0f);
	uint16_t blank = 0x20 | (attributeByte << 8);

	if (pos_y >= 25) {
		int i;
		for (i = 0*80; i < 24*80; i++) {
			vidmem[i] = vidmem[i+80];
		}

		for (i = 24*80; i < 25*80; i++) {
			vidmem[i] = blank;
		}
		pos_y = 24;
	}	
}

void printf(string str, ...) {
	// printc(str, f_white);
	uint32_t i;
	char* s;
	
	colors current_color = f_white;

	va_list arg;
	va_start(arg, str);

	colors reset_color = f_white;

	while (*str) {
		if (*str == '%') { // formating chars
			str++;
			switch (*str) {
				case 'c':
					i = va_arg(arg, int);
					putc(i, current_color);
					break;
				case 'd':
					i = va_arg(arg, int);
					if (i < 0) {
						i = -i;
						putc('-', current_color);
					}
					printc(strconv(i, 10), current_color);
					break;
				case 's':
					s = va_arg(arg, char*);
					printc(s, current_color);
					break;
				case 'x':
					i = va_arg(arg, uint32_t);
					printc("0x", current_color);
					printc(strconv(i, 16), current_color);
					break;
				case 'o':
					i = va_arg(arg, uint32_t);
					printc(strconv(i, 8), current_color);
					break;
				defualt:
					putc('%', current_color);
			}
		} else if (*str == '\33') { // colors
			*str++;
			switch (*str) {
				case 'W':
					current_color = f_white;
					break;
				case 'R':
					current_color = f_red;
					break;
				case 'G':
					current_color = f_green;
					break;
				case 'B':
					current_color = f_blue;
					break;
				case 'r':
					current_color = reset_color;
					break;
				default:
					break;
			}
		} else { // basic chars
			putc(*str, current_color);
		}
		str++;
	}
}

void clear() {
	for (uint32_t i = 0; i < SCREENSIZE; i++) {
		vidmem[i++] = ' ';
		vidmem[i] = f_white;
	}
	pos_x = 0;
	pos_y = 0;
}

void movecursor() {
	uint16_t cursorLocation = pos_y * 80 + pos_x;
	outb(0x3D4, 14);
	outb(0x3D5, cursorLocation >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, cursorLocation);
	/*
	outb(0x3d4, 14);
	outb(0x3d5, (where >> 8) & 0xff);
	outb(0x3d4, 15);
	outb(0x3d5, where & 0xff);
	*/
}
