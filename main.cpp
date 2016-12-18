#include "snake.h"

snake gameSnake;
uint8 input;
int previousMillis = 0;
int interval = 300;

void setup() {
  gameSnake.init();
}

void loop() {
  while (SerialUSB.available()) {
    input = SerialUSB.read();
    switch (input) {
      case 'h':
        gameSnake.moveLeft();
        break;
      case 'j':
        gameSnake.moveDown();
        break;
      case 'k':
        gameSnake.moveUp();
        break;
      case 'l':
        gameSnake.moveRight();
        break;
    }
  }

  // TODO: delay works worse but it fixes breaking head
  if (millis() - previousMillis > interval) {
    previousMillis = millis();

    gameSnake.move();
  }
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
