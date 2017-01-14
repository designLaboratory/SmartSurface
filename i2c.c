#include "i2c.h"
uint8_t adres_ukladu=0x1D; 
void InitI2C(void){
  SIM->SCGC5  |= SIM_SCGC5_PORTE_MASK;  // Wlaczenie zegara dla portu E
  SIM->SCGC4  |= SIM_SCGC4_I2C0_MASK;   // Wlaczenie zegara dla modulu I2C0
  
  PORTE->PCR[25] = PORT_PCR_MUX(5) |\
                  PORT_PCR_DSE_MASK;    //PTE25 (I2C1_SDA)
  PORTE->PCR[24] = PORT_PCR_MUX(5) |\
                  PORT_PCR_DSE_MASK;    //PTE24 (I2C1_SCL)

  I2C0->F   = 0x14;                     // baudrate: 300kHz
  I2C0->C1 |= I2C_C1_IICEN_MASK;        // Wlaczenie I2C0
}

void EnableI2C(void){
	I2C0->C1 |= I2C_C1_IICEN_MASK; //wlaczenie modulu
}
 
void DisableI2C(void){
	I2C0->C1 &= ~I2C_C1_IICEN_MASK; //wylaczenie modulu
}
 
void SendRestartI2C(void){
	I2C0->C1 |= I2C_C1_RSTA_MASK;		//wyslanie sygnalu restart
} 

void MasterModeI2C(void){
	I2C0->C1 |= I2C_C1_MST_MASK;		//tryb master
}

void SlaveModeI2C(void){
	I2C0->C1 &= ~I2C_C1_MST_MASK;   //tryb slave
}

void SendModeI2C(void){
	I2C0->C1 |= I2C_C1_TX_MASK; 	//tryb nadawania
}

void ReceiveModeI2C(void){
	I2C0->C1 &= ~I2C_C1_TX_MASK;   //tryb odbioru
}
void DisableAckI2C(void){
	I2C0->C1 |= I2C_C1_TXAK_MASK;		//w trybie odbioru wylaczamy ACK czyli na koniec wysylamy NACK
}

uint8_t ReadByteI2C(void){
	return I2C0->D;
}

uint8_t BusyI2C(void){
	while((I2C0->S & I2C_S_IICIF_MASK)==0){}	//czekamy na przerwanie
	if(I2C0->S & I2C_S_RXAK_MASK){return 0;}
	I2C0->S |= I2C_S_IICIF_MASK;               // Wyzerowanie flagi przerwania
  return 1;
}
void SendByteI2C(uint8_t dane){		//wysylamy bajta
	I2C0->D=dane;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///  wartstwa wyzej
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t ReadRegisterI2C(uint8_t reg,uint8_t adress1,uint8_t adress2){
	uint8_t dane=0;
	EnableI2C();
	MasterModeI2C();
	SendModeI2C();
	SendByteI2C(adress1);		//default 0x3a
	BusyI2C();
	SendByteI2C(reg);			//rejestr ktory chcemy odczytac
	BusyI2C();
	SendRestartI2C();
	SendByteI2C(adress2);		//default 0x3b
	BusyI2C();
	ReceiveModeI2C();
	DisableAckI2C();
	dane=ReadByteI2C();
	BusyI2C();
	SlaveModeI2C();
	ReceiveModeI2C();
	dane=ReadByteI2C();  //wlasciwy odczyt
	DisableI2C();
	return dane;
}

void WriteRegisterI2C(uint8_t reg, uint8_t data,uint8_t adress){
	SendModeI2C();
	SendModeI2C();
	MasterModeI2C();
	SendByteI2C(adress);	//adres slave default 0x3a
	BusyI2C();
	SendByteI2C(reg);		
	BusyI2C();
	SendByteI2C(data);
	BusyI2C();
	SlaveModeI2C();
	ReceiveModeI2C();
	DisableI2C();	
}
















