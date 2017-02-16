#include "pit.h"
#include "MKL25Z4.h"
#include "uart.h"

uint32_t starting_value=120000000; 	//przy 24mhz to ok 5s
uint32_t value100ms=0x249EFF;				//wartosc dla 100ms
uint8_t timer_on=0;
uint32_t timer_value=0;
//how to calcylate time?
//starting_value=time*clk_frq -1
////////////////////////////////////////////////////////
//inicjalizacja zegara pit
////////////////////////////////////////////////////////
void pitInit(void){
	SIM->SCGC6|=SIM_SCGC6_PIT_MASK;		//podlaczenie zegara
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;      //wlaczenie modulu
	PIT->MCR |= PIT_MCR_FRZ_MASK;			//zamrozenie timerow w debug mode
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_CHN_MASK;
	PIT->CHANNEL[0].LDVAL = starting_value;		//zaladowanie timera
	PIT->CHANNEL[1].TCTRL &= ~PIT_TCTRL_CHN_MASK;
	PIT->CHANNEL[1].LDVAL = starting_value;		//zaladowanie timera
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;		//wlaczenie przerwan
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;
	NVIC_SetPriority(PIT_IRQn, 2); // 0, 1, 2 or 3 priorytet
	NVIC_ClearPendingIRQ(PIT_IRQn); 
	NVIC_EnableIRQ(PIT_IRQn);
	__enable_irq();											//globalne przerwania
	PIT->MCR = 0x00;							//wlaczenie pit
}

void PIT_IRQHandler() {			//obsluga przerwan od timerow
	NVIC_ClearPendingIRQ(PIT_IRQn);
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK){		//przerwanie od kanalu 1
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
		PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
		timer_on=0;
		SendString("przerwanie pit");
					  SendString("\n\r");
	}
	else 	if (PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK){		//przerwanie od kanalu 2
				PIT->CHANNEL[1].TFLG &= PIT_TFLG_TIF_MASK;

	}

	
}
