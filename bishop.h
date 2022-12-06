#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
#include <cmath>
#include <vector>
#include <memory>

class Bishop: public Piece {
  private:  
    int move_count = 0;
  public:  
    // ctor for bishop
    Bishop(char symbol);
    // Checks if the bishop move is valid
    bool valid_move(ChessBoard* bo, Position pos1, Position pos2) override;
    void add_move_count();
};

#endif