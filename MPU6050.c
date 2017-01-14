#include "MPU6050.h"
#include "i2c.h"

void SetRangeAccel(uint8_t range){		//you can choose 0-2g, 1-4g, 2-8g, 3-16g
	uint8_t data=0;
	if (range==0){data=0;}
	else if(range==1){data=0x08;}
	else if(range==2){data=0x10;}
	else if(range==3){data=0x18;}
	WriteRegisterI2C(ACCEL_CONF,data,MPU_adress);
}

uint16_t ReadAxisAccel(uint8_t axis){		//axis=0 -> x,axis=1 -> y, axis=2 -> z
	uint8_t Register=0;
	uint16_t Data=0;
	if(axis==0){Register=ACCEL_X_H;}
	else if(axis==1){Register=ACCEL_Y_H;}
	else if(axis==2){Register=ACCEL_Z_H;}
	else {return 0;}
	Data=ReadRegisterI2C(axis,MPU_adress,(MPU_adress+1));
	Data=Data<<8;
	Data+=ReadRegisterI2C((axis+1),MPU_adress,(MPU_adress+1));
	return Data;
}

uint16_t ReadTemperature(void){
	uint16_t Data=0;
	Data=ReadRegisterI2C(TEMP_H,MPU_adress,(MPU_adress+1));
	Data=Data<<8;
	Data+=ReadRegisterI2C(TEMP_L,MPU_adress,(MPU_adress+1));
	return Data;
}

