#include "snake.h"

#define DIRECTION_UP 0
#define DIRECTION_DOWN 1
#define DIRECTION_LEFT 2
#define DIRECTION_RIGHT 3

snake gameSnake;
bool i = false;
uint8_t direction;

void setup() {
  randomSeed(analogRead(0));
  gameSnake.init();
}

void moveHorizontal() {
  if (direction == DIRECTION_LEFT || random(0xffff) % 2) {
    gameSnake.moveLeft();
    direction = DIRECTION_LEFT;
  }
  else {
    gameSnake.moveRight();
    direction = DIRECTION_RIGHT;
  }
}

void moveVertical() {
  if (direction == DIRECTION_UP || random(0xffff) % 2) {
    gameSnake.moveUp();
    direction = DIRECTION_UP;
  }
  else {
    gameSnake.moveDown();
    direction = DIRECTION_DOWN;
  }
}

void loop() {
  if (random(4))
    i = !i;

  i ? moveHorizontal() : moveVertical();

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
