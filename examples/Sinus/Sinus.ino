#include "Libofanten.h"

#define PANELS 3

uint8_t offset_value = 0;

void setup() {
  Blof.begin(PANELS);
}

void sinus(int wellenlaenge, int offset) {
  for (int i=0; i<PANELS*8; i++) {
    float factor=2*PI/wellenlaenge;
    int x = round(sin((i-offset)*factor)*4)+4;
    Blof.setPixel(i, x, 1);
  }
}

void loop() {
  Blof.clear();
  sinus(24,offset_value);
  offset_value = (offset_value + 1) % 24;
  Blof.flush();
  delay(30);
}
