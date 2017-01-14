#include "tap.h"
#include "i2c.h"



//////////////////////////////////////////////
//function return code of taps
//////////////////////////////////////////////
uint8_t WaitForTap(void){
	uint16_t measure_table[10];
	uint16_t base_value=0;
	uint16_t acc_value=0;
	uint32_t temp=0;
	for(temp=0;temp<10;temp++){measure_table[temp]=0;}
	//we have to measure base value from accelometer
	for(temp=0;temp<10;temp++){
		measure_table[temp]=(ReadRegisterI2C(0x05,0x3A,0x3B)<<8);		//z axis msb
		measure_table[temp]+=ReadRegisterI2C(0x06,0x3A,0x3B);				//z axis lsb
		measure_table[temp]/=4;
		base_value=base_value+measure_table[temp];
	}
	base_value=base_value/10;					//average
	while(1){
		for(temp=0;temp<10;temp++){
			measure_table[temp]=(ReadRegisterI2C(0x05,0x3A,0x3B)<<8);		//z axis msb
			measure_table[temp]+=ReadRegisterI2C(0x06,0x3A,0x3B);				//z axis lsb
			measure_table[temp]/=4;
			acc_value=acc_value+measure_table[temp];
		}
		acc_value=acc_value/10; 			//average
		if (base_value-acc_value>10){return 1;}			//single tap			IMPORTANT its sensitivity value
		//else {return 0;}
	}
	
	return ;
}
