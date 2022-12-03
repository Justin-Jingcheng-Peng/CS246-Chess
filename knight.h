#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
#include <cmath>
#include <vector>

class Knight: public Piece {
  private:  
    int move_count = 0;
  public:  
    // ctor for Knight
    Knight(char symbol);
    // Checks if the Knight move is valid
    bool valid_move(ChessBoard* bo, Position pos1, Position pos2) override;
    void add_move_count();
};

#endif