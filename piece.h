#ifndef PIECE_H
#define PIECE_H

#include "position.h"
#include <vector>

class ChessBoard;
class Piece
{
  // private:
  //   char symbol;
public:
  char symbol;
  Piece(char symbol);
  virtual ~Piece();
  virtual bool valid_move(ChessBoard *bo, Position pos1, Position pos2) = 0;
  // virtual bool isKingChecked();
  char get_symbol();
  char get_type();
  char get_color();
};

#endif
