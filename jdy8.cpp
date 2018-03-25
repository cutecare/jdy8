/*
Part of http://cutecare.ru project
Author: evgeny.savitsky@gmail.com
*/
#include "jdy8.h"

/**
 * Constructor
 */
JDY8::JDY8(int rxPin = 3, int txPin = 4, int resetPin = 5, long baud = 115200)
{
	bleRxPin = rxPin;
	bleTxPin = txPin;
	bleResetPin = resetPin;
	bleBaud = baud;
}

void JDY8::configure(const char * bleName, int io1 = 0, int io2 = 0, int io3 = 0, int io4 = 0)
{
	pinMode(bleRxPin, OUTPUT);
	
	SoftwareSerial bleSerial(bleTxPin, bleRxPin);
	bleSerial.begin(bleBaud);
	
	sendCommand(&bleSerial, "AT+RESTORE");
	delay(1000);

	char text[64] = "";
	sprintf(text, "AT+NAME%s", bleName);
	sendCommand(&bleSerial, text);

	sendCommand(&bleSerial, "AT+HOSTEN3");
	sendCommand(&bleSerial, "AT+CLSSE0");
	sendCommand(&bleSerial, "AT+RST");
	delay(500);
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

	pinMode(bleRxPin, INPUT);
}

void JDY8::setIOPin(int index, int value, bool autosleep)
{
	pinMode(bleRxPin, OUTPUT);
	if ( autosleep ) {
		wakeUpBLE();
	}

	SoftwareSerial bleSerial(bleTxPin, bleRxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+PIO%d%d", index, value);
	sendCommand(&bleSerial, buff);
	if (autosleep) {
		sendCommand(&bleSerial, "AT+SLEEP1");
	}

	pinMode(bleRxPin, INPUT);
}

void JDY8::setData(unsigned int minor = 0, unsigned int major = 0, short humidity = 0, short temperature = 0, short battery = 0, bool autosleep = true)
{
	pinMode(bleRxPin, OUTPUT);
	if ( autosleep ) {
		wakeUpBLE();
	}

	SoftwareSerial bleSerial(bleTxPin, bleRxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+MAJOR%04X", major);
	sendCommand(&bleSerial, buff);
	sprintf(buff, "AT+MINOR%04X", minor);
	sendCommand(&bleSerial, buff);
	sprintf(buff, "AT+HUMID%02X", humidity);
	sendCommand(&bleSerial, buff);
	sprintf(buff, "AT+TEMP%02X", temperature);
	sendCommand(&bleSerial, buff);
	sprintf(buff, "AT+BATT%02X", battery);
	sendCommand(&bleSerial, buff);
	if (autosleep) {
		sendCommand(&bleSerial, "AT+SLEEP1");
	}

	pinMode(bleRxPin, INPUT);
}

void JDY8::major(unsigned int value, bool autosleep = true)
{
	pinMode(bleRxPin, OUTPUT);
	if ( autosleep ) {
		wakeUpBLE();
	}

	SoftwareSerial bleSerial(bleTxPin, bleRxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+MAJOR%04X", value);
	sendCommand(&bleSerial, buff);
	if (autosleep) {
		sendCommand(&bleSerial, "AT+SLEEP1");
	}

	pinMode(bleRxPin, INPUT);
}

void JDY8::minor(unsigned int value, bool autosleep = true)
{
	pinMode(bleRxPin, OUTPUT);
	if ( autosleep ) {
		wakeUpBLE();
	}

	SoftwareSerial bleSerial(bleTxPin, bleRxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+MINOR%04X", value);
	sendCommand(&bleSerial, buff);
	if (autosleep) {
		sendCommand(&bleSerial, "AT+SLEEP1");
	}

	pinMode(bleRxPin, INPUT);
}

void JDY8::humidity(short value, bool autosleep = true)
{
	pinMode(bleRxPin, OUTPUT);
	if ( autosleep ) {
		wakeUpBLE();
	}

	SoftwareSerial bleSerial(bleTxPin, bleRxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+HUMID%02X", value);
	sendCommand(&bleSerial, buff);
	if (autosleep) {
		sendCommand(&bleSerial, "AT+SLEEP1");
	}

	pinMode(bleRxPin, INPUT);
}

void JDY8::temperature(short value, bool autosleep = true)
{
	pinMode(bleRxPin, OUTPUT);
	if ( autosleep ) {
		wakeUpBLE();
	}

	SoftwareSerial bleSerial(bleTxPin, bleRxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+TEMP%02X", value);
	sendCommand(&bleSerial, buff);
	if (autosleep) {
		sendCommand(&bleSerial, "AT+SLEEP1");
	}

	pinMode(bleRxPin, INPUT);
}

void JDY8::battery(short value, bool autosleep = true)
{
	pinMode(bleRxPin, OUTPUT);
	if ( autosleep ) {
		wakeUpBLE();
	}

	SoftwareSerial bleSerial(bleTxPin, bleRxPin);
	bleSerial.begin(bleBaud);

	char buff[32] = "";
	sprintf(buff, "AT+BATT%02X", value);
	sendCommand(&bleSerial, buff);
	if (autosleep) {
		sendCommand(&bleSerial, "AT+SLEEP1");
	}

	pinMode(bleRxPin, INPUT);
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

void JDY8::sendCommand(const SoftwareSerial * bleSerial, const char * data) {
	delay(250);
	bleSerial->print(data);
}
