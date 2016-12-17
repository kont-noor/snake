#include "field.h"

#define DIRECTION_UP 0
#define DIRECTION_DOWN 1
#define DIRECTION_LEFT 2
#define DIRECTION_RIGHT 3

class snake {
public:
  snake();
  void init();
  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
  void move();
private:
  uint8_t direction;
  bool stopped;
  field gameField;

  uint16_t size;
  // TODO: currently snake size is restricted by 10
  uint8_t body[10][2];
  uint8_t buffBody[10][2];

  void redraw();
  void clearLast();
  bool checkSelfCollision();
  void notifyDead();
  void getNextPosition();
  void reverse();
};
