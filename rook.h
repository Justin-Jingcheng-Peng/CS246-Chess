#ifndef ROOK_H
#define ROOK_H
#include "piece.h"
#include <cmath>

class Rook: public Piece {
  private:  
    int move_count = 0;
  public:  
    // ctor for Rook
    Rook(char symbol);
    // Checks if the Rook move is valid
    bool valid_move(ChessBoard* bo, Position pos1, Position pos2) override;
};

#endif
