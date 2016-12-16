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
};
