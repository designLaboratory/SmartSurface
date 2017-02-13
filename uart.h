#ifndef UART_h
#define UART_h
#include "MKL25Z4.h"

void uart_init(void);
void SendString(char tablica[]);
uint8_t GetValue(void);

#endif
