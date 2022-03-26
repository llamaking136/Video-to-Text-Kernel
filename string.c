#include "string.h"

char* strconv(uint32_t num, int base) {
	static char Representation[] = "0123456789ABCDEF";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = Representation[num % base];
		num /= base;
	} while (num != 0);
	return (ptr);
}

uint32_t strlen(char* str) {
	uint32_t i = 0;
	for (; str[i] != '\0'; i++);
	return i;
}

char *strncat(char *dest, char *src, uint32_t n) {
	uint32_t dest_length = strlen(dest);
	uint32_t i;

	for (i = 0; i < n && src[i] != '\0'; i++) {
		dest[dest_length + i] = src[i];
	}

	dest[dest_length + i] = '\0';

	return dest;
}

char *strcat(char *dest, char *src) {
	return strncat(dest, src, strlen(src));
}

void vsprintf(char *str, char *format, va_list arg) {
	unsigned int i;
	unsigned int ZERO = 0;
	char *s;

	int position = 0;

	while (*format) {

		if (*format == '%') {
			format++;
			switch (*format) {
			case 'c':
				i = va_arg(arg, int);
				str[position] = i;
				position++;
				break;

			case 'd':
				i = va_arg(arg, int);
				if (i < ZERO) {
					i = -i;
					str[position] = '-';
				}
				strcat(str, strconv(i, 10));
				position += strlen(strconv(i, 10));

				break;

			case 'o':
				i = va_arg(arg, unsigned int);
				strcat(str, strconv(i, 8));
				position += strlen(strconv(i, 8));
				break;

			case 's':
				s = va_arg(arg, char *);
				strcat(str, s);
				position += strlen(s);
				break;

			case 'x':
				i = va_arg(arg, unsigned int);
				strcat(str, strconv(i, 16));
				position += strlen(strconv(i, 16));
				break;

			default:
				str[position] = '%';
				position++;
				break;
			}
		}

		else {
			str[position] = *format;
			position++;
		}

		format++;
	}
}
