#include <Eeprom_at24c256.h>

Eeprom_at24c256 eeprom(0x50);
/*
 * FOR DETAILED INFORMATION ABOUT HOW THIS WORKS
 * VISIT whole_eeprom_test.ino SKETCH
 * IT COINTAINS EXPLANATION AND DOCUMENTATION
 */
void setup()
{
	Serial.begin(9600);
	char message[30]; //buffer
	Serial.println("now reading first 30 characters of eeprom at address 100");
	eeprom.read(100, (byte *) message, sizeof(message));
	Serial.println(message);

	Serial.println("write \"0123456789-eeprom-test\"(22 characters) to address 100");

	char writemessage[] = "0123456789-eeprom-test";
	eeprom.write(100, (byte*) writemessage, sizeof(writemessage));
	Serial.println("write done, reading");
	char readmessage[30];
	eeprom.read(100, (byte *) readmessage, sizeof(readmessage));
	Serial.println("readed:");
	Serial.println(readmessage);

	Serial.println("DONE");
}

void loop()
{
 
}