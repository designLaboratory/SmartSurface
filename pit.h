
#ifndef pit_h
#define pit_h
#include "MKL25Z4.h"

extern uint8_t timer_on;
extern uint32_t timer_value;
void pitInit(void);
void PIT_IRQHandler(void); 

#endif
