#include "MKL25z4.h"
#include "i2c.h"


////////////////////////////////////////////////////////////////////////
//its simple example how to use transission i2c with accerometer on kl25z board
//we are reading only 1 axis and only accelometer
//////////////////////////////////////////////////////////////////////////////
void Wait(uint32_t value);


int main(void){
	uint16_t pomiar=0;
	InitI2C();
	while(1) {
		pomiar=(ReadRegisterI2C(0x01)<<8);
		pomiar+=ReadRegisterI2C(0x02);
		pomiar/=4;												//here is the value from accelometer
		Wait(30000);
  }
	return 1;
}



void Wait(uint32_t value){
	uint32_t i;
	for(i=0;i<value;i++){__ASM("nop");}
}
