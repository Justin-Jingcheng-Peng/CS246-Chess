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
    bool diagonal(std::vector<std::vector<std::shared_ptr<Piece>>> board, Position pos1, Position pos2);
    bool straight(std::vector<std::vector<std::shared_ptr<Piece>>> board, Position pos1, Position pos2);
};

#endif