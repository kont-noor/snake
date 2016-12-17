#include "field.h"

class snake {
public:
  snake();
  void init();
  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
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
  void move();
  bool checkSelfCollision();
  void notifyDead();
};
