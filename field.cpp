#include "field.h"

field::field() {}

void field::init() {
  display.init();
}

void field::redraw() {
  display.putPixel(random(84), random(48));
  display.redraw();
}
