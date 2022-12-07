#ifndef PIECE_H
#define PIECE_H

#include "position.h"
#include <vector>
#include <memory>

class ChessBoard;

class Piece
{
  private:
    char symbol;
    int move_count;
  public:
    Piece(char symbol);
    virtual ~Piece();
    virtual bool valid_move(ChessBoard *bo, Position pos1, Position pos2) = 0;
    char get_symbol();
    char get_type();
    char get_color();
    int get_move_count();
    void add_move_count();
    void sub_move_count();
};

#endif
