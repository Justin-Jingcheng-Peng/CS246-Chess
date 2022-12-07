#ifndef POSITION_H
#define POSITION_H

class Position
{
  int x, y;
public:
  Position(int x, int y);
  int get_x_pos();
  int get_y_pos();
  int dist_squared(Position pos);
};

#endif
