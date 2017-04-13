/*
Eeprom_at24c256.cpp - Library for AT24C256 IIC EEPROM.
*/

#include "Arduino.h"
#include "Wire.h"
#include "Eeprom_at24c256.h"

Eeprom_at24c256::Eeprom_at24c256(int address)
{	
	Wire.begin();
	_address = address;
}

void Eeprom_at24c256::write(unsigned  int writeAddress, byte* data, byte len)
{
	
	Wire.beginTransmission(_address);
	Wire.write((int)(writeAddress >> 8));
	Wire.write((int)(writeAddress & 0xFF));
	byte c;
	for (c = 0; c < len; c++)
		Wire.write(data[c]);
	Wire.endTransmission();
}

void Eeprom_at24c256::read(unsigned  int readAdress, byte *buffer, byte len)
{
	Wire.beginTransmission(_address);
	Wire.write((int)(readAdress >> 8));
	Wire.write((int)(readAdress & 0xFF)); 
	Wire.endTransmission();
	Wire.requestFrom(_address, len);
	int c = 0;
	for (c = 0; c < len; c++)
		if (Wire.available()) buffer[c] = Wire.read();
}