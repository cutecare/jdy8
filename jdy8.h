/*
Part of http://cutecare.ru project
Author: evgeny.savitsky@gmail.com
*/

#ifndef JDY8_h
#define JDY8_h

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include <SoftwareSerial.h>

class JDY8 {
  public:
	  JDY8(int txPin = 3, int rxPin = 4, int resetPin = 5, int baud = 115200);
	  void configure(const char * bleName, int io1 = 0, int io2 = 0, int io3 = 0, int io4 = 0);
	  void setData(unsigned int minor = 0, unsigned int major = 0, short humidity = 0, short temperature = 0, short battery = 0, bool autosleep = true);
	  void major(unsigned int value, bool autosleep = true);
	  void minor(unsigned int value, bool autosleep = true);
	  void humidity(short value, bool autosleep = true);
	  void temperature(short value, bool autosleep = true);
	  void battery(short value, bool autosleep = true);

  private:
	  void sendCommand(const SoftwareSerial * bleSerial, const char * data);
	  void wakeUpBLE();

	  int bleTxPin = 0;
	  int bleRxPin = 0;
	  int bleResetPin = 0;
	  int bleBaud = 0;
};

#endif
