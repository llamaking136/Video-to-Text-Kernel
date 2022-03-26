#if !defined(STRING_H)
#define STRING_H

#include "types.h"
#include <stdarg.h>

char* strconv(uint32_t, int);
uint32_t strlen(char*);
char* strncat(char*, char*, uint32_t);
char* strcat(char*, char*);
void vsprintf(char*, char*, va_list);

#endif // STRING_H
