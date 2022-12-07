#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
#include <cmath>

class Knight: public Piece {
  private:  
    
  public:  
    // ctor for Knight
    Knight(char symbol);
    // Checks if the Knight move is valid
    bool valid_move(ChessBoard* bo, Position pos1, Position pos2) override;
};

#endif
