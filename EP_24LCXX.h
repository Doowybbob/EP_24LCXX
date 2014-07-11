#include <Wire.h>

#define BUFFER_LENGTH 32
#define DATA_TOO_LONG 0xFF
#define DROPPED_BYTES 0xFE
#define WRITE_ERR 0xFD
#define READ_ERR 0xFC

class EEPROM24 {

	private:
		static uint8_t device;

	public:
		EEPROM24();
		EEPROM24(uint8_t);
		uint8_t writeEEPROM (uint16_t, uint8_t *, uint8_t);
		uint8_t readEEPROM (uint16_t, uint8_t *, uint8_t);
		
};
