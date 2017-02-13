#include "uart.h"

void uart_init(){
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[1] = PORT_PCR_MUX(2);
	PORTA->PCR[2] = PORT_PCR_MUX(2);
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
	UART0->C4 |= UART0_C4_OSR(31);
	UART0->BDH = UART0_BDH_SBR(224);
	UART0->BDL = UART0_BDL_SBR(156);
	UART0->BDH &= ~(UART0_BDH_SBNS_MASK);
	UART0->C1 &= ~(UART0_C1_PE_MASK | UART0_C1_M_MASK);
	UART0->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);
}

void SendString(char tablica[]){
	uint8_t size=0;
	for(size=0;size<=16;size++){
		UART0->D=tablica[size];
		while((UART0->S1 & UART_S1_TDRE_MASK)==0){}
	}
}

uint8_t GetValue(void){
	char temp=0;
	while((UART0->S1 & UART_S1_RDRF_MASK)==0){}
	temp=UART0->D;
	UART0->D = temp;
	SendString("-\n\r");
	return temp;
}
