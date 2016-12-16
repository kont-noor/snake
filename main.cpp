#include "snake.h"

snake gameSnake;

void setup() {
  gameSnake.init();
}

void loop() {
  gameSnake.moveUp();
  delay(300);
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
