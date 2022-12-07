#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
#include <cmath>
#include <memory>

class Pawn: public Piece {
  private:  
    
  public:  
    // ctor for pawn
    Pawn(char symbol);
    // Checks if the pawn move is valid
    bool valid_move(ChessBoard* bo, Position pos1, Position pos2) override;
};

#endif
