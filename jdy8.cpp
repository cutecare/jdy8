/*
Part of http://cutecare.ru project
Author: evgeny.savitsky@gmail.com
*/
#include "jdy8.h"

/**
 * Constructor
 */
JDY8::JDY8(int txPin = 3, int rxPin = 4, int resetPin = 5, int baud = 115200, int io1Pin = 6, int io2Pin = 7, int io3Pin = 8, int io4Pin = 9)
{
	bleTxPin = txPin;
	bleRxPin = rxPin;
	bleResetPin = resetPin;
	bleBaud = baud;
	bleIO1Pin = io1Pin;
	bleIO2Pin = io2Pin;
	bleIO3Pin = io3Pin;
	bleIO4Pin = io4Pin;
}

void JDY8::configure(const char * bleName, int io1 = 0, int io2 = 0, int io3 = 0, int io4 = 0)
{
	pinMode(bleTxPin, OUTPUT);
	
	SoftwareSerial bleSerial(bleRxPin, bleTxPin);
	bleSerial.begin(bleBaud);
	
	sendCommand(&bleSerial, "AT+RESTORE");
	delay(500);

	char text[64] = "";
	sprintf(text, "AT+NAME%s", bleName);
	sendCommand(&bleSerial, text);

	sendCommand(&bleSerial, "AT+HOSTEN3");
	sendCommand(&bleSerial, "AT+CLSSE0");
	sendCommand(&bleSerial, "AT+RST");
	sendCommand(&bleSerial, "AT+POWR0");      // max RF power
	sendCommand(&bleSerial, "AT+ADVEN1");     // advertising enabled
	sendCommand(&bleSerial, "AT+ADVIN1");     // setup advertising interval
	sendCommand(&bleSerial, "AT+PWMOPEN0");   // turn off PWM
	sendCommand(&bleSerial, "AT+RTCOPEN0");   // disable RTC
	
	sprintf(text, "AT+PIO1%d", io1);
	sendCommand(&bleSerial, text);
	sprintf(text, "AT+PIO2%d", io2);
	sendCommand(&bleSerial, text);
	sprintf(text, "AT+PIO3%d", io3);
	sendCommand(&bleSerial, text);
	sprintf(text, "AT+PIO4%d", io4);
	sendCommand(&bleSerial, text);

	pinMode(bleTxPin, INPUT);
}

void JDY8::setData(unsigned int minor = 0, unsigned int major = 0, short humidity = 0, short temperature = 0, short battery = 0, bool autosleep = true)
{
	pinMode(bleTxPin, OUTPUT);
	wakeUpBLE();

	SoftwareSerial bleSerial(bleRxPin, bleTxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+MAJOR%04X", major);
	sendCommand(bleSerial, buff);
	sprintf(buff, "AT+MINOR%04X", minor);
	sendCommand(bleSerial, buff);
	sprintf(buff, "AT+HUMID%02X", humidity);
	sendCommand(bleSerial, buff);
	sprintf(buff, "AT+TEMP%02X", temperature);
	sendCommand(bleSerial, buff);
	sprintf(buff, "AT+BATT%02X", battery);
	sendCommand(bleSerial, buff);
	if (autosleep) {
		sendCommand(bleSerial, "AT+SLEEP1");
	}

	pinMode(bleTxPin, INPUT);
}

void JDY8::major(unsigned int value, bool autosleep = true)
{
	pinMode(bleTxPin, OUTPUT);
	wakeUpBLE();

	SoftwareSerial bleSerial(bleRxPin, bleTxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+MAJOR%04X", value);
	sendCommand(bleSerial, buff);
	if (autosleep) {
		sendCommand(bleSerial, "AT+SLEEP1");
	}

	pinMode(bleTxPin, INPUT);
}

void JDY8::minor(unsigned int value, bool autosleep = true)
{
	pinMode(bleTxPin, OUTPUT);
	wakeUpBLE();

	SoftwareSerial bleSerial(bleRxPin, bleTxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+MINOR%04X", value);
	sendCommand(bleSerial, buff);
	if (autosleep) {
		sendCommand(bleSerial, "AT+SLEEP1");
	}

	pinMode(bleTxPin, INPUT);
}

void JDY8::humidity(short value, bool autosleep = true)
{
	pinMode(bleTxPin, OUTPUT);
	wakeUpBLE();

	SoftwareSerial bleSerial(bleRxPin, bleTxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+HUMID%02X", value);
	sendCommand(bleSerial, buff);
	if (autosleep) {
		sendCommand(bleSerial, "AT+SLEEP1");
	}

	pinMode(bleTxPin, INPUT);
}

void JDY8::temperature(short value, bool autosleep = true)
{
	pinMode(bleTxPin, OUTPUT);
	wakeUpBLE();

	SoftwareSerial bleSerial(bleRxPin, bleTxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+TEMP%02X", value);
	sendCommand(bleSerial, buff);
	if (autosleep) {
		sendCommand(bleSerial, "AT+SLEEP1");
	}

	pinMode(bleTxPin, INPUT);
}

void JDY8::battery(int value, bool autosleep = true)
{
	pinMode(bleTxPin, OUTPUT);
	wakeUpBLE();

	SoftwareSerial bleSerial(bleRxPin, bleTxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+BATT%02X", value);
	sendCommand(bleSerial, buff);
	if (autosleep) {
		sendCommand(bleSerial, "AT+SLEEP1");
	}

	pinMode(bleTxPin, INPUT);
}

void JDY8::wakeUpBLE() 
{
	pinMode(bleResetPin, OUTPUT);
	delay(200);
	digitalWrite(bleResetPin, HIGH);
	delay(500);
	digitalWrite(bleResetPin, LOW);
	delay(100);
	pinMode(bleResetPin, INPUT);
}

void JDY8::sendCommand(SoftwareSerial * bleSerial, const char * data) {
	delay(200);
	bleSerial->print(data);
}