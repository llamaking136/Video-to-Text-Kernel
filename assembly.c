#include "assembly.h"

uint8_t inb(uint16_t port) {
	uint8_t r;
	asm volatile("inb %1, %0"
        : "=a"(r)
        : "Nd"(port));
	return r;
}

uint32_t inl(uint16_t port) {
	uint32_t ret;
    asm volatile("in %%dx,%%eax"
        : "=a"(ret)
        : "d"(port));
    return ret;
}

uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile("inw %1, %0" 
		: "=a" (ret) 
		: "dN" (port));
	return ret;
}

void outb(uint16_t port, uint8_t value) {
	asm volatile("outb %0, %1"
        :
        : "a"(value), "Nd"(port)
        :);
}

void outl(uint16_t port, uint32_t value) {
	asm volatile("out %%eax,%%dx" 
		:
		: "a"(value), "d"(port));	
}

void outw(uint16_t port, uint16_t value) {
	asm volatile("outw %%ax,%%dx"
        :
        : "dN"(port), "a"(value));	
}

void sti() {
	asm volatile("sti");
}

void cli() {
	asm volatile("cli");
}

void hlt() {
	asm volatile("hlt");
}

void hlt_loop() {
	for (;;) { hlt(); }
}

void nop() {
	asm volatile("nop");
}
