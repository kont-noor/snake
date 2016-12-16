#include "snake.h"

snake::snake() {}

void snake::init() {
  gameField.init();

  size = 3;

  body[0][0] = 10;
  body[1][0] = 10;
  body[2][0] = 10;
  body[0][1] = 5;
  body[1][1] = 6;
  body[2][1] = 7;

  redraw();
}

void snake::moveUp() {
  clearLast();
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
  clearLast();
  buffBody[0][0] = (body[0][0] == 20) ? 0 : body[0][0] + 1;
  buffBody[0][1] = body[0][1];
  move();
}

void snake::moveLeft() {
  clearLast();
  buffBody[0][0] = (body[0][0] == 0) ? 20 : body[0][0] - 1;
  buffBody[0][1] = body[0][1];
  move();
}

void snake::move(){
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

void snake::redraw() {
  for (uint16_t i = 0; i < size; i++) {
    gameField.putPosition((uint8_t)body[i][0], (uint8_t)body[i][1]);
  }
  gameField.redraw();
}

void snake::clearLast() {
  gameField.removePosition(body[size - 1][0], body[size - 1][1]);
  gameField.redraw();
}
