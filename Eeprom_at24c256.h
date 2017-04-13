/*
Eeprom_at24c256.h - Library for AT24C256 IIC EEPROM.
*/
#ifndef Eeprom_at24c256_h
#define Eeprom_at24c256_h

#include "Arduino.h"
#include "Wire.h"

class Eeprom_at24c256
{
public:
	Eeprom_at24c256(int address);
	void write(unsigned  int writeAddress, byte* data, byte len);
	void read(unsigned  int readAdress, byte *buffer, byte len);
private:
	int _address;
};

#endif