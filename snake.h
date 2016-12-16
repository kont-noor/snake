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
  field gameField;

  uint16_t size;
  uint8_t body[1000][2];
  uint8_t buffBody[1000][2];

  void redraw();
  void clearLast();
};
