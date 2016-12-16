#include "snake.h"

snake::snake() {}

void snake::init() {
  gameField.init();
}

void snake::moveLeft() {
  gameField.redraw();
}
