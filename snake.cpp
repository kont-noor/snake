#include "snake.h"

snake::snake() {}

void snake::init() {
  randomSeed(analogRead(0));
  gameField.init();

  size = 2;

  for (uint8_t i = 0; i < size; i++) {
    body[i][0] = 10;
    body[i][1] = i + 1;
  }

  direction = DIRECTION_UP;
  stopped = false;

  redraw();
  setFeed();
}

void snake::setFeed() {
  do {
    feed[0] = (uint8_t)random(20);
    feed[1] = (uint8_t)random(10);
  } while (checkCollisionWith(feed));

  gameField.putPosition((uint8_t)feed[0], (uint8_t)feed[1]);
  gameField.redraw();
}

void snake::moveUp() {
  if (direction == DIRECTION_DOWN)
    reverse();
  else
  direction = DIRECTION_UP;
}

void snake::moveDown() {
  if (direction == DIRECTION_UP)
    reverse();
  else
    direction = DIRECTION_DOWN;
}

void snake::moveRight() {
  if (direction == DIRECTION_LEFT)
    reverse();
  else
  direction = DIRECTION_RIGHT;
}

void snake::moveLeft() {
  if (direction == DIRECTION_RIGHT)
    reverse();
  else
  direction = DIRECTION_LEFT;
}

void snake::reverse() {
  for (uint16_t i = 0; i < size; i++) {
    buffBody[i][0] = uint8_t(body[size - i - 1][0]);
    buffBody[i][1] = uint8_t(body[size - i - 1][1]);
  }
  for (uint16_t i = 0; i < size; i++) {
    body[i][0] = uint8_t(buffBody[i][0]);
    body[i][1] = uint8_t(buffBody[i][1]);
  }

  if (body[0][0] == body[1][0])
    if (body[0][1] < body[1][1])
      direction = DIRECTION_UP;
    else
      direction = DIRECTION_DOWN;
  else
    if (body[0][0] < body[1][0])
      direction = DIRECTION_RIGHT;
    else
      direction = DIRECTION_LEFT;
}

void snake::move(){
  if (stopped)
    return;

  getNextPosition();

  if (checkSelfCollision())
    return;

  if (buffBody[0][0] == feed[0] && buffBody[0][1] == feed[1]) {
    size++;
    setFeed();
  }
  else {
    clearLast();
    gameField.putPosition(buffBody[0][0], buffBody[0][1]);
    gameField.redraw();
  }

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

void snake::getNextPosition() {
  switch (direction) {
    case DIRECTION_UP:
      buffBody[0][0] = body[0][0];
      buffBody[0][1] = (body[0][1] == 0) ? 11 : body[0][1] - 1;
      break;
    case DIRECTION_DOWN:
      buffBody[0][0] = body[0][0];
      buffBody[0][1] = (body[0][1] == 11) ? 0 : body[0][1] + 1;
      break;
    case DIRECTION_LEFT:
      buffBody[0][0] = (body[0][0] == 0) ? 20 : body[0][0] - 1;
      buffBody[0][1] = body[0][1];
      break;
    case DIRECTION_RIGHT:
      buffBody[0][0] = (body[0][0] == 20) ? 0 : body[0][0] + 1;
      buffBody[0][1] = body[0][1];
      break;
  }
}

bool snake::checkSelfCollision() {
  if (checkCollisionWith(buffBody[0])) {
    stopped = true;
    notifyDead();
    return true;
  }

  return false;
}

bool snake::checkCollisionWith(uint8_t* coordinates) {
  for (uint16_t i = 0; i < size; i++) {
    if (body[i][0] == coordinates[0] && body[i][1] == coordinates[1]) {
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
