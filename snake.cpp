#include "snake.h"

snake::snake() {}

void snake::init() {
  gameField.init();

  size = 10;

  for (uint8_t i = 0; i < size; i++) {
    body[i][0] = 10;
    body[i][1] = i + 1;
  }

  stopped = false;

  redraw();
}

void snake::moveUp() {
  buffBody[0][0] = body[0][0];
  buffBody[0][1] = (body[0][1] == 0) ? 11 : body[0][1] - 1;
  move();
}

void snake::moveDown() {
  clearLast();
  buffBody[0][0] = body[0][0];
  buffBody[0][1] = (body[0][1] == 11) ? 0 : body[0][1] + 1;
  move();
}

void snake::moveRight() {
  buffBody[0][0] = (body[0][0] == 20) ? 0 : body[0][0] + 1;
  buffBody[0][1] = body[0][1];
  move();
}

void snake::moveLeft() {
  buffBody[0][0] = (body[0][0] == 0) ? 20 : body[0][0] - 1;
  buffBody[0][1] = body[0][1];
  move();
}

void snake::move(){
  if (stopped || checkSelfCollision())
    return;

  clearLast();

  gameField.putPosition(buffBody[0][0], buffBody[0][1]);
  gameField.redraw();

  for (uint16_t i = 1; i < size; i++) {
    buffBody[i][0] = body[i - 1][0];
    buffBody[i][1] = body[i - 1][1];
  }

  for (uint16_t i = 0; i < size; i++) {
    body[i][0] = uint8_t(buffBody[i][0]);
    body[i][1] = uint8_t(buffBody[i][1]);
  }

  redraw();
}

bool snake::checkSelfCollision() {
  for (uint16_t i = 0; i < size; i++) {
    if (body[i][0] == buffBody[0][0] && body[i][1] == buffBody[0][1]) {
      stopped = true;
      notifyDead();
      return true;
    }
  }

  return false;
}

void snake::notifyDead() {
  for (uint8_t i = 0; i < 3; i++) {
    delay(400);
    for (uint16_t i = 0; i < size; i++)
      gameField.removePosition((uint8_t)body[i][0], (uint8_t)body[i][1]);
    gameField.redraw();
    delay(400);
    redraw();
  }
}

void snake::redraw() {
  for (uint16_t i = 0; i < size; i++)
    gameField.putPosition((uint8_t)body[i][0], (uint8_t)body[i][1]);
  gameField.redraw();
}

void snake::clearLast() {
  gameField.removePosition(body[size - 1][0], body[size - 1][1]);
  gameField.redraw();
}
