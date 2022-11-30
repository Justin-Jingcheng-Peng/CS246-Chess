#ifndef MOVE_H
#define MOVE_H
#include <string>
#include "position.h"

class Piece;

class Move{
  private:
    Position original_pos; // The position of the moved_piece before being moved.
    Position final_pos; // The position of the moved_piece after moving
    Piece* removed_piece; // The piece that was removed
    Piece* moved_piece; // The piece that moved
    bool is_en_passant; // Did en_passant occur
    bool is_castle; // Did castling occur
    bool is_convert; // Did the pawn convert
  public:
    // Ctor for Move
    Move(Piece* moved_piece, Piece* removed_piece, Position original_pos, Position final_pos, bool is_en_passant, bool is_castle, bool is_convert);
    // getter for moved_piece field
    Piece* get_moved_piece();
    // getter for removed_piece field
    Piece* get_removed_piece();
    // getter for original_pos field
    Position get_orig_pos();
    // getter for final_pos field
    Position get_final_pos();
    // getter for is_en_passant field
    bool get_en_passant();
    // getter for is_castle field
    bool get_castle();
    // getter for is_convert field
    bool get_convert();
    // sets the is_convert field to new_convert
    void set_convert(bool new_convert);
};

#endif
