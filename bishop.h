#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
#include <cmath>

class Bishop: public Piece {
  private:  

  public:  
    // ctor for bishop
    Bishop(char symbol);
    // Checks if the bishop move is valid
    bool valid_move(ChessBoard* bo, Position pos1, Position pos2) override;
};

#endif
