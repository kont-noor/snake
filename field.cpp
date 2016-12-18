#include "field.h"
#include "data.h"

field::field() {}

void field::init() {
  display.init();
}

void field::redraw() {
  display.redraw();
}

void field::putPosition(uint8_t x, uint8_t y) {
  for (uint8_t i = uint8_t(x * PLACE_SIZE); i < (x + 1) * PLACE_SIZE; i++) {
    for (uint8_t j = uint8_t(y * PLACE_SIZE); j < (y + 1) * PLACE_SIZE; j++) {
      display.putPixel((uint8_t)i, (uint8_t)j);
    }
  }
}

void field::removePosition(uint8_t x, uint8_t y) {
  for (uint8_t i = uint8_t(x * PLACE_SIZE); i < (x + 1) * PLACE_SIZE; i++) {
    for (uint8_t j = uint8_t(y * PLACE_SIZE); j < (y + 1) * PLACE_SIZE; j++) {
      display.clearPixel((uint8_t)i, (uint8_t)j);
    }
  }
}

void field::showStartup() {
  display.drawBitmap(snake_data);
  delay(3000);
  uint8_t white[504];
  for (int16_t i = 0; i < 504; i++)
    white[i] = 0;
  display.drawBitmap(white);
}
