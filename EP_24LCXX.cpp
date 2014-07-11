#include "EP_24LCXX.h"

uint8_t EEPROM24::device = 0;

EEPROM24::EEPROM24() {
	//initialize to default address
	device = 0x50;
	Wire.begin(device);
}

EEPROM24::EEPROM24( uint8_t addr) {
	// set device address and then start Wire lib
	device = addr;
	Wire.begin(device);
}

uint8_t EEPROM24::writeEEPROM (uint16_t addr, uint8_t * data, uint8_t len ) {
	uint8_t err;
	uint8_t counter;

	if (len > BUFFER_LENGTH)  // 32 (in Wire.h)
		return DATA_TOO_LONG;  // too long

	Wire.beginTransmission(device);
	Wire.write (addr >> 8);    // high order byte
	Wire.write (addr & 0xFF);  // low-order byte
	Wire.write (data, len);
	err = Wire.endTransmission ();
  
	if (err != 0)
		return WRITE_ERR;  // cannot write to device
    
	// Try ACK polling, described in datasheet.
	// eeprom wont send an ACK from a new request until
	// it's finished writing.
	for (counter = 0; counter < 100; counter++) {
		Wire.beginTransmission (device);
		Wire.write (addr >> 8);    // high order byte
		Wire.write (addr & 0xFF);  // low-order byte
		err = Wire.endTransmission ();
		if (err == 0)
			break;
    }
   
	return err;
 } 
  
uint8_t EEPROM24::readEEPROM (uint16_t addr, uint8_t * ret, uint8_t len ) {
	uint8_t err;
	uint8_t counter;

	//Make sure we wont overflow the Wire lib buffer
	if (len > BUFFER_LENGTH)  
		return DATA_TOO_LONG;  

	//Write the address that we're reading from
	Wire.beginTransmission (device);
	Wire.write (addr >> 8);    // high order byte
	Wire.write (addr & 0xFF);  // low-order byte
	err = Wire.endTransmission ();
  
	if (err != 0)
		return READ_ERR;  // cannot read from device
  
	// Read into Wire lib buffer
	Wire.requestFrom (device, len);

	// Read data from the Wire buffer and return
	for (counter = 0; counter < len; counter++) {
		if (Wire.available ()) 
			ret [counter] = Wire.read ();
		else
			return DROPPED_BYTES;  // did not get all bytes
    }
    
	return 0; 
} 