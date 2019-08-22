/*
	Libofanten.h - Library for using Blinkofanten LED Matrix
	Created by jstsmthrgk
	basically a library wrapper of blinkofant_testcode.ino by wizard23 and TomK32
	https://github.com/DevLoL/blinkofanten/blob/master/blinkofant_testcode/blinkofant_testcode.ino
*/


#include "Libofanten.h"
#include "SPI.h"

BlofClass Blof;
int BlofClass::active = 1;
int BlofClass::panels;
int BlofClass::panelDataSize;
uint8_t * BlofClass::panelData;

void BlofClass::begin(int panelcount) {
	panels = panelcount;
	panelDataSize = panels*10;
	panelData = new uint8_t[panelDataSize];

	pinMode(CLEAR_PANEL_PIN, OUTPUT);
	pinMode(DATA_PIN, OUTPUT);
	pinMode(CLOCK_PIN, OUTPUT);

	digitalWrite(CLEAR_PANEL_PIN, LOW);
	digitalWrite(DATA_PIN, LOW);
	digitalWrite(CLOCK_PIN, LOW);

	SPI.begin();
	SPI.setBitOrder(LSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV128); // biggest divider there is.
}

void BlofClass::clear() {
	for (int i = 0; i < panelDataSize; i++) {
		panelData[i] = 0;
	}
}

void BlofClass::setBlink(int col, int val) {
	setPixel(col, -1, val);
}

void BlofClass::setPixel(int col, int row, int val) {
	int index = (row + 1) + col * 10; // y+1 because 1st bit controlls blinking
	int byteNr = index >> 3; // division by 8
	int bitNr = index & 0x7; // rest bei div durch 8
	
	if (val)
	{
		panelData[byteNr] |= 1 << bitNr;
	} else {
		panelData[byteNr] &= ~(1 << bitNr);
	}
}

void BlofClass::off() {
	active = 0;
	digitalWrite(CLEAR_PANEL_PIN, LOW);
}

void BlofClass::on() {
	active = 1;
	digitalWrite(CLEAR_PANEL_PIN, HIGH);
}

void BlofClass::flush() {
	if (active) {
		digitalWrite(CLEAR_PANEL_PIN, LOW);
	}
	for (int i = 0; i < panelDataSize; i++) {
		uint8_t value = panelData[i];
		SPDR = panelData[i];
		while (!(SPSR & (1 << SPIF)));
	}
	if (active) {
		digitalWrite(CLEAR_PANEL_PIN, HIGH);
	}
}
