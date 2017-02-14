#include "MKL25z4.h"
#include "i2c.h"
#include "uart.h"
#include "MPU6050.h"
#include "pit.h"


#define PORTC_IRQn 
#define BUSCLOCK 24000000UL
#define LedRed 0
#define LedGreen 1
const uint32_t LedMask[]={(1UL<<18),(1UL<<19),(1UL<<8)};
////////////////////////////////////////////////////////////////////////
//its simple example how to use transission i2c with accerometer on kl25z board
//we are reading only 1 axis and only accelometer
//////////////////////////////////////////////////////////////////////////////
void Wait(uint32_t value);
void ledInit(void);
void InitInput(void);

void Recognise(uint32_t value){
	if(value<7000000){
		PTB->PTOR|=LedMask[LedRed];
	}
	else if(value>7000000 && value<20000000){
		PTB->PTOR|=LedMask[LedGreen];
	}
}

void code(void){
	char znak[16]="                ";
		if(PORTA->ISFR & (1UL<<1)){
			//PTB->PTOR|=LedMask[LedGreen];
			if(timer_on==0){
				PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
				timer_on++;
				SendString("timeron");
			  SendString("\n\r");
			}
			else {
				timer_value=120000000-PIT->CHANNEL[0].CVAL;
				PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
				timer_on=0;
				Recognise(timer_value);
				SendString("timeroff");
			  SendString("\n\r");
				sprintf(znak, "%d",timer_value);
		    SendString(znak);
		    SendString("\n\r");
			}
		}

}
void PORTA_IRQHandler(void){
		NVIC_ClearPendingIRQ(PORTA_IRQn);
		code();
		PORTA->ISFR=0xffffffff;
}


int main(void){
	uint16_t pomiar=0;
	float temp=0;
	char znak[16]="                ";
	ledInit();
	InitI2C();
	uart_init();
	SetRangeAccel(0); //+-2g
	MpuInit();
	MotionInit();
	InitInput();
	pitInit();
	
	
	SendString("MPU6050");

	while(1) {
		//pomiar=ReadAxisAccel(1);  //z axis
		//sprintf(znak, "%d",timer_value);
		//SendString(znak);
		//SendString("\n\r");
		//Wait(1000000);
	}
	return 1;
}



void Wait(uint32_t value){
	uint32_t i;
	for(i=0;i<value;i++){__ASM("nop");}
}

void ledInit(void){
	SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[18] = PORT_PCR_MUX(1UL);
	PORTB->PCR[19] = PORT_PCR_MUX(1UL);
	PTB->PDDR|=LedMask[LedRed];			//red led
	PTB->PDDR|=LedMask[LedGreen];
	PTB->PSOR|=LedMask[LedRed];
	PTB->PSOR|=LedMask[LedGreen];
}

void InitInput(void){
	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[1]|=PORT_PCR_MUX(1)|PORT_PCR_PE_MASK | PORT_PCR_IRQC(9);
	PORTA->PCR[1]&=~PORT_PCR_PS_MASK;
	PORTA->PCR[1]&=~PORT_PCR_PS_MASK;
	PTA->PDDR&=~(1UL<<1);
	NVIC_SetPriority(PORTA_IRQn,1);
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);
}
