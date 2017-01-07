#include "MKL25z4.h"
#include "i2c.h"

#define LedRed 0
#define LedGreen 1
const uint32_t LedMask[]={(1UL<<18),(1UL<<19),(1UL<<8)};
////////////////////////////////////////////////////////////////////////
//its simple example how to use transission i2c with accerometer on kl25z board
//we are reading only 1 axis and only accelometer
//////////////////////////////////////////////////////////////////////////////
void Wait(uint32_t value);


int main(void){
	uint16_t pomiar=0;
	SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[18] = PORT_PCR_MUX(1UL);
	PTB->PDDR|=LedMask[LedRed];			//red led
	PTB->PDDR|=LedMask[LedGreen];
	PTB->PSOR|=LedMask[LedRed];
	PTB->PSOR|=LedMask[LedGreen];
	InitI2C();
	while(1) {
		if(WaitForTap()==1){PTB->PTOR|=LedMask[LedGreen];}
		Wait(2000);
	}
	return 1;
}



void Wait(uint32_t value){
	uint32_t i;
	for(i=0;i<value;i++){__ASM("nop");}
}
