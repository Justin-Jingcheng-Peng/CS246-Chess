#ifndef KING_H
#define KING_H
#include "piece.h"
#include <cmath>

class King: public Piece {
  private:  
    int move_count = 0;
  public:  
    // ctor for King
    King(char symbol);
    // Checks if the King move is valid
    bool valid_move(ChessBoard* bo, Position pos1, Position pos2) override;
    void add_move_count();
};

#endif