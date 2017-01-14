#include "MKL25Z4.h"


#ifndef MPU6050_h
#define MPU6050_h

#define MPU_adress  (0x68)		//everything is 8 bit data
#define ACCEL_X_H   (0x3B)
#define ACCEL_X_L   (0x3C)
#define ACCEL_Y_H		(0x3D)
#define ACCEL_Y_L		(0x3E)
#define ACCEL_Z_H   (0x3F)
#define ACCEL_Z_L   (0x40)
#define TEMP_H 			(0x41)
#define TEMP_L 			(0x42)
#define ACCEL_CONF  (0x1C)


void SetRangeAccel(uint8_t range);
uint16_t ReadAxisAccel(uint8_t axis);
uint16_t ReadTemperature(void);
#endif
