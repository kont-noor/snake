#include "snake.h"

snake gameSnake;
int i = 0;

void setup() {
  gameSnake.init();
}

void loop() {
  if (i < 50)
    gameSnake.moveUp();
  else if (i >=50 && i < 100)
    gameSnake.moveRight();
  else if (i >= 100 && i < 150)
    gameSnake.moveDown();
  else if (i >= 150 && i < 200)
    gameSnake.moveLeft();
  else
    i = 0;

  delay(200);
  i++;
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
