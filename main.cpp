#include "snake.h"

snake gameSnake;

void setup() {
  gameSnake.init();
}

void loop() {
  gameSnake.moveLeft();
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
