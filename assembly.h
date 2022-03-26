#if !defined(ASSEMBLY_H)
#define ASSEMBLY_H

#include "common.h"

uint8_t inb(uint16_t);
uint32_t inl(uint16_t);
uint16_t inw(uint16_t);
void outb(uint16_t, uint8_t);
void outl(uint16_t, uint32_t);
void outw(uint16_t, uint16_t);
void sti();
void cli();
void hlt();
void hlt_loop();
void nop();

#endif // ASSEMBLY_HPP
