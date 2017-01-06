#ifndef MOJE_I2C_h
#define MOJE_I2C_h
#include "MKL25Z4.h"

void InitI2C(void);
void EnableI2C(void);
void DisableI2C(void);
void SendRestartI2C(void);
void MasterModeI2C(void);
void SlaveModeI2C(void);
void SendModeI2C(void);
void ReceiveModeI2C(void);
void DisableAckI2C(void);
uint8_t ReadByteI2C(void);
uint8_t BusyI2C(void);
uint8_t ReadRegisterI2C(uint8_t adres);
#endif
