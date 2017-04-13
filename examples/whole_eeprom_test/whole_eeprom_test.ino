#include <Eeprom_at24c256.h>

//create eeprom at address 0x50
Eeprom_at24c256 eeprom(0x50);


/*
 * Testing whole EEPROM 
 * Written by Adam Jezek, April 14th, 2017
 * 
 * The EEPROM has 32kb of memory, that means 
 * 32 768 characters
 * As the Wire library has only 32b buffer, we will avoid reading/writing 
 * long messages. So we will divide the memory into 2048 fictional block,
 * each has 16 chars size.
 * 
 * WHAT THIS SKETCH DOES
 * ====================
 * First, we will print content of whole EEPROM. If you just bought it, 
 * you will propably see strange characters. Then, we will write into
 * each block it's number. The rest will be filled by # (you can change it
 * in the fillchar variable). When the writing is done, we will read it again. 
 * If you have enabled it for writing (pin 7 of EEPROM to GND) and it's not
 * corrupted (EEPROM hase only limited number of writings, this one has
 * one milion of writing cycles), each block should have the same value
 * as was printed during writing.
 * 
 * 
 * READ/WRITE FUNCTION PARAMETERS
 * =============================
 * Both read and write functions has 3 parameters - address, buffer and buffer size
 * Address could be number from range 0-32768 - it addresses every single char
 * As we decided to divide memory into blocks of 16, to read the first block,
 * we will use address 0. The following 16 chars will be readed (0-15).
 * To read second block, use address 16, and block 16-31 will be readed
 * 
 * Second parameter is buffer - char[]. During writing, data from buffer will be writed.
 * During readed, data will be saved in buffer. This means that read function returns nothing, but
 * saves the data into the given buffer.
 * 
 * Last parameter should be always sizeof(buffer). It tells the library how many characters should 
 * be readed/writed
 * 
 * The rest is explained in the code
 */
 
void setup()
{
  Serial.begin(115200);
  
  Serial.println("\n\nreading whole eeprom");
  Serial.println("32kb means 32768 characters");
  Serial.println("Wire library has 32b buffer, so we will only read 16 characters at once");
  Serial.println("32768/16 = 2048 blocks");
  delay(5000);
  
  for(int i = 0; i < 2048; i++){
    char message[16]; //buffer    
    //reading(address, buffer to read into, bytes to write(usually size of buffer))
    eeprom.read(i * 16, (byte *) message,sizeof(message));
   
    Serial.print(String(i)+"\t"); //print block address
    for(int z=0; z < 16;z++){
      
      Serial.print(message[z]); //print block content
    }
    Serial.println();   
  }


  String fillchar = "=";
  Serial.println("whole eeprom is printed above");
  Serial.println("to test it now, number of each block will be writen into it");
  Serial.println("the rest will be filled with"+fillchar);
  delay(2500);
  
  for(int i = 0; i < 2048; i++){
    
    //message to be writen to every block
    String writemessage = String(i);
    while(writemessage.length()<16){
      writemessage = writemessage + fillchar;
    }

    //buffer for writing
    char writebuffer[16];
    for(int x = 0; x < 16; x++){
      writebuffer[x] = writemessage[x]; //fill the buffer with message
    }   
    //writing(address, buffer to write from, bytes to write(usually size of buffer))
    eeprom.write(i*16, (byte*) writebuffer,sizeof(writebuffer));
    //it's not a good idea to write constantly
    //writing without delay usually corrupts data written during next writings
    delay(10);
    //print block number and what was written to it
    Serial.println(String(i) + "\t" + writemessage);   
   
  }

  Serial.println("DONE");
  Serial.println("Writing to eeprom finished");
  Serial.println("Now reading it again");
  delay(2500);

  for(int i = 0; i < 2048; i++){
    char message[16]; //buffer    
    //reading(address, buffer to read into, bytes to write(usually size of buffer))
    eeprom.read(i * 16, (byte *) message,sizeof(message));
   
    Serial.print(String(i)+"\t"); //print block address
    for(int z=0; z < 16;z++){
      
      Serial.print(message[z]); //print block
    }
    Serial.println();   
  }
}

void loop()
{
  
 
}