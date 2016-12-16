#include <wirish/wirish.h>
#include "screen.h"

screen gameScreen;

void fillScreen() {
  for (int x = 0; x < 84; x++) {
    for (int y = 0; y < 48; y++) {
      gameScreen.putPixel(x, y);
    }
  }

  gameScreen.redraw();
}

void drawSin(int ky, int kx, bool inverse = false) {
  float result;

  for (int x = 0; x < 84; x++) {
    result = 24.0 + ky * sin((float)x / kx);
    if (result < 48 && result >= 0) {
      if (inverse)
        gameScreen.clearPixel(x, int(result));
      else
        gameScreen.putPixel(x, int(result));
    }
  }
  gameScreen.redraw();
}

void sinuses() {
  for (uint8_t k = 0; k < 24; k++)
    drawSin(k, 12);
  for (uint8_t k = 0; k < 24; k++)
    drawSin(k, 12, true);
  for (int8_t k = 23; k >= 0; k--)
    drawSin(k, 12);
  for (int8_t k = 23; k >= 0; k--)
    drawSin(k, 12, true);
  for (int8_t k = 0; k > -24; k--)
    drawSin(k, 12);
  for (int8_t k = 0; k > -24; k--)
    drawSin(k, 12, true);
  for (int8_t k = -23; k <= 0; k++)
    drawSin(k, 12);
  for (int8_t k = -23; k <= 0; k++)
    drawSin(k, 12, true);
}

void setup() {
  gameScreen.init();
}

void loop() {
  //for (int y = 0; y < 48; y++) {
  //  for (int x = 0; x < 84; x++) {
  //    gameScreen.putPixel(x, y);
  //    gameScreen.redraw();
  //  }
  //}
  //for (int x = 0; x < 84; x++) {
  //  for (int y = 0; y < 48; y++) {
  //    gameScreen.clearPixel(x, y);
  //    gameScreen.redraw();
  //  }
  //}

  sinuses();
}

__attribute__((constructor)) void premain() {
    init();
}

int main() {
  setup();
  while (true) {
    loop();
  }

  return 0;
}
