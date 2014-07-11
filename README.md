# README #

EP_24LCXX is an Arduino library that provides basic functionality for reading and writing to 
the EERPROM. The library uses the Arduino Wire library for i2c communication with the 
EEPROM. 

Version 0.0.1

### How do I get set up? ###

Download the source from GitHub and place the downloaded EP_24LCXX folder in your
Arduino/libraries/ directory. If the Arduino IDE is running, you will have to 
restart the IDE to see the EP_24LCXX library in the IDE.

To add it to your sketch go to:
Sketch->Import Library...->EP_24LCXX
The Wire library is also required so add it as well by going to:
Sketch->Import Library...->Wire

### Usage ###

Declare a new EEPROM24 object:

```
EEPROM24 eeprom;
```

This will create a new EEPROM24 object with a default i2c address for the eeprom chip: 0x50. 
To provide a specific address use:

```
EEPROM eeprom (address); //where address is the i2c address of the chip
```

To determine the address of your 24LCXX chip use the values you set for the A2, A1, A0 pins:
Address: 01010A2A1A0
So is all address pins are tied to LOW or GND the address would be 0b01010000 or 0x50 (default);

Using the EEPROM24 object, write or read from the 24LCXX chip.

Writing:

```
eeprom.writeEEPROM(addr, data, len);
```

Where,<br>
addr is a 16 bit address to write to within memory.<br>
data is a pointer to the data that should be written to memory.<br>
len is the number of bytes that data will use in memory.<br>
		
Reading:

```
eeprom.readEEROM(aadr, ret, len);
```

Where,<br>
addr is a 16 bit address to read from within memory.<br>
ret is a pointer to a variable that will hold the data read from memory.<br>
len is the number of bytes that should be read from memory.<br>



