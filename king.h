#ifndef KING_H
#define KING_H
#include "piece.h"
#include <cmath>
#include <vector>
#include <memory>

class King: public Piece {
  private:  
    
  public:  
    // ctor for King
    King(char symbol);
    // Checks if the King move is valid
    bool valid_move(ChessBoard* bo, Position pos1, Position pos2) override;
};

#endif
