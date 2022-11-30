#include "position.h"

Position::Position(int x, int y): x{x}, y{y} {}

int Position::get_x_pos() {
  return this->x;
}

int Position::get_y_pos() {
  return this->y;
}
