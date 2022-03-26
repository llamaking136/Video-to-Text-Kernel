#include "common.h"
#include "isr.h"
#include "stdio.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8int n, isr_t handler, string name) {
	// printf("[ LOG ]: a new handler (%s, %d) has been issued\n", name, n);
	interrupt_handlers[n] = handler;
	if (interrupt_handlers[n]) {
		//  printf("[ LOG ]: handler (%s, %d) has been issued and added\n", name, n);
	} else {
		// panic("handler (%s, %d) was issued, but not added\n", name, n);
	}
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
	if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
	// Send an EOI (end of interrupt) signal to the PICs.
	// If this interrupt involved the slave.
	if (regs.int_no >= 40)
	{
		// Send reset signal to slave.
		outb(0xA0, 0x20);
	}
	// Send reset signal to master. (As well as slave, if necessary).
	outb(0x20, 0x20);

	if (interrupt_handlers[regs.int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}
