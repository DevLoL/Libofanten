/*
	Libofanten.h - Library for using Blinkofanten LED Matrix
	Created by jstsmthrgk
	basically a library wrapper of blinkofant_testcode.ino by wizard23 and TomK32
	https://github.com/DevLoL/blinkofanten/blob/master/blinkofant_testcode/blinkofant_testcode.ino
*/

#ifndef LIBOFANTEN_H
#define LIBOFANTEN_H

#include "Arduino.h"

#ifdef ESP8266_WEMOS_D1MINI
  #define CLEAR_PANEL_PIN D8 // pin #10 on the blinkofant panel
  #define DATA_PIN D7 // pin #8
  #define CLOCK_PIN D5 // pin #4
#else
  #define CLEAR_PANEL_PIN 10 // this goes on panel to pin #10 on the blinkofant panel
  #define DATA_PIN 11 // pin #8
  #define CLOCK_PIN 13 // pin #4
#endif

class BlofClass {
public:
	static void begin(int panelcount);
	static void clear();
	static void setBlink(int col, int val);
	static void setPixel(int col, int row, int val);
	static void off();
	static void on();
	static void flush();
private:
	static int panels;
	static int panelDataSize;
	static uint8_t * panelData;
	static int active;
};

extern BlofClass Blof;

#endif
