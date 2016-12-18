#include "screen.h"

#define PLACE_SIZE 4
#define FIELD_X 84 / PLACE_SIZE
#define FIELD_Y 48 / PLACE_SIZE

class field {
public:
  field();
  void init();
  void redraw();
  void putPosition(uint8_t, uint8_t);
  void removePosition(uint8_t, uint8_t);
  void showStartup();
private:
  screen display;
};
