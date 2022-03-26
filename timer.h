#ifndef TIMER_H
#define TIMER_H

#include "common.h"
#include "types.h"

extern uint64_t tick;

void init_timer(u32int frequency);
uint64_t millis();

#endif
