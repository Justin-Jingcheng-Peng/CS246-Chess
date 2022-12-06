#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"
#include <cmath>

class Queen: public Piece {
  private:  
    
  public:  
    // ctor for queen
    Queen(char symbol);
    // Checks if the queen move is valid
    bool valid_move(ChessBoard* bo, Position pos1, Position pos2) override;
};

#endif