#include "snake.h"

snake gameSnake;
uint8 input;

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
