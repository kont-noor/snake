#include "snake.h"

snake gameSnake;
uint8_t i = 0;

void setup() {
  gameSnake.init();
}

void loop() {
  if (!random(5))
    i++;

  switch (i) {
    case 0:
      gameSnake.moveUp();
      break;
    case 1:
      gameSnake.moveRight();
      break;
    case 2:
      gameSnake.moveDown();
      break;
    case 3:
      gameSnake.moveLeft();
      break;
    default:
      i = 0;
  }

  delay(200);
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
